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

#include "trapdoor.h"

TrapDoor::TrapDoor(const Value & trapDoorFeatures){
    position=vec4f(trapDoorFeatures["position"][0].GetFloat(),trapDoorFeatures["position"][1].GetFloat(),trapDoorFeatures["position"][2].GetFloat(),1.0);
    //damage=trapDoorFeatures["damage"].GetFloat();

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedTrap=soundCollect->getSound(sATRAP);
    animationSound=soundCollect->getSound(sNTRAP);

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);

    transActivate=new Matrix4f();
    transActivate->identity();

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(transActivate);
    root->add(materialCollect->getMaterial(mTRAPDOOR));
    root->add(meshCollect->getMesh(TRAPDOOR));

    currentTime=SDL_GetTicks();
    hitDelay=currentTime;
    delayTime=currentTime;
    desactivatedDelay=currentTime;
    activated=false;
    delayActivated=false;

    initAnimation();

}

//**********************************************************************//

TrapDoor::~TrapDoor(){
    delete root;
}

//**********************************************************************//

void TrapDoor::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void TrapDoor::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    //if hero is near of a disactivated trap
    if(!activated && distance<=0.75 && (position.y>posHero.y-1 && position.y<posHero.y)){
        activated=true;
        delayActivated=true;
        delayTime=time;
        desactivatedDelay=time;
        animationUp->resetState();
        animationDown->resetState();
        transActivate->identity();
        activatedTrap->play(0);
    }

    if(activated && desactivatedDelay<(time-2100) && distance>0.75){ //if hero is far of an activated trap
        activated=false;
        delayActivated=false;
        animationSound->play(0);
    }

    if(activated){ // if is activated
        if(!delayActivated){ //If is not in delayTime
            if(distance<=0.75 && (position.y>posHero.y-1 && position.y<posHero.y) && hitDelay<(time-400)){
                hero->takeDamage(damage);
                hitDelay=time;
            }
        }
        else { //If is in delayTime
            if(delayTime<(time-600)){
                delayActivated=false;
                animationSound->play(0);
            }
        }
    }

    ////////////////////////////////
    // Updated animation
    if(activated && !delayActivated && animationUp->getScriptState(0)!=1){
        animationUp->updateState(time-currentTime);
        transActivate->product(animationUp->readMatrix(0).getMatrix());
    }
    else if(!activated && animationDown->getScriptState(0)!=1){
        animationDown->updateState(time-currentTime);
        transActivate->product(animationDown->readMatrix(0).getMatrix());
    }
    else if(animationDown->getScriptState(0)==1){
        transActivate->identity();
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

bool TrapDoor::isActivated(){
    return activated;
}

//**********************************************************************//

void TrapDoor::initAnimation(){
    //////////////////////////////////////
    //Animation up
    animationUp=new ScriptLMD();

    LinearMovement * movementUp=new LinearMovement(0.0,7.0,0.0);
    MatrixStatic * notMove=new MatrixStatic();

    MatrixScript * scriptUp=new MatrixScript();

    scriptUp->add(0.12,movementUp);
    scriptUp->add(0.5,notMove);

    animationUp->add(scriptUp);


    /////////////////////////////
    //Animation down
    animationDown=new ScriptLMD();

    LinearMovement * movementDown=new LinearMovement(0.0,-7.0,0.0);

    MatrixScript * scriptDown=new MatrixScript();

    scriptDown->add(0.12,movementDown);
    scriptDown->add(0.5,notMove);

    animationDown->add(scriptDown);
}
