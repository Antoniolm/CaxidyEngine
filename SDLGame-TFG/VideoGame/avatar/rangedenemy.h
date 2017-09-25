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

#ifndef RANGEDENEMY_H
#define RANGEDENEMY_H

#include "enemy.h"
#include "../lib/rapidjson/document.h"
#include "../GraphicEngine/ia/iarangedenemy.h"
#include "../GraphicEngine/ia/iameleeenemy.h"
#include "../projectile.h"
#include "../equipment.h"
#include <vector>

using namespace rapidjson;

class RangedEnemy : public Enemy
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        RangedEnemy();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters
        *   @param enemyFeatures -> the value json that contain all the information of the enemy
        */
        //////////////////////////////////////////////////////////////////////////
        RangedEnemy(const Value & enemyFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~RangedEnemy();

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
        *    It will create a projectile
        *    @param damage -> the damage of the created projectile
        *    \return Projectile *
        */
        //////////////////////////////////////////////////////////////////////////
        Projectile * createProjectile(float damage);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of our ranged enemy
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

        vector<Projectile *> projectiles;   // Vector of projectiles
        IAEnemy * secondIA;                 // Second Ia of the enemy
};

#endif // RANGEDENEMY_H
