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

#ifndef MOVABLEVOXEL_H
#define MOVABLEVOXEL_H

#include "../GraphicEngine/objectscene.h"
#include "respawnvoxel.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/matrix/matrix4fdynamic.h"
#include "../GraphicEngine/matrix/acceleratedmovement.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/collection/materialcollection.h"
#include "../GraphicEngine/collection/soundcollection.h"
#include "../lib/rapidjson/document.h"
#include "avatar/enemy.h"
#include "enemylist.h"

using namespace rapidjson;

class RespawnVoxel;
class MovableVoxel : public ObjectScene
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param movableFeatures -> the value json that contain all the information of our movable voxel object
        *    @param ID -> ID of the movable voxel
        */
        //////////////////////////////////////////////////////////////////////////
        MovableVoxel(const Value & movableFeatures,const vector<RespawnVoxel*> & respawns, int id);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MovableVoxel();

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
        *    It will return if the movable voxel is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of the movable voxel
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Check the enemies that can be obstruct the movable voxel movement
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool checkEnemies(vec3f newPos,vector<Enemy *> &enemies);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will create the gravity for the movable voxel
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene * gravity(GameState & gameState);

        vec4f defaultPosition;      // The initial position of the movable voxel
        RespawnVoxel * respawn;     // Respawn Voxel linked with the Movable voxel
        Matrix4f * transActivate;   // Matrix 4x4 for the activaction of the movable voxel
        ScriptLMD * animation;      // animation of the movable voxel
        float delayTime;            // Delay time
        bool activated;             // Flag to activation
        bool isFalling;             // Flag to know if is falling or not
        avatarDirection currentDir; // Current direction of the movement
        AcceleratedMovement * acceleratedMove;  // Accelerated movement
        Sound * activatedVoxel;     // Sound for its activation
        Sound * fallSound;     // Sound for its falling
        int voxelID;                // Id of the movable voxel
};

#endif // MOVABLEVOXEL_H
