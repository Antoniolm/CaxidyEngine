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

#include "iarangedenemy.h"

IARangedEnemy::IARangedEnemy()
{
    //ctor
}

//**********************************************************************//

IARangedEnemy::~IARangedEnemy()
{
    //dtor
}

//**********************************************************************//

pair<avatarDirection,vec3f> IARangedEnemy::nextPosition(vec3f posEnemy,vec3f posHero,EnemyList * enemies){
    vec3f newMovement;
    float distance,maxDistance;
    pair<avatarDirection,vec3f> result;

    //If the enemy is far of our hero. The enemy stop the movement
    distance=sqrt(pow(posEnemy.x-posHero.x,2.0)+pow(posEnemy.y-posHero.y,2.0)+pow(posEnemy.z-posHero.z,2.0));
    if(distance>1.0){

        if(posEnemy.z>posHero.z && (posEnemy.x>=posHero.x-0.3 && posEnemy.x<=posHero.x+0.3))
            result.first=BACKWARD;
        else if(posEnemy.z<posHero.z && (posEnemy.x>=posHero.x-0.3 && posEnemy.x<=posHero.x+0.3))
            result.first=FORWARD;
        else if(posEnemy.x<posHero.x && (posEnemy.z>=posHero.z-0.3 && posEnemy.z<=posHero.z+0.3))
                result.first=RIGHTWARD;
        else if(posEnemy.x>posHero.x && (posEnemy.z>=posHero.z-0.3 && posEnemy.z<=posHero.z+0.3))
                result.first=LEFTWARD;
        else if(posEnemy.x<posHero.x && posEnemy.z>posHero.z)
                result.first=BACK_RIGHTWARD;
        else if(posEnemy.x>posHero.x && posEnemy.z>posHero.z)
                result.first=BACK_LEFTWARD;
        else if(posEnemy.x<posHero.x && posEnemy.z<posHero.z)
                result.first=FOR_RIGHTWARD;
        else if(posEnemy.x>posHero.x && posEnemy.z<posHero.z)
                result.first=FOR_LEFTWARD;
        result.second=vec3f(0.0f,0.0f,0.0f);
        return result;
    }

    //Else
    vector<vec3f> posEnemies=obtainPosEnemies(enemies->getEnemies());


    //Case -> Default
    newMovement.x=posEnemy.x;newMovement.y=posEnemy.y;newMovement.z=posEnemy.z;
    result.first=FORWARD;
    result.second=vec3f(0.0f,0.0f,0.0f);
    maxDistance=0.0;

    //Case -> Leftward will be the movement of our enemy
    newMovement.x=posEnemy.x-2.0;newMovement.z=posEnemy.z;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(maxDistance<distance && !checkCollision(posEnemies,vec3f(posEnemy.x-0.2,posEnemy.y,posEnemy.z))){ //If Rightward will be our move -> The distance is smallest between them
        result.first=LEFTWARD;
        result.second=vec3f(2.0f,0.0f,0.0f);
        maxDistance=distance;
    }


    //Case -> Rightward
    newMovement.x=posEnemy.x+2.0;newMovement.z=posEnemy.z;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(maxDistance<distance && !checkCollision(posEnemies,vec3f(posEnemy.x+0.2,posEnemy.y,posEnemy.z))){ //If Rightward will be our move -> The distance is smallest between them
        result.first=RIGHTWARD;
        result.second=vec3f(2.0f,0.0f,0.0f);
        maxDistance=distance;
    }

    //Case -> Backward
    newMovement.x=posEnemy.x;newMovement.z=posEnemy.z-2.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(maxDistance<distance && !checkCollision(posEnemies,vec3f(posEnemy.x,posEnemy.y,posEnemy.z-0.2))){ //If Backward will be our move -> The distance is smallest between them
        result.first=BACKWARD;
        result.second=vec3f(0.0f,0.0f,-2.0f);
        maxDistance=distance;
    }

    //Case -> Forward
    newMovement.x=posEnemy.x;newMovement.z=posEnemy.z+2.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(maxDistance<distance && !checkCollision(posEnemies,vec3f(posEnemy.x,posEnemy.y,posEnemy.z+0.2))){ //If Forward will be our move -> The distance is smallest between them
        result.first=FORWARD;
        result.second=vec3f(0.0f,0.0f,2.0f);
        maxDistance=distance;
    }

    //Case -> Left-forward
    newMovement.x=posEnemy.x-1.0;newMovement.z=posEnemy.z+1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(maxDistance<distance && !checkCollision(posEnemies,vec3f(posEnemy.x-0.1,posEnemy.y,posEnemy.z+0.1))){ //If Left-forward will be our move -> The distance is smallest between them
        result.first=FOR_LEFTWARD;
        result.second=vec3f(-1.0f,0.0f,1.0f);
        maxDistance=distance;
    }

    //Case -> Right-forward
    newMovement.x=posEnemy.x+1.0;newMovement.z=posEnemy.z+1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(maxDistance<distance && !checkCollision(posEnemies,vec3f(posEnemy.x+0.1,posEnemy.y,posEnemy.z+0.1))){ //If Right-forward will be our move -> The distance is smallest between them
        result.first=FOR_RIGHTWARD;
        result.second=vec3f(+1.0f,0.0f,+1.0f);
        maxDistance=distance;
    }

    //Case -> Left-backward
    newMovement.x=posEnemy.x-1.0;newMovement.z=posEnemy.z-1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(maxDistance<distance && !checkCollision(posEnemies,vec3f(posEnemy.x-0.1,posEnemy.y,posEnemy.z-0.1))){ //If Left-backward will be our move -> The distance is smallest between them
        result.first=BACK_LEFTWARD;
        result.second=vec3f(-1.0f,0.0f,-1.0f);
        maxDistance=distance;
    }

    //Case -> Right-backward
    newMovement.x=posEnemy.x+1.0;newMovement.z=posEnemy.z-1.0;
    distance=sqrt(pow(newMovement.x-posHero.x,2.0)+pow(newMovement.y-posHero.y,2.0)+pow(newMovement.z-posHero.z,2.0));
    if(maxDistance<distance && !checkCollision(posEnemies,vec3f(posEnemy.x+0.1,posEnemy.y,posEnemy.z-0.1))){ //If Right-backward will be our move -> The distance is smallest between them
        result.first=BACK_RIGHTWARD;
        result.second=vec3f(1.0f,0.0f,-1.0f);
        maxDistance=distance;
    }

    return result;
}
