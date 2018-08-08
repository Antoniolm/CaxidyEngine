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

#include "respawnvoxelgame.h"

RespawnVoxelGame::RespawnVoxelGame(const Value & respawnFeatures)
    :RespawnVoxel(respawnFeatures)
{
    
}

//**********************************************************************//

RespawnVoxelGame::~RespawnVoxelGame(){
    delete root;
}

//**********************************************************************//

void RespawnVoxelGame::updateState(GameState & gameState){
    float time=gameState.time;

    if(time-currentTime>200) currentTime=time-50;

    vec3f posRef=gameState.refPoint;
    float distance=sqrt(pow(position.x-posRef.x,2.0)+pow(position.z-posRef.z,2.0));

    //if hero is near of a disactivated trap
    if(!activated && (int)position.x==(int)posRef.x && (int)position.z==(int)posRef.z
       && (position.y>posRef.y-1 && position.y<posRef.y)){
        activated=true;
        animationDown->resetState();
        animationUp->resetState();
        transActivate->identity();
        activatedButton->play(distance);
    }

    if(activated && ( (int)position.x!=(int)posRef.x || (int)position.z!=(int)posRef.z
        || position.y>posRef.y+1 || position.y<posRef.y-1)){ //if hero is far of an activated trap
        activated=false;
        activatedButton->play(distance);
    }

    ////////////////////////////////
    // Updated animation
    if(activated && animationDown->getScriptState(0)!=1){
        animationDown->updateState(time-currentTime);
        transActivate->product(animationDown->readMatrix(0).getMatrix());
    }
    else if(!activated && animationUp->getScriptState(0)!=1){
        animationUp->updateState(time-currentTime);
        transActivate->product(animationUp->readMatrix(0).getMatrix());
    }
    else if(animationUp->getScriptState(0)==1){
        transActivate->identity();
    }

    currentTime+=time-currentTime;
}
