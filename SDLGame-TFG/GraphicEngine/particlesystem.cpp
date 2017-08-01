// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David López Machado
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "particlesystem.h"

ParticleSystem::ParticleSystem()
{
    //ctor
}

//**********************************************************************//

ParticleSystem::ParticleSystem(int numParticle,string aMaterial,vec3f aScale,vec3f aMinPos,vec3f aMaxPos,vec3f aVelocity,float aMinTime,float aMaxTime)
{
    vec3f pos=(aMaxPos-aMinPos)/2;
    position=vec4f(pos.x,pos.y,pos.z,1.0);

    MaterialCollection * materialCollect=MaterialCollection::getInstance();

    material=materialCollect->getMaterial(aMaterial);
    scale=aScale;
    nParticles=numParticle;
    minPos=aMinPos;
    maxPos=aMaxPos;
    velocity=aVelocity;
    minTime=aMinTime;
    maxTime=aMaxTime;
    currentParticles=0;
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

ParticleSystem::ParticleSystem(const rapidjson::Value & particleFeature){

    MaterialCollection * materialCollect=MaterialCollection::getInstance();

    material=materialCollect->getMaterial(particleFeature["material"].GetString());
    scale=vec3f(particleFeature["scale"][0].GetFloat(), particleFeature["scale"][1].GetFloat(), particleFeature["scale"][2].GetFloat());
    nParticles=particleFeature["number"].GetFloat();
    minPos=vec3f(particleFeature["minPosition"][0].GetFloat(), particleFeature["minPosition"][1].GetFloat(), particleFeature["minPosition"][2].GetFloat());
    maxPos=vec3f(particleFeature["maxPosition"][0].GetFloat(), particleFeature["maxPosition"][1].GetFloat(), particleFeature["maxPosition"][2].GetFloat());
    velocity=vec3f(particleFeature["velocity"][0].GetFloat(), particleFeature["velocity"][1].GetFloat(), particleFeature["velocity"][2].GetFloat());
    minTime=particleFeature["minLife"].GetFloat();
    maxTime=particleFeature["maxLife"].GetFloat();
    currentParticles=0;
    currentTime=SDL_GetTicks();

    vec3f pos=minPos+((maxPos-minPos)/2);
    position=vec4f(pos.x,pos.y,pos.z,1.0);


}

//**********************************************************************//

ParticleSystem::~ParticleSystem()
{
    for(list<Particle *>::iterator it = particles.begin() ; it != particles.end(); ++it)
        delete (*it);
}

//**********************************************************************//

void ParticleSystem::visualization(Context & cv){
    list<Particle *>::iterator it;
    for(it=particles.begin();it!=particles.end();it++){
        (*it)->visualization(cv);
    }
}

//**********************************************************************//

void ParticleSystem::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    list<Particle *>::iterator it=particles.begin();
    while(it!=particles.end()){ //loop about our particle and update them
        (*it)->updateState(gameState);
        if((*it)->getRemainingTime()<=0.0){
            delete (*it);
            it=particles.erase(it);
            currentParticles--;
        }
        else
            it++;
    }

    //Create new particles if some of them is dead
    int diff=nParticles-currentParticles;
    for(int i=0;i<diff;i++){
        particles.push_back(new Particle(material,scale,minPos,maxPos,velocity,minTime,maxTime));
        currentParticles++;
    }

    currentTime+=(time-currentTime);
}

//**********************************************************************//
void ParticleSystem::setParameters(int numParticle,string aMaterial,vec3f aScale,vec3f aMinPos,vec3f aMaxPos,vec3f aVelocity,float aMinTime,float aMaxTime){
    vec3f pos=(aMaxPos-aMinPos)/2;
    position=vec4f(pos.x,pos.y,pos.z,1.0);

    MaterialCollection * materialCollect=MaterialCollection::getInstance();

    material=materialCollect->getMaterial(aMaterial);
    scale=aScale;
    nParticles=numParticle;
    minPos=aMinPos;
    maxPos=aMaxPos;
    velocity=aVelocity;
    minTime=aMinTime;
    maxTime=aMaxTime;
    currentParticles=0;
    currentTime=SDL_GetTicks();

}

//**********************************************************************//

int ParticleSystem::getNumParticle(){
    return nParticles;
}

//**********************************************************************//

Material * ParticleSystem::getMaterial(){
    return material;
}

//**********************************************************************//

vec3f ParticleSystem::getScale(){
    return scale;
}

//**********************************************************************//

vec3f ParticleSystem::getMaxPos(){
    return maxPos;
}

//**********************************************************************//

vec3f ParticleSystem::getMinPos(){
    return minPos;
}

//**********************************************************************//

vec3f ParticleSystem::getVelocity(){
    return velocity;
}

//**********************************************************************//

float ParticleSystem::getMinTime(){
    return minTime;
}

//**********************************************************************//

float ParticleSystem::getMaxTime(){
    return maxTime;
}
