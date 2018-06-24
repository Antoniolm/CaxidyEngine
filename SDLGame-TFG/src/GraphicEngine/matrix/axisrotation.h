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

#ifndef AXISROTATION_H
#define AXISROTATION_H

#include "matrix4fdynamic.h"
#include "structdata.h"

class AxisRotation : public Matrix4fDynamic
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        AxisRotation();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor
        *   @param anAVelocity -> the angular velocity of our axis rotation
        *                          (Grade per second)
        *   @param x -> axis X
        *   @param y -> axis Y
        *   @param z -> axis Z
        */
        //////////////////////////////////////////////////////////////////////////
        AxisRotation(float anAVelocity,float x,float y,float z);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~AxisRotation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value of some parameters in the object
        *   @param anAVelocity -> Grade per second
        *   @param x -> axis X
        *   @param y -> axis Y
        *   @param z -> axis Z
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(float anAVelocity,float x,float y,float z);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the Matrix4xf. That change need the
        *    current time in our application
        *    @param time -> the time between the lastTime and the currentTime
        *    \return the new state of the matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        virtual Matrix4f & updateState(float time);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will reset to the initial state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void resetState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the angular velocity of our axisrotation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getAngularVelocity();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the axis of our axisrotation
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getAxis();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the current grade of our axisrotation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getCurrentGrade();

    protected:

    private:
        float angularVelocity;  // Angular velocity of the movement
        vec3f axis;             // Direction of the movement
        float currentGrade;     // Current grade of the movement
};

#endif // AXISROTATION_H
