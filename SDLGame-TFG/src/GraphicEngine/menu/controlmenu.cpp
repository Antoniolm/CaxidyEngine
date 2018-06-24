// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David L�pez Machado
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

#include "controlmenu.h"

ControlMenu::ControlMenu(vec3f position,string fileName)
{
    currentOption=0;
    activateMenu=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"resources/textures/controlScreen.png");
    materialBack=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,fileName.c_str());

    positionMenu=new Matrix4f();
    positionMenu->translation(position.x,position.y,position.z);

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.2);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ///////////////////////
    //Text
    Matrix4f * positionText=new Matrix4f();
    positionText->translation(0.0,0.2,0.8);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.5,2.0,0.5);

    NodeSceneGraph * nodeText=new NodeSceneGraph(false,true);
    nodeText->add(positionText);
    nodeText->add(scaleMenu);
    nodeText->add(currentMaterial);
    nodeText->add(meshCollect->getMesh(TEXT));

    ///////////////////////
    //Back
    Matrix4f * scaleMenuBack=new Matrix4f();
    scaleMenuBack->scale(1.0,4.2,1.0);

    NodeSceneGraph * nodeBack=new NodeSceneGraph(false,true);
    nodeBack->add(scaleMenuBack);
    nodeBack->add(materialBack);
    nodeBack->add(meshCollect->getMesh(TEXT));

    //////////////////////
    // MainMenuBack
    Matrix4f * positionMainBack=new Matrix4f();
    positionMainBack->translation(0.725,0.5,0.8);

    Matrix4f * scaleMain=new Matrix4f();
    scaleMain->scale(0.35,1.8,0.5);

    material=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"resources/textures/mainMenuControl.png");

    NodeSceneGraph * nodeMainBack=new NodeSceneGraph(false,true);
    nodeMainBack->add(positionMainBack);
    nodeMainBack->add(scaleMain);
    nodeMainBack->add(material);
    nodeMainBack->add(meshCollect->getMesh(TEXT));


    root=new NodeSceneGraph(false,true);
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(betweenMenu);
    root->add(nodeBack);
    root->add(nodeText);
    root->add(nodeMainBack);
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    openSound=soundCollect->getSound(sOpen);
}

//**********************************************************************//

ControlMenu::~ControlMenu()
{
    delete root;
    delete currentMaterial;
    delete materialBack;
    delete material;
}

//**********************************************************************//

void ControlMenu::visualization(Context & cv){
    if(activateMenu){
        root->visualization(cv);
    }
}

//**********************************************************************//

void ControlMenu::updateState(GameState & gameState){
    vec3f position;
    float time=gameState.time;

    if(time-currentTime>200)
        currentTime=time-50;

    if(activateMenu){ //If the menu is activated
        if(gameState.controller->checkButton(cACTION) && menuDelay<(time-300)){ //If the user push the action intro
            menuDelay=time;
            activateMenu=false;
            gameState.controller->consumeButtons();
            openSound->play();
        }
    }

    currentTime+=time-currentTime;
}

//**********************************************************************//

void ControlMenu::activate(){
    activateMenu=true;
}
