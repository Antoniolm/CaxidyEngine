// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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

#include "oscillaterotation.h"

namespace CaxidyEngine {
    
OscillateRotation::OscillateRotation()
{
    //ctor
}

//**********************************************************************//

OscillateRotation::OscillateRotation(bool incre,float maxG,float minG,float initG,float velocity,vec3f dir,int aLoop){
    increment=incre;
    maxGrade=maxG;
    minGrade=minG;
    initialGrade=initG;
    angularVelocity=velocity;
    direction=dir;
    loop=aLoop;

    currentGrade=initialGrade;
    currentTime=SDL_GetTicks()/1000;
    currentMatrix.identity();

    currentLoop=0;
}

//**********************************************************************//

OscillateRotation::~OscillateRotation()
{
    //dtor
}

//**********************************************************************//

void OscillateRotation::setParameters(bool incre,float maxG,float minG,float initG,float velocity,vec3f dir,int aLoop){
    increment=incre;
    maxGrade=maxG;
    minGrade=minG;
    initialGrade=initG;
    angularVelocity=velocity;
    direction=dir;
    loop=aLoop;

    currentGrade=initialGrade;
    currentMatrix.identity();

    currentLoop=0;
}

//**********************************************************************//

Matrix4f & OscillateRotation::updateState(float time){
    time=time/1000;

    if((currentGrade>= maxGrade) && increment){
        increment=false;
        currentLoop++;
    }
    else if((currentGrade<=minGrade) && !increment){
        increment=true;
        currentLoop++;
    }

    if(!increment){
        currentGrade-=angularVelocity*(time);
    }
    else{
        currentGrade+=angularVelocity*(time);
    }

    if(loop==-1 || currentLoop<=loop)
        currentMatrix.rotation(currentGrade,direction.x,direction.y,direction.z);

    return currentMatrix;


}

//**********************************************************************//

void OscillateRotation::resetState(){
    if(loop!=-1){
        currentGrade=initialGrade;
        currentLoop=0;
        currentMatrix.identity();
    }
}

//**********************************************************************//

float OscillateRotation::getMaxGrade(){
    return maxGrade;
}

//**********************************************************************//

float OscillateRotation::getMinGrade(){
    return minGrade;
}

//**********************************************************************//

float OscillateRotation::getInitialGrade(){
    return initialGrade;
}

//**********************************************************************//

float OscillateRotation::getCurrentGrade(){
    return currentGrade;
}

//**********************************************************************//

float OscillateRotation::getAngularVelocity(){
    return angularVelocity;
}

//**********************************************************************//

bool OscillateRotation::getIncrement(){
    return increment;
}

//**********************************************************************//

int OscillateRotation::getLoop(){
    return loop;
}

} // CaxidyEngine
