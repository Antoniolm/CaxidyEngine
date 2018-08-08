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
#include "axisrotation.h"

namespace CaxidyEngine {
    
AxisRotation::AxisRotation()
{
    //ctor
}

//**********************************************************************//

AxisRotation::AxisRotation(float anAVelocity,float x,float y,float z){
    angularVelocity=anAVelocity;
    axis.x=x;
    axis.y=y;
    axis.z=z;
    currentMatrix.identity();
    currentGrade=0;
}

//**********************************************************************//

AxisRotation::~AxisRotation()
{
    //dtor
}

//**********************************************************************//

void AxisRotation::setParameters(float anAVelocity,float x,float y,float z){
    angularVelocity=anAVelocity;
    axis.x=x;
    axis.y=y;
    axis.z=z;
    currentMatrix.identity();
    currentGrade=0;
}

//**********************************************************************//

float AxisRotation::getAngularVelocity(){
    return angularVelocity;
}

//**********************************************************************//

vec3f AxisRotation::getAxis(){
    return axis;
}

//**********************************************************************//

float AxisRotation::getCurrentGrade(){
    return currentGrade;
}

//**********************************************************************//

Matrix4f & AxisRotation::updateState(float time){
    time=time/1000;

    currentGrade+=angularVelocity*time;
    currentMatrix.rotation(currentGrade,axis.x,axis.y,axis.z);

    return currentMatrix;
}

//**********************************************************************//

void AxisRotation::resetState(){

}

} // CaxidyEngine
