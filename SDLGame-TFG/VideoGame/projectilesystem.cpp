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

#include "projectilesystem.h"

ProjectileSystem::ProjectileSystem(vec3f aRadio,vec3f aPos,vec3f aVeloc,int aDir,float aDelay,string aMesh,string aMaterial)
{
    radioActivity=aRadio;
    position=aPos;
    velocity=aVeloc;

    direction=(avatarDirection)aDir;
    timeBWprojectile=aDelay;//time between one projectile and another
    mesh=aMesh;
    material=aMaterial;
    currentTime=SDL_GetTicks();
    projectileDelay=currentTime;
}

//**********************************************************************//

ProjectileSystem::ProjectileSystem(const rapidjson::Value & projectileFeature){

    radioActivity=vec3f(projectileFeature["radioActivity"][0].GetFloat(), projectileFeature["radioActivity"][1].GetFloat(), projectileFeature["radioActivity"][2].GetFloat());
    position=vec3f(projectileFeature["position"][0].GetFloat(), projectileFeature["position"][1].GetFloat(), projectileFeature["position"][2].GetFloat());
    velocity=vec3f(projectileFeature["velocity"][0].GetFloat(), projectileFeature["velocity"][1].GetFloat(), projectileFeature["velocity"][2].GetFloat());

    direction=(avatarDirection)projectileFeature["direction"].GetFloat();
    timeBWprojectile=projectileFeature["delay"].GetFloat();//time between one projectile and another
    mesh=projectileFeature["mesh"].GetString();
    material=projectileFeature["material"].GetString();
    currentTime=SDL_GetTicks();
    projectileDelay=currentTime;
}

//**********************************************************************//

ProjectileSystem::~ProjectileSystem()
{
    for(list<Projectile *>::iterator it = projectiles.begin() ; it != projectiles.end(); ++it)
        delete (*it);
}

//**********************************************************************//

void ProjectileSystem::visualization(Context & cv){
    list<Projectile *>::iterator it;
    for(it=projectiles.begin();it!=projectiles.end();it++){
        (*it)->visualization(cv);
    }
}

//**********************************************************************//

void ProjectileSystem::updateState(GameState & gameState){
    float time=gameState.time;
    if(time-currentTime>200){
        time+=-50;
        projectileDelay=time-(currentTime-projectileDelay);
        currentTime=time;
    }

    list<Projectile *>::iterator it=projectiles.begin();
    while(it!=projectiles.end()){
        (*it)->updateState(gameState);
        if(!(*it)->isLive()){
            delete (*it);
            it=projectiles.erase(it);
        }
        else
            it++;
    }

    vec3f posHero=gameState.refPoint;
    vec3f distance=vec3f(position.x,position.y,position.z)-posHero;
    if(projectileDelay<(time-timeBWprojectile) && (distance.x>-radioActivity.x && distance.x<radioActivity.x)&&(distance.y>-radioActivity.y && distance.y<radioActivity.y)&&(distance.z>-radioActivity.z && distance.z<radioActivity.z)){
        projectiles.push_back(new Projectile(position,velocity,direction,-25,mesh,material));
        projectileDelay=time;
    }


    currentTime+=(time-currentTime);
}

//**********************************************************************//

void ProjectileSystem::setParameters(vec3f aRadio,vec3f aPos,vec3f aVeloc,int aDir,float aDelay,string aMesh,string aMaterial){
    radioActivity=aRadio;
    position=aPos;
    velocity=aVeloc;

    direction=(avatarDirection)aDir;
    timeBWprojectile=aDelay;//time between one projectile and another
    mesh=aMesh;
    material=aMaterial;
    currentTime=SDL_GetTicks();
    projectileDelay=currentTime;
}

//**********************************************************************//

list<Projectile *> & ProjectileSystem::getArrows(){
    return projectiles;
}

//**********************************************************************//

vec3f ProjectileSystem::getRadio(){
    return radioActivity;
}

//**********************************************************************//

vec3f ProjectileSystem::getPosition(){
    return position;
}

//**********************************************************************//

vec3f ProjectileSystem::getVelocity(){
    return velocity;
}

//**********************************************************************//

int ProjectileSystem::getDir(){
    return direction;
}

//**********************************************************************//

float ProjectileSystem::getDelay(){
    return timeBWprojectile;
}

//**********************************************************************//

string ProjectileSystem::getMesh(){
    return mesh;
}

//**********************************************************************//

string ProjectileSystem::getMaterial(){
    return material;
}
