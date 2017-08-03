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

    activatedVoxel=soundCollect->getSound(sROT);

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);

    transActivate=new Matrix4f();
    transActivate->identity();

    NodeSceneGraph * root=new NodeSceneGraph();
    root->add(transObject);
    root->add(transActivate);
    root->add(materialCollect->getMaterial(mCUBE_STEEL));
    root->add(meshCollect->getMesh(CUBE));

    currentTime=SDL_GetTicks();
    delayTime=currentTime;
    activated=false;
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

    //if hero is near of a movable voxel and he push E -> Hero push the voxel in his arms
    if(gameState.controller->checkButton(cACTION) && distance<=1.3 /*&&
       (position.y>posHero.y-1 && position.y<posHero.y+1)*/){
        gameState.controller->consumeButtons();
        cout<< "yep"<<endl;

        if(position.z>posHero.z && (position.x>=posHero.x-0.4 && position.x<=posHero.x+0.4))
            transActivate->translation(0.0f,0.0f,1.0f);

        if(position.z<posHero.z && (position.x>=posHero.x-0.4 && position.x<=posHero.x+0.4))
            transActivate->translation(0.0f,0.0f,-1.0f);

        if(position.x<posHero.x && (position.z>=posHero.z-0.4 && position.z<=posHero.z+0.4))
            transActivate->translation(1.0f,0.0f,0.0f);

        if(position.x>posHero.x && (position.z>=posHero.z-0.4 && position.z<=posHero.z+0.4))
            transActivate->translation(-1.0f,0.0f,0.0f);
    }

}

//**********************************************************************//

bool MovableVoxel::isActivated(){
    return activated;
}

//**********************************************************************//

void MovableVoxel::initAnimation(){

}
