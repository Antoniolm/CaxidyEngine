// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David López Machado
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

#include "movablevoxel.h"

MovableVoxel::MovableVoxel(const Value & movableFeatures, int id){
    position=vec4f(movableFeatures["position"][0].GetFloat(),movableFeatures["position"][1].GetFloat(),movableFeatures["position"][2].GetFloat()+0.1f,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedVoxel=soundCollect->getSound(sMOV);

    transActivate=new Matrix4f();
    transActivate->translation(position.x,position.y,position.z);

    acceleratedMove=new AcceleratedMovement();
    acceleratedMove->resetState();

    NodeSceneGraph * root=new NodeSceneGraph();
    root->add(transActivate);
    root->add(materialCollect->getMaterial(mCUBE_STEEL));
    root->add(meshCollect->getMesh(CUBE));

    currentTime=SDL_GetTicks();
    delayTime=currentTime;
    activated=false;
    isFalling=false;
    voxelID=id;

    object=root;
    damage=0.0;
    initAnimation();
}

//**********************************************************************//

MovableVoxel::~MovableVoxel(){
    delete object;
}

//**********************************************************************//

void MovableVoxel::visualization(Context & cv){
    object->visualization(cv);
}

//**********************************************************************//

void MovableVoxel::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    gravity(gameState);

    vec4f pos=transActivate->product(vec4f());
    position.y=pos.y;

    //if hero is near of a movable voxel and he push E -> Hero push the voxel in his arms
    if( !activated && !hero->isFall() && !hero->isJump() && gameState.controller->checkButton(cACTION) && distance<=1.3&&
       (position.y>posHero.y-0.5 && position.y<posHero.y+0.5)){

        animation->resetState();

        // Case FRONT
        if(hero->getDirection()==FORWARD && gameState.rootMap->collision(vec3f(position.x,position.y,position.z+1.0f))==0
           && !checkEnemies(vec3f(position.x,position.y,position.z+1.0f),gameState.rootMap->getEnemyList()->getEnemies())
           && position.z>posHero.z && (position.x>=posHero.x-0.4 && position.x<=posHero.x+0.4)){
            currentDir=FORWARD;
            activated=true;
        }

        // Case BACK
        if(hero->getDirection()==BACKWARD && gameState.rootMap->collision(vec3f(position.x,position.y,position.z-1.0f))==0
           && !checkEnemies(vec3f(position.x,position.y,position.z-1.0f),gameState.rootMap->getEnemyList()->getEnemies())
           && position.z<posHero.z && (position.x>=posHero.x-0.4 && position.x<=posHero.x+0.4)){
            currentDir=BACKWARD;
            activated=true;
        }

        // Case LEFT
        if(hero->getDirection()==LEFTWARD && gameState.rootMap->collision(vec3f(position.x-1.0f,position.y,position.z))==0
           && !checkEnemies(vec3f(position.x-1.0f,position.y,position.z),gameState.rootMap->getEnemyList()->getEnemies())
           && position.x<posHero.x && (position.z>=posHero.z-0.4 && position.z<=posHero.z+0.4)){
            currentDir=LEFTWARD;
            activated=true;
        }

        // Case RIGHT
        if(hero->getDirection()==RIGHTWARD && gameState.rootMap->collision(vec3f(position.x+1.0f,position.y,position.z))==0
           && !checkEnemies(vec3f(position.x+1.0f,position.y,position.z),gameState.rootMap->getEnemyList()->getEnemies())
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

bool MovableVoxel::isActivated(){
    return activated;
}

//**********************************************************************//

void MovableVoxel::initAnimation(){
    //////////////////////////////////////
    //Animation Front
    animation=new ScriptLMD();

    LinearMovement * movementFront=new LinearMovement(0.0f,0.0f,3.0f);
    MatrixStatic * notMove=new MatrixStatic();

    MatrixScript * scriptFront=new MatrixScript();

    scriptFront->add(0.3,movementFront);
    scriptFront->add(0.05,notMove);

    animation->add(scriptFront);

    //////////////////////////////////////
    //Animation Back
    LinearMovement * movementBack=new LinearMovement(0.0f,0.0f,-3.0f);

    MatrixScript * scriptBack=new MatrixScript();

    scriptBack->add(0.3,movementBack);
    scriptBack->add(0.05,notMove);

    animation->add(scriptBack);

    //////////////////////////////////////
    //Animation Left

    LinearMovement * movementLeft=new LinearMovement(-3.0f,0.0f,0.0f);

    MatrixScript * scriptLeft=new MatrixScript();

    scriptLeft->add(0.3,movementLeft);
    scriptLeft->add(0.05,notMove);

    animation->add(scriptLeft);

    //////////////////////////////////////
    //Animation Right
    LinearMovement * movementRight=new LinearMovement(3.0f,0.0f,0.0f);

    MatrixScript * scriptRight=new MatrixScript();

    scriptRight->add(0.3,movementRight);
    scriptRight->add(0.05,notMove);

    animation->add(scriptRight);
}

//**********************************************************************//

bool MovableVoxel::checkEnemies(vec3f newPos,vector<Enemy *> &enemies){
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

//**********************************************************************//
ObjectScene * MovableVoxel::gravity(GameState & gameState){
    ObjectScene * hasCollision=0;

    float time=gameState.time;

    vec3f posVoxel=vec3f(position);
    posVoxel.y-=0.6;

    GLfloat * moveGravity=acceleratedMove->updateState(time-currentTime).getMatrix();
    if(moveGravity[13]<-0.5)
        moveGravity[13]=-0.5;

    //Check the collision in the center
    hasCollision=gameState.rootMap->collision(vec3f(posVoxel.x,posVoxel.y,posVoxel.z));

    if(hasCollision==0){ //if not collision
        transActivate->product(moveGravity);
        isFalling=true;
    }
    else {
        if(isFalling){
            vec3f positionObs=hasCollision->getPosition();
            BoundingBox box=hasCollision->getBoundingBox();
            if((positionObs.y+box.maxValue.y)-(posVoxel.y)>0.1 && (positionObs.y+box.maxValue.y)-(posVoxel.y)<0.5){
                Matrix4f trans;
                trans.translation(0.0,(positionObs.y+box.maxValue.y)-(posVoxel.y),0.0);
                transActivate->product(trans.getMatrix());
            }
        }
        isFalling=false;
        acceleratedMove->resetState();
    }

    return hasCollision;
}
