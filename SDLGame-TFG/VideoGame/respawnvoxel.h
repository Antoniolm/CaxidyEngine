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

#ifndef RESPAWNVOXEL_H
#define RESPAWNVOXEL_H

#include "../GraphicEngine/object3d.h"
#include "enemylist.h"
#include "avatar/enemy.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/matrix/matrix4fdynamic.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/collection/materialcollection.h"
#include "../GraphicEngine/collection/soundcollection.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class RespawnVoxel : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param respawnFeatures -> the value json that contain all the information of the RespawnVoxel object
        */
        //////////////////////////////////////////////////////////////////////////
        RespawnVoxel(const Value & respawnFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~RespawnVoxel();

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
        *    It will return if the respawn voxel is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of the respawn voxel
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        NodeSceneGraph * root;      // Root of the object
        Matrix4f * transActivate;   // Matrix 4x4 for the activaction of the spiketrap
        ScriptLMD * animation;      // Up animation of the spike trap
        bool activated;             // Flag to activation
        Sound * activatedButton;      // Sound for its activation
};

#endif // RESPAWNVOXEL_H
