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

#ifndef PARTICLE_H
#define PARTICLE_H

#include "object3d.h"
#include "mesh/mesh.h"
#include "context/context.h"
#include "rootmap.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include <stdlib.h>

class NodeSceneGraph;
class Particle : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Particle();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters */
        //////////////////////////////////////////////////////////////////////////
        Particle(Material * material,vec3f aScale,vec3f minPos,vec3f maxPos,vec3f aVelocity,float minTime,float maxTime);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Particle();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

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
        *    It will return the remaining time of our particle
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getRemainingTime();
    protected:

    private:
        vec3f position;         // Current position of the particle
        vec3f velocity;         // Current velocity of the particle
        NodeSceneGraph *root;   // Root of the scene graph of particle
        Matrix4f * transMatrix; // Matrix 4x4 with the transformation in the particle
        float remainingTime;    // Time of life of the particle
};

#endif // PARTICLE_H
