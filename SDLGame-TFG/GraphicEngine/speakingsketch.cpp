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

#include "speakingsketch.h"

SpeakingSketch::SpeakingSketch(vec3f aPos, string material){

    initialPosition=aPos;
    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    Matrix4f * transObject=new Matrix4f();
    transObject->identity();

    transActivate=new Matrix4f();
    transActivate->identity();

    Matrix4f * scaleSketch=new Matrix4f();
    scaleSketch->scale(1.0,4.2,1.0);

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(transActivate);
    root->add(scaleSketch);
    root->add(materialCollect->getMaterial(material));
    root->add(meshCollect->getMesh(TEXT));

    currentTime=SDL_GetTicks();
    activated=false;

}

//**********************************************************************//

SpeakingSketch::~SpeakingSketch(){
    delete root;
}

//**********************************************************************//

void SpeakingSketch::visualization(Context & cv){
    if(activated)
        root->visualization(cv);
}

//**********************************************************************//

void SpeakingSketch::updateState(GameState & gameState){
    vec3f posCamera;
    if(activated){
        posCamera=gameState.camera->getPosition();
        transActivate->translation(posCamera.x+initialPosition.x,posCamera.y+initialPosition.y,posCamera.z+initialPosition.z);
    }
}

//**********************************************************************//

void SpeakingSketch::setActivate(bool value){
    activated=value;
}

//**********************************************************************//

bool SpeakingSketch::isActivated(){
    return activated;
}
