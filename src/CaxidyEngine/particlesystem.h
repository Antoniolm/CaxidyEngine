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

#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "object3d.h"
#include "nodescenegraph.h"
#include "context/context.h"
#include "collection/materialcollection.h"
#include "rootmap.h"
#include <list>
#include "particle.h"
#include <string>
#include "rapidjson/document.h"

namespace CaxidyEngine {
    
class Particle;
class ParticleSystem : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ParticleSystem();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        ParticleSystem(int numParticle, std::string aMaterial,vec3f aScale,vec3f aMinPos,vec3f aMaxPos,vec3f aVelocity,float aMinTime,float aMaxTime);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with json*/
        //////////////////////////////////////////////////////////////////////////
        ParticleSystem(const rapidjson::Value & particleSys);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ParticleSystem();

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
        *    The method will set some parameters of our particle system
        *    @param numParticle
        *    @param aMaterial
        *    @param aScale
        *    @param aMinPos
        *    @param aMaxPos
        *    @param aVelocity
        *    @param aMinTime
        *    @param aMaxTime
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(int numParticle, std::string aMaterial,vec3f aScale,vec3f aMinPos,vec3f aMaxPos,vec3f aVelocity,float aMinTime,float aMaxTime);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the number of particle of our particle system
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getNumParticle();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the material of our particle system
        *    \return material *
        */
        //////////////////////////////////////////////////////////////////////////
        Material * getMaterial();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the scale of our particle
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getScale();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get max position of our particle
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getMaxPos();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get min position of our particle
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getMinPos();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the velocity of our particle
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getVelocity();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the min time life of our particle
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getMinTime();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the max time life of our particle
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getMaxTime();

    protected:

    private:
        std::list<Particle *> particles; // List of particles in the system
        int nParticles;             // Total number of particles that the system has to have with life
        int currentParticles;       // Number of live particles in the system
        vec3f maxPos;               // Max position for the particles
        vec3f minPos;               // Min position for the particles
        vec3f velocity;             // Velocity for the particles
        vec3f scale;                // Scale of the particles
        float minTime;              // Min time of life for the particles
        float maxTime;              // Max time of life for the particles
        Material * material;        // Material applied in the particles
};

} // CaxidyEngine 

#endif // PARTICLESYSTEM_H
