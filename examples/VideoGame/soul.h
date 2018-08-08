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

#ifndef SOUL_H
#define SOUL_H

#include "CaxidyEngine/object3d.h"
#include "CaxidyEngine/avatar/avatar.h"
#include "CaxidyEngine/nodescenegraph.h"
#include "CaxidyEngine/matrix/matrix4f.h"
#include "CaxidyEngine/matrix/matrix4fdynamic.h"
#include "CaxidyEngine/collection/meshcollection.h"
#include "CaxidyEngine/collection/materialcollection.h"
#include "CaxidyEngine/matrix/axisrotation.h"
#include "rapidjson/document.h"

using namespace rapidjson;

class Soul : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *    @param soulFeatures -> the value json that contain all the information of our soul object
        */
        //////////////////////////////////////////////////////////////////////////
        Soul(const Value & soulFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Soul();

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
        *    It will set the position of our soul
        *    @param value -> the new value of our position
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the soul is in the hand of our hero or not
        *    @param  value -> the new value of our boolean
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setInCarrier(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the soul is in the hand of our hero
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool getInCarrier();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the soul is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool getActivate();

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will calculate the position of our soul when is taken for a hero
        *    @param posHero -> position of our hero
        *    @param direction -> direction of our hero
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void calculatePosition(vec3f posHero,avatarDirection direction);

        NodeSceneGraph * root;      // Root of the object
        Matrix4f * transMatrix;     // Matrix for the position
        Matrix4f * animationMatrix; // Animation of the soul
        AxisRotation * rotation;    // Rotation movement
        bool activated;             // Flag of activation
        bool inCarrier;             // Flag to know if the soul is inside a soul carrier
};

#endif // SOUL_H
