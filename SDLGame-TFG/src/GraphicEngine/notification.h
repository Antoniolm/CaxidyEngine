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

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "object3d.h"
#include "context/context.h"
#include "nodescenegraph.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "../../resources/lib/rapidjson/document.h"
#include "gamestate.h"

using namespace rapidjson;

class Notification : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Notification(vec3f aPosition,vec3f aScale,float aVisibleTime,MaterialIndex material);

        //////////////////////////////////////////////////////////////////////////
        /** Json constructor */
        //////////////////////////////////////////////////////////////////////////
        Notification(const Value & notificationFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Notification();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the position of our notification
        *    @param value -> the new position of our notification
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the initial time of our notification
        *    @param value -> the initial time of our notification
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setInitialTime(float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the initial time of our notification
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getInitialTime();

    protected:

    private:
        NodeSceneGraph * root;  // Root of the scene graph of the notification
        Matrix4f * transNoti;   // Matrix 4x4 with the position of the notification
        float visibleTime;      // Time that notification will be activated
        float initialTime;      // The initial time of the notification
        bool activatedNoti;     // Flag of the notification was activated

};

#endif // NOTIFICATION_H
