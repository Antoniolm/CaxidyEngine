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

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "equipment.h"

using namespace std;

class Inventory
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Inventory();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Inventory();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the number of items in the X axis
        *    \return unsigned
        */
        //////////////////////////////////////////////////////////////////////////
        unsigned getSizeX();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the number of items in the Y axis
        *    \return unsigned
        */
        //////////////////////////////////////////////////////////////////////////
        unsigned getSizeY();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add an item to the inventory
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addItem(int x,int y,Equipment * aEquip);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will remove an item to the inventory
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool removeItem(int x,int y);

        Equipment * getItem(int x,int y);

        vector<Equipment *> & getItems();

        int getNumItems();

        pair<int,int> emptySlot();

        bool equipItem(int x,int y,bool value);

        bool unEquipItem(EquipmentType typeEquip);

    protected:

    private:


        static const unsigned sizeX = 6;
        static const unsigned sizeY = 3;

        vector< vector<Equipment *> > items;

};

#endif // INVENTORY_H
