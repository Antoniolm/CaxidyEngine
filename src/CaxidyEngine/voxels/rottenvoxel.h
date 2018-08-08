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

#ifndef ROTTENVOXEL_H
#define ROTTENVOXEL_H

#include "CaxidyEngine/objectscene.h"
#include "CaxidyEngine/nodescenegraph.h"
#include "matrix/matrix4f.h"
#include "matrix/matrix4fdynamic.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "collection/soundcollection.h"
#include "rapidjson/document.h"

namespace CaxidyEngine {

class RottenVoxel : public ObjectScene
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param rottenFeatures -> the value json that contain all the information of the rotten voxel object
        *   @param ID -> ID of the rotten voxel
        */
        //////////////////////////////////////////////////////////////////////////
        RottenVoxel(const rapidjson::Value & rottenFeatures, int id);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~RottenVoxel();

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
        *    It will return if the rotten voxel is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the rotten voxel was disappear or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isDisappear();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return if the object will be deleted or not
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual bool isDeleting();

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of the rotten voxel
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        Matrix4f * transActivate;   // Matrix 4x4 for the activaction of the rotten voxel
        ScriptLMD * animation;      // Up animation of the rotten voxel
        float delayTime;            // Delay time
        bool activated;             // Flag to activation
        bool disappear;             // Flag to know if the rotten voxel was disappear
        Sound * activatedVoxel;     // Sound for its activation
        int voxelID;                // Id of the rotten voxel
};

} // CaxidyEngine

#endif // ROTTENVOXEL_H
