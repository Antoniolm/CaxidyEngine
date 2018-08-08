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

#ifndef OBJECTSCENE_H
#define OBJECTSCENE_H

#include "object3d.h"
#include "matrix/matrix4f.h"
#include "collection/materialcollection.h"
#include "matrix/structdata.h"


class GameState;

class ObjectScene : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ObjectScene(Object3D * aObject3,bool shadow=false,float aDamage=0.0);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ObjectScene();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & vis);

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
        *    It will set the damage that the object do to an avatar
        *    @param value -> the damage that the object will do in an avatar
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDamage(float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the shadow is enable or disable in this object
        *    @param value -> will be tru if the object will have shadow in the scene
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setShadow(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the position of the object.
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the boundingBox of the object.
        *    \return boundingBox
        */
        //////////////////////////////////////////////////////////////////////////
        BoundingBox getBoundingBox();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the damage that the object do to an avatar
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will get if the shadow is enable or not in the object
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isShadow();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will get the material type of our objectScene
        *    \return MaterialIndex
        */
        //////////////////////////////////////////////////////////////////////////
        MaterialIndex getMaterialIndex();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the position of our objectScene
        *    @param vis -> the context of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void obtainPosition(Context vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return if the object will be deleted or not
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual bool isDeleting();

    protected:
        vec4f position;     // Position of the object scene
        Object3D * object;  // Object of the object scene
        Matrix4f matrix;    // Matrix 4x4 with the transformation in the object
        MaterialIndex index;// Material index of the object
        bool hasShadow;     // Flag to know if the object has shadow
        float damage;       // Damage that the object do to an avatar
    private:

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will generate the next boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void generateBoundingbox();

};

#endif // OBJECTSCENE_H
