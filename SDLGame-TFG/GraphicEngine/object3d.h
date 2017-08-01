// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David López Machado
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

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "context/context.h"
#include "matrix/structdata.h"
#include "controller/controller.h"
#include "controller/keyboardcontroller.h"
#include "controller/controllermanager.h"
#include "SDL2/SDL.h"

class Context;
class RootMap;
class GameState;

struct BoundingBox{
    vec3f maxValue;
    vec3f minValue;

    bool operator<(BoundingBox aBounding){
        bool result=false;

        if(maxValue<aBounding.maxValue && minValue>aBounding.minValue)
            result=true;

        return result;
    }
};

class Object3D
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Object3D();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Object3D();

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
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual BoundingBox getBoundingBox();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void obtainPosition(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will get the position of our object3D
        *   \return vec4f with the mesh position
        */
        //////////////////////////////////////////////////////////////////////////
        vec4f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will remove a link of our object3D
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void removeLink();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will add a link in our object3D
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addLink();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will get the position of our object3D
        *   \return int -> Number of link of our object
        */
        //////////////////////////////////////////////////////////////////////////
        int getCountLink();

    protected:
        float currentTime;          // Time of the application
        vec4f position;             // Position of the object
        int countLink;              // Number of links of the object
        BoundingBox boundingBox;    // Bounding box of the object

    private:


};

#endif // OBJECT3D_H
