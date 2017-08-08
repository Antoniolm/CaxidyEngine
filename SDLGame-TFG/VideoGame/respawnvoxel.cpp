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

#include "respawnvoxel.h"

RespawnVoxel::RespawnVoxel(const Value & respawnFeatures){
    position=vec4f(respawnFeatures["position"][0].GetFloat(),respawnFeatures["position"][1].GetFloat(),respawnFeatures["position"][2].GetFloat(),1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedButton=soundCollect->getSound(sATRAP);

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);

    transActivate=new Matrix4f();
    transActivate->identity();

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(transActivate);
    root->add(materialCollect->getMaterial(mSPIKE));
    root->add(meshCollect->getMesh(SPIKE));

    currentTime=SDL_GetTicks();
    activated=false;

    initAnimation();
}

//**********************************************************************//

RespawnVoxel::~RespawnVoxel(){
    delete root;
}

//**********************************************************************//

void RespawnVoxel::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void RespawnVoxel::updateState(GameState & gameState){
    float time=gameState.time;
    Hero * hero=gameState.rootMap->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    //if hero is near of a disactivated trap
    if(!activated && (int)position.x==(int)posHero.x && (int)position.z==(int)posHero.z
       && (position.y>posHero.y-1 && position.y<posHero.y)){
        activated=true;
        animation->resetState();
        transActivate->identity();
        activatedButton->play(distance);
    }

    if(activated && ((int)position.x!=(int)posHero.x || (int)position.z!=(int)posHero.z) ){ //if hero is far of an activated trap
        activated=false;
        activatedButton->play(distance);
    }

    ////////////////////////////////
    // Updated animation
    if(activated && animation->getScriptState(0)!=1){
        animation->updateState(time-currentTime);
        transActivate->product(animation->readMatrix(0).getMatrix());
    }
    else if(!activated && animation->getScriptState(1)!=1){
        animation->updateState(time-currentTime);
        transActivate->product(animation->readMatrix(1).getMatrix());
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

bool RespawnVoxel::isActivated(){
    return activated;
}

//**********************************************************************//

void RespawnVoxel::initAnimation(){
    //////////////////////////////////////
    //Animation
    animation=new ScriptLMD();

    Matrix4f * trans=new Matrix4f();
    trans->translation(0.0f,-2.0f,0.0f);

    MatrixScript * scriptUp=new MatrixScript();
    MatrixScript * scriptDown=new MatrixScript();

    scriptUp->add(0.12,new LinearMovement(0.0,7.0,0.0));
    scriptUp->add(0.3,new MatrixStatic());

    scriptDown->add(0.12,new LinearMovement(0.0,-7.0,0.0));
    scriptDown->add(0.3,new MatrixStatic(*trans));

    animation->add(scriptDown);
    animation->add(scriptUp);

}
