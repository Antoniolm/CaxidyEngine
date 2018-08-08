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

#include "movablevoxel.h"
#include "rootmap.h"

MovableVoxel::MovableVoxel(){

}

//**********************************************************************//

MovableVoxel::MovableVoxel(const Value & movableFeatures, const vector<RespawnVoxel*> & respawns , int id){
    position=vec4f(movableFeatures["position"][0].GetFloat(),movableFeatures["position"][1].GetFloat(),movableFeatures["position"][2].GetFloat()+0.1f,1.0);
    defaultPosition=position;
    respawn=respawns[movableFeatures["respawn"].GetFloat()];

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedVoxel=soundCollect->getSound(sMOV);
    fallSound=soundCollect->getSound(sFBLOCK);

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
    
    if(time-currentTime>200) currentTime=time-50;

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
