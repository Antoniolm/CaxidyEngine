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

#ifndef SPEAKINGSKETCH_H
#define SPEAKINGSKETCH_H

#include "object3d.h"
#include "nodescenegraph.h"
#include "./matrix/matrix4f.h"
#include "./matrix/matrix4fdynamic.h"
#include "./collection/meshcollection.h"
#include "./collection/materialcollection.h"

class SpeakingSketch : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        SpeakingSketch(vec3f aPos, string material);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~SpeakingSketch();

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
        *    The method will activate or deactivate the sketch object
        *    @param value -> The new value of its activation
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setActivate(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return if the speakingSketch is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();

    protected:

    private:
        NodeSceneGraph * root;      // Root of the object
        Matrix4f * transActivate;   // Matrix 4x4 for the activaction of the speaking sketch
        ScriptLMD * animationUp;    // Up animation of the speaking sketch
        ScriptLMD * animationDown;  // Down animation of the speaking sketch
        vec3f initialPosition;
        bool activated;             // Flag to activation
        bool visibleState;
};

#endif // SPEAKINGSKETCH_H
