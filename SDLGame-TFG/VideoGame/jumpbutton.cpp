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

#include "jumpbutton.h"

JumpButton::JumpButton(const Value & buttonFeatures){
    position=vec4f(respawnFeatures["position"][0].GetFloat(),respawnFeatures["position"][1].GetFloat(),respawnFeatures["position"][2].GetFloat(),1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedButton=soundCollect->getSound(sATRAP);

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);
    Matrix4f * transButton=new Matrix4f();
    transButton->translation(0.0f,0.08f,0.0f);

    transActivate=new Matrix4f();
    transActivate->identity();

    NodeSceneGraph * button=new NodeSceneGraph();
    button->add(transActivate);
    button->add(transButton);
    button->add(meshCollect->getMesh(BUTTON));

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(materialCollect->getMaterial(mBUTTON));
    root->add(button);
    root->add(meshCollect->getMesh(BUTTONB));

    currentTime=SDL_GetTicks();
    activated=false;

    initAnimation();
}

//**********************************************************************//

JumpButton::~JumpButton(){
    delete root;
}

//**********************************************************************//

void JumpButton::visualization(Context & cv){
    root->visualization(cv);
}

//**********************************************************************//

void JumpButton::updateState(GameState & gameState){

}

//**********************************************************************//

bool JumpButton::isActivated(){
    return activated;
}

//**********************************************************************//

void JumpButton::initAnimation(){
    //////////////////////////////////////
    //Animation up
    animationUp=new ScriptLMD();

    LinearMovement * movementUp=new LinearMovement(0.0,1.0,0.0);
    MatrixStatic * notMove=new MatrixStatic();

    MatrixScript * scriptUp=new MatrixScript();

    scriptUp->add(0.08,movementUp);
    scriptUp->add(0.5,notMove);

    animationUp->add(scriptUp);


    /////////////////////////////
    //Animation down
    animationDown=new ScriptLMD();

    LinearMovement * movementDown=new LinearMovement(0.0,-1.0,0.0);

    MatrixScript * scriptDown=new MatrixScript();

    scriptDown->add(0.08,movementDown);
    scriptDown->add(0.5,notMove);

    animationDown->add(scriptDown);
}
