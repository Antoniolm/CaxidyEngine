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
#include "linearmovement.h"

LinearMovement::LinearMovement()
{
    //dtor
}

//**********************************************************************//

LinearMovement::LinearMovement(float x,float y,float z){
    velocity.x=x;
    velocity.y=y;
    velocity.z=z;
    currentTime=SDL_GetTicks()/1000;
    currentMatrix.identity();
}

//**********************************************************************//

LinearMovement::LinearMovement(const vec3f & aVelocity)
{
    velocity=aVelocity;
    currentTime=SDL_GetTicks()/1000;
    currentMatrix.identity();
}

//**********************************************************************//

LinearMovement::~LinearMovement()
{
    //dtor
}

//**********************************************************************//

void LinearMovement::setParameters(float x,float y,float z){
    velocity.x=x;
    velocity.y=y;
    velocity.z=z;
    currentMatrix.identity();
}

//**********************************************************************//

void LinearMovement::setParameters(const vec3f & aVelocity){
    velocity=aVelocity;
    currentMatrix.identity();
}

//**********************************************************************//

Matrix4f & LinearMovement::updateState(float time){
    time=time/1000;
    currentMatrix.translation(velocity.x*time,velocity.y*time,velocity.z*time);

    currentTime+=time;
    return currentMatrix;
}

//**********************************************************************//

void LinearMovement::resetState(){

}
