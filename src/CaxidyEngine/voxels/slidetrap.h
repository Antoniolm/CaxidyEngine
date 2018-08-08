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

#ifndef SLIDETRAP_H
#define SLIDETRAP_H

#include "CaxidyEngine/objectscene.h"
#include "CaxidyEngine/nodescenegraph.h"
#include "matrix/matrix4f.h"
#include "matrix/matrix4fdynamic.h"
#include "matrix/acceleratedmovement.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "collection/soundcollection.h"
#include "rapidjson/document.h"
#include "avatar/avatar.h"

namespace CaxidyEngine {

class SlideTrap : public ObjectScene
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param slideFeatures -> the value json that contain all the information of the slide trap object
        *    @param ID -> ID of the slide trap
        */
        //////////////////////////////////////////////////////////////////////////
        SlideTrap(const rapidjson::Value & slideFeatures, int id);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~SlideTrap();

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

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of the slide trap
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        Matrix4f * transActivate;   // Matrix 4x4 for the activaction of the slide trap
        ScriptLMD * animation;      // animation of the slide trap
        float delayTime;            // Delay time
        float timeState;            // Time between states
        bool activated;             // Flag to activation
        bool soundActivation;       // Flag to activate sound
        avatarDirection currentDir; // Current direction of the movement
        Sound * activatedVoxel;     // Sound for its activation
        int voxelID;                // Id of the slide trap

    protected:

    private:
};

} // CaxidyEngine

#endif // SLIDETRAP_H
