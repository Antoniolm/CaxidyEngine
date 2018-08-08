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

#include "particle.h"

Particle::Particle(){
}

//**********************************************************************//

Particle::Particle(Material * material,vec3f aScale,vec3f minPos,vec3f maxPos,vec3f aVelocity,float minTime,float maxTime){
    position.x=minPos.x + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxPos.x-minPos.x)));
    position.y=minPos.y + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxPos.y-minPos.y)));
    position.z=minPos.z + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxPos.z-minPos.z)));
    velocity=aVelocity;
    remainingTime= minTime + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxTime-minTime)));

    MeshCollection * meshCollect= MeshCollection::getInstance();

    transMatrix=new Matrix4f();
    transMatrix->translation(position.x,position.y,position.z);

    Matrix4f * scaleParticle=new Matrix4f();
    scaleParticle->scale(aScale.x,aScale.y,aScale.z);

    root=new NodeSceneGraph();
    root->add(transMatrix);
    root->add(scaleParticle);
    root->add(material);
    root->add(meshCollect->getMesh(SPHERE));
    currentTime=SDL_GetTicks();
}

//**********************************************************************//

Particle::~Particle()
{
    delete root;
}

//**********************************************************************//

void Particle::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void Particle::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    //update the position
    LinearMovement lineMove(velocity);
    transMatrix->product(lineMove.updateState(time-currentTime).getMatrix());

    remainingTime-=(time-currentTime);
    currentTime+=(time-currentTime);
}

//**********************************************************************//

float Particle::getRemainingTime(){
    return remainingTime;
}

