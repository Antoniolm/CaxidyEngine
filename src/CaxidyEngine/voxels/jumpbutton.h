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

#ifndef JUMPBUTTON_H
#define JUMPBUTTON_H

#include "object3d.h"
#include "nodescenegraph.h"
#include "matrix/matrix4f.h"
#include "matrix/matrix4fdynamic.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "collection/soundcollection.h"
#include "rapidjson/document.h"

using namespace rapidjson;

class JumpButton : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        */
        //////////////////////////////////////////////////////////////////////////
        JumpButton();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param buttonFeatures -> the value json that contain all the information of the jump button object
        */
        //////////////////////////////////////////////////////////////////////////
        JumpButton(const Value & buttonFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~JumpButton();

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
        *    It will return if the jump button is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();
    protected:
        NodeSceneGraph * root;      // Root of the object
        vec3f velocity;             // Initial velocity of the jump
        vec3f acceleration;         // Initial acceleration of the jump
        Matrix4f * transActivate;   // Matrix 4x4 for the activaction of the respawn voxel
        ScriptLMD * animationUp;    // Up animation of the respawn voxel
        ScriptLMD * animationDown;  // Down animation of the respawn voxel
        bool activated;             // Flag to activation
        bool jumping;               // Flag to know if the hero is jumping
        Sound * activatedButton;    // Sound for its activation
    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of the jump button
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

};

#endif // JUMPBUTTON_H
