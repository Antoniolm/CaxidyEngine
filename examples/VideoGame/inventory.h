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

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>
#include "equipment.h"

using namespace std;
class Equipment;
class Inventory
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Inventory(int tamX,int tamY);

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
        *    It will add an item in the inventory
        *    @param x -> the x position of the item in the inventory
        *    @param y -> the y position of the item in the inventory
        *    @param aEquip -> the equipment that will be added to the inventory
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addItem(int x,int y,Equipment * aEquip);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will remove an item of the inventory
        *    @param x -> the x position of the item in the inventory
        *    @param y -> the y position of the item in the inventory
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool removeItem(int x,int y);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return an item of the inventory
        *    @param x -> the x position of the item in the inventory
        *    @param y -> the y position of the item in the inventory
        *    \return equipment *
        */
        //////////////////////////////////////////////////////////////////////////
        Equipment * getItem(int x,int y);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return all the items in the inventory
        *    \return vector<Equipment *> &
        */
        //////////////////////////////////////////////////////////////////////////
        vector<Equipment *> & getItems();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the number of items in the inventory
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getNumItems();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if a cell in the inventory is empty or not
        *    @param x -> the x position of the item in the inventory
        *    @param y -> the y position of the item in the inventory
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isEmpty(int x,int y);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the first cell empty in the inventory
        *    \return pair<int,int> -> first - x position , second - y position
        */
        //////////////////////////////////////////////////////////////////////////
        pair<int,int> emptySlot();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will equip an item of the inventory
        *    @param x -> the x position of the item in the inventory
        *    @param y -> the y position of the item in the inventory
        *    \return bool -> if the item was equipped or not
        */
        //////////////////////////////////////////////////////////////////////////
        bool equipItem(int x,int y);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will unequip a type of item in the inventory
        *    @param typeEquip-> the tpye of the item that will be unequipped
        *    \return bool -> if the item was unequipped or not
        */
        //////////////////////////////////////////////////////////////////////////
        bool unequipItem(int typeEquip);

    protected:

    private:


        unsigned sizeX;                       //The number of items in the X axis of the inventory
        unsigned sizeY;                       //The number of items in the Y axis of the inventory

        vector< vector<Equipment *> > items;  //The matrix of items
        vector< Equipment * > auxItems;

};

#endif // INVENTORY_H
