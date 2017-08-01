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

#ifndef ITEMLIST_H
#define ITEMLIST_H

#include "../GraphicEngine/object3d.h"
#include "item.h"
#include <vector>
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class ItemList
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ItemList();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor
        *   @param coinFeatures -> the value json that contain all the information of our items object
        */
        //////////////////////////////////////////////////////////////////////////
        ItemList(const Value & coinFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ItemList();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new enemy on the list
        *    \param coin -> The new element that will added on our list
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(Item * coin);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the vector of item
        *    \return const vector<Item *> &
        */
        //////////////////////////////////////////////////////////////////////////
        const vector<Item *> & getItems();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the item in the index position
        *    @param index -> position of our item in our vector
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        Item * getItem(int index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the number of item in our vector
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getNumItem();
    protected:

    private:
        vector<Item *> items;   // Vector of items
};

#endif // ITEMLIST_H
