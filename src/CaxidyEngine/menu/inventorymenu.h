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

#ifndef INVENTORYMENU_H
#define INVENTORYMENU_H

#include <iostream>
#include <vector>
#include "CaxidyEngine/object3d.h"
#include "CaxidyEngine/rootmap.h"
#include "context/context.h"
#include "mesh/mesh.h"
#include "CaxidyEngine/nodescenegraph.h"
#include "material/texture.h"
#include "material/material.h"
#include "sound/sound.h"
#include "menu.h"
#include "CaxidyEngine/profile.h"
#include "mainmenu.h"
#include "collection/materialcollection.h"
#include "collection/soundcollection.h"
#include <string>

using namespace std;

class Text;
class MeshCollection;
class InventoryMenu : public Menu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        InventoryMenu();

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

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will be clear the inventory of items
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void clearInventory();

    protected:
        NodeSceneGraph * confirmInterface;   // NodeSceneGraph of the confirm interface
        vec3f initialPosition;               // Initial position of the menu
        Matrix4f * selectedPosition;         // The position of the current selected item
        Material * materialBack;             // The texture in background
        Material * confirmMaterial;          // Material of the confirm interface
        Material * materialCurrentMaterial;  // material of the image profile of the selected item
        Material * materialEquipped;         // Material of the equipped equipment
        MaterialCollection * materialCollect;// Material collection
        Sound * openSound;                   // Sound for open an option
        Sound * moveSound;                   // Sound for movement

        vec3f distItem;                      // Distance between items
        int currentItemX;                    // Current X cell of the inventory
        int currentItemY;                    // Current Y cell of the inventory

        bool isConfirming;                   // Flag to know if the user is confirming a removement of a item or not

    private:

};

#endif // INVENTORYMENU_H
