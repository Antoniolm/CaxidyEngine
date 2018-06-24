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

#ifndef MELEEENEMY_H
#define MELEEENEMY_H

#include "enemy.h"
#include "../resources/lib/rapidjson/document.h"
#include "../ia/iameleeenemy.h"
#include "../enemylist.h"
#include "../equipment.h"

using namespace rapidjson;

class MeleeEnemy : public Enemy
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters
        *   @param enemyFeatures -> the value json that contain all the information of the enemy
        */
        //////////////////////////////////////////////////////////////////////////
        MeleeEnemy(const Value & enemyFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MeleeEnemy();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the animation of our melee Enemy
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initAnimation();

};

#endif // MELEEENEMY_H
