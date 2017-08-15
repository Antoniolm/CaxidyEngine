// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David López Machado
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

#include "inventory.h"

Inventory::Inventory(){
    items.resize(sizeY);

    for(int i=0;i<items.size();i++){
        items[i].resize(sizeX);
    }

    if(items[1][1]==0)
        cout<< "yeeep"<<endl;
}

//**********************************************************************//

Inventory::~Inventory(){

}

//**********************************************************************//

unsigned Inventory::getSizeX(){
    return sizeX;
}

//**********************************************************************//

unsigned Inventory::getSizeY(){
    return sizeY;
}
