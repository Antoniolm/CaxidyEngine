// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David L�pez Machado
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

#include "movablevoxelgame.h"
#include "rootmapgame.h"

MovableVoxelGame::MovableVoxelGame(const Value & movableFeatures, const vector<RespawnVoxel*> & respawns , int id)
    :MovableVoxel(movableFeatures,respawns,id)
{
}

//**********************************************************************//

MovableVoxelGame::~MovableVoxelGame(){
    delete object;
}

//**********************************************************************//

void MovableVoxelGame::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=dynamic_cast<RootMapGame*>(gameState.rootMap)->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    bool auxFalling=isFalling;
    gravity(gameState);

    //If the flag change its state of fallen
    if(auxFalling && !isFalling)
        fallSound->play(distance);

    vec4f pos=transActivate->product(vec4f());
    position.y=pos.y;

    //If the hero repawn the movable voxel
    vector<Enemy *> enemies=dynamic_cast<RootMapGame*>(gameState.rootMap)->getEnemyList()->getEnemies();

    if(respawn->isActivated() && ((int)position.x!=(int)defaultPosition.x || (int)position.z!=(int)defaultPosition.z)){
        gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

        position=defaultPosition;

        transActivate->translation(position.x,position.y,position.z);
        gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);
    }

    //if hero is near of a movable voxel and he push E -> Hero push the voxel in his arms
    if( !activated && !hero->isFall() && !hero->isJump() && gameState.controller->checkButton(cACTION) && distance<=1.3&&
       (position.y>posHero.y-0.5 && position.y<posHero.y+0.5)){

        animation->resetState();

        // Case FRONT
        if(hero->getDirection()==FORWARD && gameState.rootMap->collision(vec3f(position.x,position.y,position.z+1.0f))==0
           && !checkEnemies(vec3f(position.x,position.y,position.z+1.0f),enemies)
           && position.z>posHero.z && (position.x>=posHero.x-0.4 && position.x<=posHero.x+0.4)){

                currentDir=FORWARD;
                activated=true;
        }

        // Case BACK
        if(hero->getDirection()==BACKWARD && gameState.rootMap->collision(vec3f(position.x,position.y,position.z-1.0f))==0
           && !checkEnemies(vec3f(position.x,position.y,position.z-1.0f),enemies)
           && position.z<posHero.z && (position.x>=posHero.x-0.4 && position.x<=posHero.x+0.4)){

                currentDir=BACKWARD;
                activated=true;
        }

        // Case LEFT
        if(hero->getDirection()==LEFTWARD && gameState.rootMap->collision(vec3f(position.x-1.0f,position.y,position.z))==0
           && !checkEnemies(vec3f(position.x-1.0f,position.y,position.z),enemies)
           && position.x<posHero.x && (position.z>=posHero.z-0.4 && position.z<=posHero.z+0.4)){

                currentDir=LEFTWARD;
                activated=true;
        }

        // Case RIGHT
        if(hero->getDirection()==RIGHTWARD && gameState.rootMap->collision(vec3f(position.x+1.0f,position.y,position.z))==0
           && !checkEnemies(vec3f(position.x+1.0f,position.y,position.z),enemies)
           && position.x>posHero.x && (position.z>=posHero.z-0.4 && position.z<=posHero.z+0.4)){

                currentDir=RIGHTWARD;
                activated=true;
        }
        if(activated){
            gameState.controller->consumeButtons();
            activatedVoxel->play();
        }
    }

    ////////////////////////////////
    // Updated animation
    if(activated){

        switch(currentDir){
        case FORWARD:
            animation->updateState(time-currentTime);
            transActivate->product(animation->readMatrix(0).getMatrix());

            if(animation->getScriptState(0)==1)
                activated=false;

            break;

        case BACKWARD:
            animation->updateState(time-currentTime);
            transActivate->product(animation->readMatrix(1).getMatrix());

            if(animation->getScriptState(1)==1)
                activated=false;

            break;

        case LEFTWARD:
            animation->updateState(time-currentTime);
            transActivate->product(animation->readMatrix(2).getMatrix());

            if(animation->getScriptState(2)==1)
                activated=false;

            break;

        case RIGHTWARD:
            animation->updateState(time-currentTime);
            transActivate->product(animation->readMatrix(3).getMatrix());

            if(animation->getScriptState(3)==1)
                activated=false;

            break;
        }

        if(!activated){
            switch(currentDir){
                case FORWARD:
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

                    position.z=position.z+1.0f;
                    transActivate->translation(position.x,position.y,position.z);
                    gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);
                    break;

                case BACKWARD:
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

                    position.z=position.z-1.0f;
                    transActivate->translation(position.x,position.y,position.z);
                    gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);

                    break;

                case LEFTWARD:
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

                    position.x=position.x-1.0f;
                    transActivate->translation(position.x,position.y,position.z);
                    gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);

                    break;

                case RIGHTWARD:
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

                    position.x=position.x+1.0f;
                    transActivate->translation(position.x,position.y,position.z);
                    gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);

                    break;
            }

        }

    }

    currentTime+=time-currentTime;

}

//**********************************************************************//

bool MovableVoxelGame::checkEnemies(vec3f newPos,vector<Enemy *> &enemies){
    vec3f posEnemy;

    bool result=false;

    for(int i=0;i<enemies.size();i++){
        posEnemy=enemies[i]->getPosition();

        if((int)posEnemy.x == (int)newPos.x && (int)posEnemy.z == (int)newPos.z
           && (newPos.y>posEnemy.y-1 && newPos.y<posEnemy.y+1)){
            result=true;
        }
    }

    return result;
}
