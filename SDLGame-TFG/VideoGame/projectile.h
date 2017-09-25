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

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../GraphicEngine/avatar/avatar.h"
#include "../../GraphicEngine/avatar/avatarmove.h"
#include "../GraphicEngine/mesh/mesh.h"
#include "../GraphicEngine/material/material.h"
#include "../GraphicEngine/collection/meshcollection.h"
#include "../GraphicEngine/collection/materialcollection.h"
#include "../GraphicEngine/collection/soundcollection.h"
#include "../GraphicEngine/animation/scriptlmd.h"
#include "../GraphicEngine/context/context.h"
#include "../GraphicEngine/matrix/matrixscript.h"
#include "../GraphicEngine/rootmap.h"
#include "../GraphicEngine/matrix/matrix4f.h"
#include "../GraphicEngine/objectscene.h"
#include "../GraphicEngine/sound/sound.h"
#include "../GraphicEngine/text.h"
#include "avatar/enemy.h"
#include "enemylist.h"

#include <vector>


using namespace std;
class RootMap;
class Mesh;
class Material;
class Projectile : public AvatarMove
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    Constructor
        *    @param aPosition -> the initial position of our projectile
        *    @param aVelocity -> the velocity of movement of our projectile
        *    @param aDir -> the direction of our projectile
        *    @param aDamage -> the damage of our projectile
        *    @param mesh -> the mesh that will visualize our projectile
        *    @param material -> the material that will have our projectile
        */
        //////////////////////////////////////////////////////////////////////////
        Projectile(vec3f aPosition,vec3f aVelocity,avatarDirection aDir,float aDamage,string mesh,string material);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Projectile();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our scene
        *    @param cv -> the context of our visualization
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
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
        *    It will return if the projectile is live or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isLive();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the projectile is live or not
        *    @param value -> the new value of live
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setLive(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the damage of our projectile
        *    @param value -> the new value of damage
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDamage(float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the velocity of our projectile
        *    @param value -> the new value of velocity
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setVelocity(vec3f value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the damage of our projectile
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getDamage();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the velocity of our projectile
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getVelocity();

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will calculate the head of our projectile because this is needed this position
        *    to check the hits
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void calculateHead();

        Sound * soundHit;           // Sound of hit
        vec3f velocity;             // Velocity of the projectile
        vec3f projectileHead;       // Position of the head projectile
        bool live;                  // flag to know if the projectile is live or not
        float damage;               // Damage of the projectile
        Matrix4f * animationMatrix; // Animation of the projectile
        AxisRotation * rotation;    // Rotation movement

};

#endif // PROJECTILE_H
