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

#include "avatar.h"

Avatar::~Avatar()
{
}

//**********************************************************************//

void Avatar::visualization(Context & cv){
}

//**********************************************************************//

void Avatar::updateState(GameState & gameState){}

//**********************************************************************//

void Avatar::setLife(float aLife){
    life=aLife;
}

//**********************************************************************//

void Avatar::setMaxLife(float aMaxLife){
    maxLife=aMaxLife;
}

//**********************************************************************//

float Avatar::getLite(){
    return life;
}

//**********************************************************************//

float Avatar::getMaxLite(){
    return maxLife;
}

//**********************************************************************//

void Avatar::addLife(float value){
    life+=value;
    if(life>maxLife){
        life=maxLife;
    }
}
