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

#ifndef AVATAR_H
#define AVATAR_H

#include "../../GraphicEngine/object3d.h"
#include "../../GraphicEngine/context/context.h"
#include "../../GraphicEngine/nodescenegraph.h"

enum avatarDirection
{
	FORWARD,       //0
	FOR_LEFTWARD,  //1
	LEFTWARD,      //2
	BACK_LEFTWARD, //3
	BACKWARD,      //4
	BACK_RIGHTWARD,//5
	RIGHTWARD,     //6
	FOR_RIGHTWARD  //7
};

class Avatar: public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Avatar();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param vis -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & vis) =0 ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState) = 0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set the life of an avatar
        *    @param aLife -> The new value of our life
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setLife(float aLife);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will set the maxlife of an avatar
        *    @param aMaxLife -> The new value of our max life
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setMaxLife(float aMaxLife);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the life of an avatar
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getLife();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the maximum life of an avatar
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getMaxLife();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add the value to our life
        *    @param value -> The value that the avatar will add to his life
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addLife(float value);

    protected:
        NodeSceneGraph * root;  // Root of the avatar
        float life;             // Current life of the avatar
        float maxLife;          // Max life of the avatar
    private:

};

#endif // AVATAR_H
