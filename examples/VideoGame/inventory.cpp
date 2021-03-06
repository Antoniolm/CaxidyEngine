// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David L�pez Machado
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
#include "equipment.h"

Inventory::Inventory(int tamX,int tamY){
    sizeY=tamY;
    sizeX=tamX;

    items.resize(sizeY);

    for(int i=0;i<items.size();i++){
        items[i].resize(sizeX);
    }
}

//**********************************************************************//

Inventory::~Inventory(){
    for(int i=0;i<items.size();i++){
        for(int j=0;j<items[i].size();j++){
            if(items[i][j]!=0)
                delete items[i][j];
        }
    }
}

//**********************************************************************//

unsigned Inventory::getSizeX(){
    return sizeX;
}

//**********************************************************************//

unsigned Inventory::getSizeY(){
    return sizeY;
}

//**********************************************************************//

void Inventory::addItem(int x,int y,Equipment * aEquip){
    items[y][x]=aEquip;
}

//**********************************************************************//

bool Inventory::removeItem(int x,int y){
    bool result=false;

    if(items[y][x]!=0){
        Equipment * equip=items[y][x];

        items[y][x]=0;
        delete equip;
        result=true;
    }

    return result;
}

//**********************************************************************//

Equipment * Inventory::getItem(int x,int y){
    return items[y][x];
}

//**********************************************************************//

vector<Equipment *> & Inventory::getItems(){
    auxItems.clear();

    for(int i=0;i<items.size();i++){
        for(int j=0;j<items[i].size();j++)
            if(items[i][j]!=0){
                auxItems.push_back(items[i][j]);
            }
    }

    return auxItems;
}

//**********************************************************************//

int Inventory::getNumItems(){
    return getItems().size();
}

//**********************************************************************//

bool Inventory::isEmpty(int x,int y){
    bool result=false;

    if(items[y][x]==0)
        result=true;

    return result;

}

//**********************************************************************//

pair<int,int> Inventory::emptySlot(){
    pair<int,int> result(-1,-1);
    bool  isEmpty=false;

    for(int i=0;i<items.size() && !isEmpty;i++){
        for(int j=0;j<items[i].size() && !isEmpty;j++)
            if(items[i][j]==0){
                result.first=j;
                result.second=i;
                isEmpty=true;
            }
    }

    return result;
}

//**********************************************************************//

bool Inventory::equipItem(int x,int y){
    bool result=false;

    if(items[y][x]!=0 && !items[y][x]->isEquipped()){
        unequipItem(items[y][x]->getEquipType());

        items[y][x]->setEquipped(true);
        result=true;
    }

    return result;
}

//**********************************************************************//

bool Inventory::unequipItem(int typeEquip){
    bool result=false;

    for(int i=0;i<items.size() && !result;i++){
        for(int j=0;j<items[i].size() && !result;j++)

            //if the items is not null && is equipped && is the same type of the parameter
            if(items[i][j]!=0 && items[i][j]->isEquipped() && items[i][j]->getEquipType()==typeEquip){
                items[i][j]->setEquipped(false);
                result=true;
            }
    }

    return result;

}

