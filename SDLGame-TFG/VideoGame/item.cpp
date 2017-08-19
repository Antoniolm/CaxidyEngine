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
#include "item.h"

Item::Item(){
}

//**********************************************************************//

Item::~Item(){
}

//**********************************************************************//

void Item::visualization(Context & cv){
}

//**********************************************************************//

void Item::updateState(GameState & gameState){
}
//**********************************************************************//

void Item::setValue(int aValue){
    value=aValue;
}

//**********************************************************************//

int Item::getValue(){
    return value;
}

//**********************************************************************//

bool Item::isTake(){
    return !notTake;
}

//**********************************************************************//

ItemIndex Item::getType2(){
    return type;
}
