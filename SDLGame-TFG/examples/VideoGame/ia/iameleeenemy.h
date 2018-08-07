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

#ifndef IAMELEEENEMY_H
#define IAMELEEENEMY_H

#include "iaenemy.h"
#include "VideoGame/enemylist.h"

class IAMeleeEnemy : public IAEnemy
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        IAMeleeEnemy();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~IAMeleeEnemy();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will calculate the next position and direction of our enemy
        *    \return pair<avatarDirection,vec3f>
        */
        //////////////////////////////////////////////////////////////////////////
        pair<avatarDirection,vec3f> nextPosition(vec3f posEnemy,vec3f posHero,EnemyList * enemies);

    protected:

    private:
};

#endif // IAMELEEENEMY_H
