// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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

#ifndef MATE_H
#define MATE_H

#include "../../GraphicEngine/object3d.h"
#include "../../GraphicEngine/nodescenegraph.h"
#include "../../GraphicEngine/material/material.h"
#include "../../GraphicEngine/matrix/matrix4f.h"
#include "../../GraphicEngine/matrix/matrix4fdynamic.h"
#include "../../GraphicEngine/collection/meshcollection.h"
#include "../../GraphicEngine/collection/soundcollection.h"
#include "../../GraphicEngine/matrix/axisrotation.h"
#include "../../GraphicEngine/sound/sound.h"
#include "../../GraphicEngine/text.h"
#include "../../GraphicEngine/animation/animationlist.h"
#include "../../../lib/rapidjson/document.h"
#include "../../GraphicEngine/avatar/avatar.h"

using namespace rapidjson;

class Mate : public Avatar
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor
        *    @param aPosition -> the initial position of our mate
        */
        //////////////////////////////////////////////////////////////////////////
        Mate(const Value & mateFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Mate();

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
        *    It will set a new message for our text
        *    \param message -> it is the new message that our text will show
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDialog(string message);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate the text of our hero
        *    @param value -> value indicate if the dialog will be enable or disable
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateDialog(bool value);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of our mate
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will give to our mate his next direction and position
        *    @param posHero -> the current position of our hero
        *    \return pair<avatarDirection,vec3f>
        */
        //////////////////////////////////////////////////////////////////////////
        pair<avatarDirection,vec3f> nextPosition(vec3f posHero);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will move our mate
        *    @param time -> the current time of our application
        *    @param aMove -> the new movement of our mate
        *    @param aDir -> the new direction of our mate
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void moveMate(float time,vec3f aMove,avatarDirection aDir);

        vector<Matrix4f *> moveMatrix;           // Vector of movement
        pair<avatarDirection,vec3f> currentMove; // Current move of the mate
        Matrix4f * moveAvatar;                   // Matrix 4x4 of movement of the mate
        avatarDirection direction;               // Direction of the mate
        ScriptLMD * animation;                   // Animation of the mate
        Text * currentText;                      // Current text of the mate
        bool textActivated;                      // Flag for the activation of the dialog
};

#endif // MATE_H
