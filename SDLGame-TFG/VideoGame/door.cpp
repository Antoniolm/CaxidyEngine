// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David López Machado
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

#include "door.h"

Door::Door(const Value & doorFeatures,const vector<SoulCarrier*> & soulCarriers,int ID)
{
    position=vec4f(doorFeatures["position"][0].GetFloat(),doorFeatures["position"][1].GetFloat(),doorFeatures["position"][2].GetFloat(),1.0);
    sCarrier=soulCarriers[doorFeatures["soulCarrier"].GetFloat()];
    doorType=doorFeatures["direction"].GetFloat();
    doorID=ID;
    activated=false;

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    moveDoor=new Matrix4f();
    Matrix4f *transDoor=new Matrix4f();

    rotateDoor=new Matrix4f();
    rotateDoor->identity();

    transDoor->translation(1.0,0.0,0.0);
    moveDoor->translation(position.x-1.0,position.y,position.z);

    if(doorType==1)
        rotateDoor->rotation(90,0.0,1.0,0.0);


    NodeSceneGraph * root=new NodeSceneGraph();
    root->add(moveDoor);
    root->add(rotateDoor);
    root->add(transDoor);
    root->add(materialCollect->getMaterial(mDOOR));
    root->add(meshCollect->getMesh(DOOR));

    object=root;
    damage=0.0;
    currentTime=SDL_GetTicks();

    initAnimation();
}

//**********************************************************************//

Door::~Door()
{
    delete object;
}

//**********************************************************************//

void Door::visualization(Context & cv){
    object->visualization(cv);
}

//**********************************************************************//

void Door::updateState(GameState & gameState ){
    float time=gameState.time;

    if(time-currentTime>200) currentTime=time-50;

    //if hero put a soul in our soulCarrier this is activated and our door is opened
    if(sCarrier->isActivated()){
        if(!activated){
            switch(doorType){
                case 0: //Remove in front side
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),doorID);
                    gameState.rootMap->removeCollision(vec2f(position.x-1.0,position.z),doorID);
                    break;
                case 1: //Remove in sideAway
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z),doorID);
                    gameState.rootMap->removeCollision(vec2f(position.x,position.z+1.0),doorID);
                    break;

            }
        }
        activated=true;
    }

    //if is activate && not finish the rotate animation use the animation
    if(activated && animation->getScriptState(0)!=1 && animation->getScriptState(1)!=1){
        animation->updateState(time-currentTime);
        if(animation->getScriptState(0)!=1 && doorType==0){ //DoorType 0 use script 0
            rotateDoor->setMatrix(animation->readMatrix(0).getMatrix());
        }
        else if(animation->getScriptState(1)!=1 && doorType==1) //Doortype 1 use script 1
            rotateDoor->setMatrix(animation->readMatrix(1).getMatrix());
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void Door::initAnimation(){
    animation=new ScriptLMD();

    OscillateRotation * oscltDoorFront=new OscillateRotation(true,90,0,1,300,vec3f(0,1,0),1);
    OscillateRotation * oscltDoorSide=new OscillateRotation(true,180,90,91,300,vec3f(0,1,0),1);
    MatrixStatic * notMove=new MatrixStatic();

    MatrixScript * scriptFront=new MatrixScript();
    MatrixScript * scriptSide=new MatrixScript();

    scriptFront->add(0.3,oscltDoorFront);
    scriptFront->add(0.5,notMove);

    scriptSide->add(0.3,oscltDoorSide);
    scriptSide->add(0.5,notMove);

    animation->add(scriptFront);
    animation->add(scriptSide);
}
