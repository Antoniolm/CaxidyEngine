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

#ifndef PROJECTILESYSTEM_H
#define PROJECTILESYSTEM_H

#include "projectile.h"
#include "CaxidyEngine/nodescenegraph.h"
#include <string>
#include "CaxidyEngine/nodescenegraph.h"
#include "CaxidyEngine/rootmap.h"
#include <list>
#include "rapidjson/document.h"


class Projectile;
class ProjectileSystem : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    Constructor
        *    @param aRadio -> the radio activity of our projectile Sys
        *    @param aPos -> the initial position of our projectile Sys
        *    @param aVeloc -> the velocity of movement of our projectile
        *    @param aDir -> the direction of our projectile Sys
        *    @param aDelay -> the delay between projectile creation
        *    @param aMesh -> the mesh that will visualize our projectile
        *    @param aMterial -> the material that will have our projectile
        */
        //////////////////////////////////////////////////////////////////////////
        ProjectileSystem(vec3f aRadio,vec3f aPos,vec3f aVeloc,int aDir,float aDelay,string aMesh,string aMaterial);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor with json
        *    @param projectileSys -> the value json that contain all the information
        *                            of our projectile object
        */
        //////////////////////////////////////////////////////////////////////////
        ProjectileSystem(const rapidjson::Value & projectileSys);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ProjectileSystem();

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
        *    It will set all the parameters of our projectile system object
        *    @param aRadio -> the radio activity of our projectile Sys
        *    @param aPos -> the initial position of our projectile Sys
        *    @param aVeloc -> the velocity of movement of our projectile
        *    @param aDir -> the direction of our projectile Sys
        *    @param aDelay -> the delay between projectile creation
        *    @param aMesh -> the mesh that will visualize our projectile
        *    @param aMterial -> the material that will have our projectile
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(vec3f aRadio,vec3f aPos,vec3f aVeloc,int aDir,float aDelay,string aMesh,string aMaterial);


        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the lived arrow of our system
        *    \return list<Projectile *> &
        */
        //////////////////////////////////////////////////////////////////////////
        list<Projectile *> & getArrows();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the radio of our system
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getRadio();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the position of our system
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the velocity of our system
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getVelocity();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the direction ouf the arrow of our system
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getDir();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the delay between projectiles of our system
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getDelay();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the mesh of our system
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getMesh();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the material of our system
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        string getMaterial();

    protected:

    private:
        list<Projectile *> projectiles; // List of projectiles
        vec3f radioActivity;            // Radio activity of the projectile system
        vec3f position;                 // Initial position of the projectiles
        vec3f velocity;                 // Velocity of the projectiles
        avatarDirection direction;      // direction of the projectiles
        float projectileDelay;          // time delay
        float timeBWprojectile;         // time between one projectile and another
        string mesh;                    // Mesh for the projectiles
        string material;                // Material for the projectiles
};

#endif // PROJECTILESYSTEM_H
