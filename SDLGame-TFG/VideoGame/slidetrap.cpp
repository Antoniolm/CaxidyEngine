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

#include "slidetrap.h"

SlideTrap::SlideTrap(const Value & slideFeatures, int id){
    position=vec4f(slideFeatures["position"][0].GetFloat(),slideFeatures["position"][1].GetFloat(),slideFeatures["position"][2].GetFloat()+0.1f,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedVoxel=soundCollect->getSound(sMOV);

    transActivate=new Matrix4f();
    transActivate->translation(position.x,position.y,position.z);

    NodeSceneGraph * root=new NodeSceneGraph();
    root->add(transActivate);
    root->add(materialCollect->getMaterial(mCUBE_ROCK));
    root->add(meshCollect->getMesh(CUBE));

    currentTime=SDL_GetTicks();
    delayTime=currentTime;
    activated=false;
    currentDir=FORWARD;
    voxelID=id;

    object=root;
    damage=0.0;
    initAnimation();
}

//**********************************************************************//

SlideTrap::~SlideTrap(){
    delete object;
}

//**********************************************************************//

void SlideTrap::visualization(Context & cv){
    object->visualization(cv);
}

//**********************************************************************//

void SlideTrap::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    activated=true;

    ////////////////////////////////
    // Updated animation
    if(delayTime<(time-3000)){
        activatedVoxel->play(distance);
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
            delayTime=currentTime;
            animation->resetState();

            switch(currentDir){
                case FORWARD:
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

                    position.z=position.z+1.0f;
                    transActivate->translation(position.x,position.y,position.z);
                    gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);

                    currentDir=BACKWARD;
                    break;

                case BACKWARD:
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

                    position.z=position.z-1.0f;
                    transActivate->translation(position.x,position.y,position.z);
                    gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);
                    currentDir=FORWARD;

                    break;

                case LEFTWARD:
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

                    position.x=position.x-1.0f;
                    transActivate->translation(position.x,position.y,position.z);
                    gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);
                    currentDir=RIGHTWARD;

                    break;

                case RIGHTWARD:
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);

                    position.x=position.x+1.0f;
                    transActivate->translation(position.x,position.y,position.z);
                    gameState.rootMap->addCollision(vec2f(position.x,position.z),voxelID);
                    currentDir=LEFTWARD;

                    break;
            }

        }

    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void SlideTrap::initAnimation(){
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
