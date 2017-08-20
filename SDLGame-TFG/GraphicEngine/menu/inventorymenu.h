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

#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include <iostream>
#include <vector>
#include "savedmanager.h"
#include "object3d.h"
#include "rootmap.h"
#include "context/context.h"
#include "mesh/mesh.h"
#include "nodescenegraph.h"
#include "material/texture.h"
#include "material/material.h"
#include "sound/sound.h"
#include "menu.h"
#include "profile.h"
#include "mainmenu.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "collection/soundcollection.h"
#include "../VideoGame/inventory.h"
#include <string>

using namespace std;

class InventoryMenu : public Menu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        InventoryMenu(vec3f initPos,vec3f dItem,string fileName,Inventory & inv);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~InventoryMenu();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);

        bool addEquip(Equipment * aEquip);

    protected:

    private:
        NodeSceneGraph * createMatrixItems();
        vec3f initialPosition;               // Initial position of the menu
        Matrix4f * selectedPosition;         // The position of the current selected item
        Material * materialBack;             // The texture in background
        Sound * openSound;                   // Sound for open an option
        Sound * moveSound;                   // Sound for movement
        vec3f distItem;                      // Distance between items
        int currentItemX;
        int currentItemY;
        Inventory * inventory;               // Logistic inventory of the interface
        Material * itemView[3][6];
};

#endif // INVENTORYMENU_H
