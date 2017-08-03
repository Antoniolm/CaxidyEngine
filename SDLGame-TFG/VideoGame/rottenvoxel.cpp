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

#include "rottenvoxel.h"

RottenVoxel::RottenVoxel(const Value & rottenFeatures, int id){
    position=vec4f(rottenFeatures["position"][0].GetFloat(),rottenFeatures["position"][1].GetFloat(),rottenFeatures["position"][2].GetFloat()+0.1f,1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedVoxel=soundCollect->getSound(sROT);

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z-0.5f);

    transActivate=new Matrix4f();
    transActivate->identity();


    NodeSceneGraph * root=new NodeSceneGraph();
    root->add(transObject);
    root->add(transActivate);
    root->add(materialCollect->getMaterial(mCUBE_LAND));
    root->add(meshCollect->getMesh(CUBE));

    currentTime=SDL_GetTicks();
    delayTime=currentTime;
    activated=false;
    disappear=false;
    voxelID=id;

    object=root;
    damage=0.0;
    initAnimation();

}

//**********************************************************************//

RottenVoxel::~RottenVoxel(){
    delete object;
}

//**********************************************************************//

void RottenVoxel::visualization(Context & cv){
    object->visualization(cv);
}

//**********************************************************************//

void RottenVoxel::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    //if hero is near of a disactivated trap
    if(!activated && !disappear && distance<=0.75 && (position.y>posHero.y-1 && position.y<posHero.y)){
        activated=true;
        delayTime=time;
        animation->resetState();
        transActivate->identity();
        activatedVoxel->play(0);
    }

    if(activated && delayTime<(time-1600)){ //if hero is far of an activated trap
        activated=false;
        disappear=true;
        gameState.rootMap->removeCollision(vec2f(position.x,position.z),voxelID);
    }

    ////////////////////////////////
    // Updated animation
    if(activated){
        animation->updateState(time-currentTime);
        transActivate->product(animation->readMatrix(0).getMatrix());
    }

    currentTime+=time-currentTime;

}

//**********************************************************************//

bool RottenVoxel::isActivated(){
    return activated;
}

//**********************************************************************//

bool RottenVoxel::isDisappear(){
    return disappear;
}

//**********************************************************************//

void RottenVoxel::initAnimation(){
    //////////////////////////////////////
    //Animation up
    animation=new ScriptLMD();

    LinearMovement * movement=new LinearMovement(0.0f,0.0f,0.5f);
    LinearMovement * movementOpp=new LinearMovement(0.0f,0.0f,-0.5f);
    MatrixStatic * notMove=new MatrixStatic();

    MatrixScript * scriptUp=new MatrixScript();

    scriptUp->add(0.1,movement);
    scriptUp->add(0.1,movementOpp);

    animation->add(scriptUp);
}
