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

#ifndef IAENEMY_H
#define IAENEMY_H

#include "matrix/structdata.h"
#include <iostream>
#include <math.h>
#include "../VideoGame/enemylist.h"
#include "../VideoGame/avatar/enemy.h"

using namespace std;

class IAEnemy
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        IAEnemy();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~IAEnemy();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will calculate the next position and direction of our enemy
        *    \return pair<avatarDirection,vec3f>
        */
        //////////////////////////////////////////////////////////////////////////
        virtual pair<avatarDirection,vec3f> nextPosition(vec3f posEnemy,vec3f posHero,EnemyList * enemies);

    protected:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the position of all activated enemies and put his position in
        *   a vector that will be return
        *    \return vector<vec3f>
        */
        //////////////////////////////////////////////////////////////////////////
        vector<vec3f> obtainPosEnemies(vector<Enemy *> enemies);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will check collision between an enemy and the other
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool checkCollision(vector<vec3f> & posEnemies,vec3f currentEnemy);

    private:
};

#endif // IAENEMY_H
