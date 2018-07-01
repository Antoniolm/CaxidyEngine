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

#include "inventorymenu.h"
#include "VideoGame/inventory.h"
#include "GraphicEngine/text.h"
#include "collection/meshcollection.h"



InventoryMenu::InventoryMenu(){

}

//**********************************************************************//

InventoryMenu::~InventoryMenu(){
    delete root;

    delete currentMaterial;
    delete materialBack;
    delete confirmMaterial;
    delete materialEquipped;

    delete inventory;
}

//**********************************************************************//

void InventoryMenu::visualization(Context & cv){

}

//**********************************************************************//

void InventoryMenu::updateState(GameState & gameState){

}

//**********************************************************************//

void InventoryMenu::clearInventory(){

}