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

#ifndef MOVABLEVOXELGAME_H
#define MOVABLEVOXELGAME_H

#include "CaxidyEngine/voxels/movablevoxel.h"
#include "rapidjson/document.h"

using namespace rapidjson;

class MovableVoxelGame : public MovableVoxel
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param movableFeatures -> the value json that contain all the information of our movable voxel object
        *    @param ID -> ID of the movable voxel
        */
        //////////////////////////////////////////////////////////////////////////
        MovableVoxelGame(const Value & movableFeatures,const vector<RespawnVoxel*> & respawns, int id);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MovableVoxelGame();

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

#endif // MOVABLEVOXELGAME_H
