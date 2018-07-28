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

#include "trapdoor.h"

TrapDoor::TrapDoor(const Value & trapDoorFeatures, int id){
    position=vec4f(trapDoorFeatures["position"][0].GetFloat(),trapDoorFeatures["position"][1].GetFloat(),trapDoorFeatures["position"][2].GetFloat()+0.1f,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedTrap=soundCollect->getSound(sATRAP);
    animationSound=soundCollect->getSound(sNTRAP);

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z-0.5f);

    Matrix4f * transForRot=new Matrix4f();
    transForRot->translation(0.0f,0.0f,+0.25f);

    Matrix4f * rotObject=new Matrix4f();
    rotObject->rotation(180.0f,0.0f,1.0f,0.0f);

    Matrix4f * transTrap=new Matrix4f();
    transTrap->translation(0.0f,0.0f,-1.0f);

    transActivateFirst=new Matrix4f();
    transActivateFirst->identity();

    transActivateSecond=new Matrix4f();
    transActivateSecond->identity();

    NodeSceneGraph * doorFirst=new NodeSceneGraph();
    doorFirst->add(transActivateFirst);
    doorFirst->add(transForRot);
    doorFirst->add(meshCollect->getMesh(TRAPDOOR));

    NodeSceneGraph * doorSecond=new NodeSceneGraph();
    doorSecond->add(rotObject);
    doorSecond->add(transTrap);
    doorSecond->add(transActivateSecond);
    doorSecond->add(transForRot);
    doorSecond->add(meshCollect->getMesh(TRAPDOOR));

    NodeSceneGraph * root=new NodeSceneGraph();
    root->add(transObject);
    root->add(materialCollect->getMaterial(mTRAPDOOR));
    root->add(doorFirst);
    root->add(doorSecond);

    currentTime=SDL_GetTicks();
    delayTime=currentTime;
    desactivatedDelay=currentTime;
    activated=false;
    delayActivated=false;
    trapID=id;

    object=root;
    damage=0.0;
    initAnimation();

}

//**********************************************************************//

TrapDoor::~TrapDoor(){
    delete object;
}

//**********************************************************************//

void TrapDoor::visualization(Context & cv){
    if(position.x>cv.minVisualPosition.x && position.x<cv.maxVisualPosition.x
       && position.y>cv.minVisualPosition.y && position.y<cv.maxVisualPosition.y)
        object->visualization(cv);
}

//**********************************************************************//

void TrapDoor::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=gameState.refPoint;
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    //if hero is near of a disactivated trap
    if(!activated && ((distance<=0.75 && (position.y>posHero.y-1 && position.y<posHero.y)) ) ){
        activated=true;
        delayActivated=true;
        delayTime=time;
        desactivatedDelay=time;
        animationUp->resetState();
        animationDown->resetState();
        transActivateFirst->identity();
        transActivateSecond->identity();
        activatedTrap->play(distance);
    }

    if(activated && desactivatedDelay<(time-2100) && (distance>0.75)){ //if hero is far of an activated trap
        activated=false;
        delayActivated=false;
        animationSound->play(distance);
        gameState.rootMap->addCollision(vec2f(position.x,position.z),trapID);
    }

    if(activated){ // if is activated
        if(delayActivated){ //If is not in delayTime
            if(delayTime<(time-600)){
                delayActivated=false;
                gameState.rootMap->removeCollision(vec2f(position.x,position.z),trapID);
                animationSound->play(distance);
            }
        }
    }

    ////////////////////////////////
    // Updated animation
    if(activated && !delayActivated && animationUp->getScriptState(0)!=1){
        animationUp->updateState(time-currentTime);
        transActivateFirst->setMatrix(animationUp->readMatrix(0).getMatrix());
        transActivateSecond->setMatrix(animationUp->readMatrix(0).getMatrix());
    }
    else if(!activated && animationDown->getScriptState(0)!=1){
        animationDown->updateState(time-currentTime);
        transActivateFirst->setMatrix(animationDown->readMatrix(0).getMatrix());
        transActivateSecond->setMatrix(animationDown->readMatrix(0).getMatrix());

    }
    else if(animationDown->getScriptState(0)==1){
        transActivateFirst->identity();
        transActivateSecond->identity();
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
    //Animation up first
    animationUp=new ScriptLMD();

    OscillateRotation * oscltDoorUpFirst=new OscillateRotation(false,0,-90,1,300,vec3f(1,0,0),1);

    Matrix4f * rot=new Matrix4f();
    rot->rotation(-90,1.0f,0.0f,0.0f);
    MatrixStatic * rotStatic=new MatrixStatic(*rot);

    MatrixScript * scriptUp=new MatrixScript();

    scriptUp->add(0.3,oscltDoorUpFirst);
    scriptUp->add(0.5,rotStatic);

    animationUp->add(scriptUp);

    /////////////////////////////////////////
    // Animation Down first
    animationDown=new ScriptLMD();
    OscillateRotation * oscltDoorDownFirst=new OscillateRotation(true,0,-90,-89,300,vec3f(1,0,0),1);
    MatrixStatic * notMove=new MatrixStatic();

    MatrixScript * script=new MatrixScript();

    script->add(0.3,oscltDoorDownFirst);
    script->add(0.5,notMove);

    animationDown->add(script);
}
