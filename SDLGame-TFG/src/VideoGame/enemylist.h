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


#ifndef ENEMYLIST_H
#define ENEMYLIST_H


#include "avatar/npc.h"
#include "avatar/hero.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/object3d.h"
#include "../../lib/rapidjson/document.h"

#include <vector>

using namespace rapidjson;
class Enemy;
class RangedEnemy;
class MeleeEnemy;
class EnemyList : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        EnemyList();

        //////////////////////////////////////////////////////////////////////////
        /** Constructor
        *    \param enemiesFeatures -> It is a value of json that contain all the
        *                              information of our new enemy
        */
        //////////////////////////////////////////////////////////////////////////
        EnemyList(const Value & enemiesFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~EnemyList();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will add a new enemy on the list
        *    \param enemy -> The new element that will added on our list
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(Enemy * enemy);

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
        *    The method will return the enemies of our list
        *    \return vector<Enemy *> &
        */
        //////////////////////////////////////////////////////////////////////////
        vector<Enemy *> & getEnemies();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the enemy in the index position of our vector
        *    @param index -> The position of the enemy in our vector
        *    \return enemy *
        */
        //////////////////////////////////////////////////////////////////////////
        Enemy * getEnemy(int index);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will return the number of enemies of our vector
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getNumEnemy();
    protected:

    private:
        vector<Enemy *> enemies;    // Vector of enemies
};

#endif // ENEMYLIST_H
