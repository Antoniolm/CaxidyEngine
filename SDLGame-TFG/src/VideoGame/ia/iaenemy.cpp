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

#include "iaenemy.h"

IAEnemy::IAEnemy()
{
    //ctor
}

//**********************************************************************//

IAEnemy::~IAEnemy()
{
    //dtor
}

//**********************************************************************//

pair<avatarDirection,vec3f> IAEnemy::nextPosition(vec3f posEnemy,vec3f posHero,EnemyList * enemies){
    pair<avatarDirection,vec3f> result;
    return result;
}

//**********************************************************************//

vector<vec3f> IAEnemy::obtainPosEnemies(vector<Enemy *> enemies){
    vector<vec3f> posEnemies;

    for(unsigned i=0;i<enemies.size();i++){
        vec3f pos=enemies[i]->getPosition();
        if(enemies[i]->isActivate()){ //if the enemy is activate
            posEnemies.push_back(pos);
        }
    }
    return posEnemies;
}

//**********************************************************************//

bool IAEnemy::checkCollision(vector<vec3f> & posEnemies,vec3f currentEnemy){
    bool result=false;
    float distance;
    for(unsigned i=0;i<posEnemies.size();i++){
        distance=sqrt(pow(currentEnemy.x-posEnemies[i].x,2.0)+pow(currentEnemy.z-posEnemies[i].z,2.0));
        if(distance<0.5 && distance>0.21)
            result=true;
    }

    return result;
}

