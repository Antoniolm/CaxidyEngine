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

#ifndef INVENTORYMENUGAME_H
#define INVENTORYMENUGAME_H

#include "GraphicEngine/menu/inventorymenu.h"
#include "GraphicEngine/text.h"

class InventoryMenuGame : public InventoryMenu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        InventoryMenuGame();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        InventoryMenuGame(vec3f initPos,vec3f dItem,string fileName);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~InventoryMenuGame();

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
        *    It will set the inventory content
        *    @param equipVec-> vector with the equipment of the inventory
        *    @param posVec-> vector with the position of each equipment in the inventory
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setInventory(const vector<Equipment*> & equipVec, const vector<vec2f> & posVec);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add an equipment in the inventory
        *    @param aEquip-> the equipment that will be added
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool addEquip(Equipment * aEquip);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the inventory
        *    \return Inventory *
        */
        //////////////////////////////////////////////////////////////////////////
        Inventory * getInventory();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will be clear the inventory of items
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void clearInventory();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the equipped equipment of that type
        *    @param aType-> type of the equipment
        *    \return Equipment *
        */
        //////////////////////////////////////////////////////////////////////////
        Equipment * getEquippetItem(int aType);
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will be initialize the information of the items
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initInfoItem();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will be create the matrix of items
        *    \return NodeSceneGraph *
        */
        //////////////////////////////////////////////////////////////////////////
        NodeSceneGraph * createMatrixItems();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will be change the selected items
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void changeSelectedItems();

        //Selected items
        Text * damageItemText;               // Damage text of the selected item
        Text * armourItemText;               // Armour text of the selected item
        Text * lifeItemText;                 // Life text of the selected item
        Text * nameItemText;                 // Name text of the selected item

        //Info of the hero
        Text * levelText;                    // Level text of the hero
        Text * lifeText;                     // Life text of the hero
        Text * damageText;                   // Damage text of the hero
        Text * armourText;                   // Armour text of the hero

        int currentLevel;                    // Current level of the hero
        int currentLife;                     // Current life of the hero
        int currentDmg;                      // Current damage of the hero
        int currentArmour;                   // Current armour of the hero
};

#endif // INVENTORYMENUGAME_H
