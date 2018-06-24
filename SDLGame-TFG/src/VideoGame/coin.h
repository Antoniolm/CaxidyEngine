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

#ifndef COIN_H
#define COIN_H

#include "item.h"
#include "../GraphicEngine/object3d.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/material/material.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/matrix/matrix4fdynamic.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/collection/soundcollection.h"
#include "../GraphicEngine/matrix/axisrotation.h"
#include "../GraphicEngine/sound/sound.h"

class Coin : public Item
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Coin(const Value & coinFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Coin();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param vis -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);

    protected:

    private:
};

#endif // COIN_H
