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
    delayTime=currentTime;
    desactivatedDelay=currentTime;
    activated=false;
    delayActivated=false;

    initAnimation();
}

//**********************************************************************//

RespawnVoxel::~RespawnVoxel(){
    delete root;
}

//**********************************************************************//

void RespawnVoxel::visualization(Context & cv){
    root->visualization(cv)
}

//**********************************************************************//

void RespawnVoxel::updateState(GameState & gameState){

}

//**********************************************************************//

bool RespawnVoxel::isActivated(){

}

//**********************************************************************//

void RespawnVoxel::initAnimation(){

}
