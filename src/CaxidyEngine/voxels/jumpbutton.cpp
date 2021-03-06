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

#include "jumpbutton.h"

JumpButton::JumpButton(){

}

//**********************************************************************//

JumpButton::JumpButton(const Value & buttonFeatures){
    position=vec4f(buttonFeatures["position"][0].GetFloat(),buttonFeatures["position"][1].GetFloat(),buttonFeatures["position"][2].GetFloat(),1.0);
    velocity=vec4f(buttonFeatures["velocity"][0].GetFloat(),buttonFeatures["velocity"][1].GetFloat(),buttonFeatures["velocity"][2].GetFloat(),1.0);
    acceleration=vec4f(buttonFeatures["acceleration"][0].GetFloat(),buttonFeatures["acceleration"][1].GetFloat(),buttonFeatures["acceleration"][2].GetFloat(),1.0);

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedButton=soundCollect->getSound(sATRAP);

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);
    Matrix4f * transButton=new Matrix4f();
    transButton->translation(0.0f,0.2f,0.0f);

    transActivate=new Matrix4f();
    transActivate->identity();

    NodeSceneGraph * button=new NodeSceneGraph();
    button->add(transActivate);
    button->add(transButton);
    button->add(meshCollect->getMesh(JUMP));

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(materialCollect->getMaterial(mJUMP));
    root->add(button);
    root->add(meshCollect->getMesh(BUTTONB));

    currentTime=SDL_GetTicks();
    activated=false;
    jumping=false;

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
    float time=gameState.time;

    if(time-currentTime>200) currentTime=time-50;

    currentTime+=time-currentTime;
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

    MatrixStatic * notMove=new MatrixStatic();

    MatrixScript * scriptUp=new MatrixScript();
    MatrixScript * scriptUpJump=new MatrixScript();

    scriptUp->add(0.08,new LinearMovement(0.0,1.0,0.0));
    scriptUp->add(0.5,notMove);

    scriptUpJump->add(0.4,new LinearMovement(0.0,1.0,0.0));
    scriptUpJump->add(0.5,notMove);

    animationUp->add(scriptUp);
    animationUp->add(scriptUpJump);


    /////////////////////////////
    //Animation down
    animationDown=new ScriptLMD();

    MatrixScript * scriptDown=new MatrixScript();

    scriptDown->add(0.08,new LinearMovement(0.0,-1.0,0.0));
    scriptDown->add(0.5,notMove);

    animationDown->add(scriptDown);
}
