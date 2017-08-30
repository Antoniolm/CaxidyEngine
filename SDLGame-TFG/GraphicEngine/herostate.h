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

#ifndef HEROSTATE_H
#define HEROSTATE_H

#include "object3d.h"
#include "text.h"
#include "collection/materialcollection.h"
#include "collection/meshcollection.h"
#include <sstream>

class HeroState : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        HeroState();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~HeroState();

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
    protected:

    private:
        NodeSceneGraph * root;          // Root of the scene graph of hero state
        Text * coinText;                // Text that show the coin score
        Matrix4f * positionState;       // Matrix 4x4 with the position of the object
        Matrix4f * scaleLife;           // Matrix 4x4 with the scale of the life

        int currentLife;                // Current life of the hero
        int currentCoin;                // Current coins of the hero
        bool visibleState;              // Visible state of the hero information
};

#endif // HEROSTATE_H
