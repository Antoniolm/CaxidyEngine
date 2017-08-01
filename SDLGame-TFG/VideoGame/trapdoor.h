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

#ifndef TRAPDOOR_H
#define TRAPDOOR_H

#include "../GraphicEngine/object3d.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/matrix/matrix4fdynamic.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/collection/materialcollection.h"
#include "../GraphicEngine/collection/soundcollection.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class TrapDoor : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param trapDoorFeatures -> the value json that contain all the information of our trapDoor object
        */
        //////////////////////////////////////////////////////////////////////////
        TrapDoor(const Value & trapDoorFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~TrapDoor();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
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

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the trap is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();

    protected:

    private:
        NodeSceneGraph * root;      // Root of the object

};

#endif // TRAPDOOR_H
