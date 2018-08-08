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

#include "object3d.h"
#include "rootmap.h"
#include "gamestate.h"

namespace CaxidyEngine {
    
Object3D::Object3D()
{
    countLink=0;
}

//**********************************************************************//

Object3D::~Object3D()
{
    //dtor
}

//**********************************************************************//

void Object3D::visualization(Context & cv){}

//**********************************************************************//

void Object3D::updateState(GameState & gameState){}

//**********************************************************************//

BoundingBox Object3D::getBoundingBox(){
    BoundingBox result;
    result.maxValue=vec3f(0.5,0.5,0.5);
    result.minValue=vec3f(-0.5,-0.5,-0.5);
    return result;
}

//**********************************************************************//

void Object3D::obtainPosition(Context & cv){
}

//**********************************************************************//

vec4f Object3D::getPosition(){
    return position;
}

//**********************************************************************//

void Object3D::removeLink(){
    countLink--;
}

//**********************************************************************//

void Object3D::addLink(){
    countLink++;
}

//**********************************************************************//

int Object3D::getCountLink(){
    return countLink;
}

//**********************************************************************//

bool Object3D::isDeleting(){
    return false;
}

} // CaxidyEngine 
