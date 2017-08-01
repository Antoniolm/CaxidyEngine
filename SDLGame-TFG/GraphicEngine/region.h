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

#ifndef REGION_H
#define REGION_H

#include "matrix/structdata.h"

class GameState;
class Region
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Region();

        /////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState)=0;

        /////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if our hero was in the region or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();

        /////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the position of our region
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f value);

        /////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the radioactivity of our region
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setRadioActivity(vec3f value);

        /////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the position of our region
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        /////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the radioactivity of our region
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getRadioActivity();

    protected:
        vec3f position;     // Position of the region
        vec3f radioActivity;// Radio of activity of the region
        bool activated;     // Flag of the region was activated

    private:

};

#endif // REGION_H
