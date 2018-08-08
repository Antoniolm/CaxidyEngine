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

#ifndef OSCILLATEROTATION_H
#define OSCILLATEROTATION_H

#include "matrix4fdynamic.h"
#include "SDL2/SDL.h"

namespace CaxidyEngine {
    
class OscillateRotation : public Matrix4fDynamic
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        OscillateRotation();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters
        *   \param incre -> Initial increment or decrement grade
        *   \param maxG -> max Grade in our movement
        *   \param minG -> min Grade in our movement
        *   \param initG -> Initial Grade in our movement
        *   \param velocity -> Grade per second
        *   \param dir -> axis of movement
        *   \param loop -> number of loop that the move do( -1 = infinity loop)
        */
        //////////////////////////////////////////////////////////////////////////
        OscillateRotation(bool incre,float maxG,float minG,float initG,float velocity,vec3f dir,int aLoop);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~OscillateRotation();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value of some parameters in the object
        *   \param incre -> Initial increment or decrement grade
        *   \param maxG -> max Grade in our movement
        *   \param minG -> min Grade in our movement
        *   \param initG -> Initial Grade in our movement
        *   \param velocity -> Grade per second
        *   \param dir -> axis of movement
        *   \param loop -> number of loop that the move do( -1 = infinity loop)
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(bool incre,float maxG,float minG,float initG,float velocity,vec3f dir,int aLoop);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the Matrix4xf. That change need the
        *    current time in our application
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
        virtual void resetState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the max grade of our oscillaterotation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getMaxGrade();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the min grade of our oscillaterotation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getMinGrade();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the initial grade of our oscillaterotation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getInitialGrade();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the current grade of our oscillaterotation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getCurrentGrade();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the angular velocity of our oscillaterotation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getAngularVelocity();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the increment of our oscillaterotation
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool getIncrement();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the loop of our oscillaterotation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        int getLoop();

    protected:

    private:
        vec3f direction;        // Direction of the movement
        float maxGrade;         // Max grade of the movement
        float minGrade;         // Min grade of the movement
        float initialGrade;     // Initial grade of the movement
        float currentGrade;     // Current grade of the movement
        float angularVelocity;  // Angular velocity of the movement
        float currentTime;      // Current time of the application
        bool increment;         // Flag to detect the increment/decrement
        int loop;               // Number of loop of the movement
        int currentLoop;        // Current loop

};

} // CaxidyEngine

#endif // OSCILLATEROTATION_H
