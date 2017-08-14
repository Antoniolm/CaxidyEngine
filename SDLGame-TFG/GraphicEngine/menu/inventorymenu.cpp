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

#include "inventorymenu.h"

InventoryMenu::InventoryMenu(vec3f initPos,string fileName){

    currentOption=0;
    activateMenu=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();
    initialPosition=initPos;

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/selectItem.png");
    materialBack=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,fileName.c_str());

    positionMenu=new Matrix4f();
    positionMenu->translation(initPos.x,initPos.y,initPos.z);

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.2);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ///////////////////////
    //Text
    selectedPosition=new Matrix4f();
    selectedPosition->translation(0.725,0.5,0.8);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.35,1.8,0.5);

    NodeSceneGraph * nodeText=new NodeSceneGraph(false,true);
    nodeText->add(selectedPosition);
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

    root=new NodeSceneGraph(false,true);
    root->add(positionMenu);
    root->add(rotationMenu);
    root->add(betweenMenu);
    root->add(nodeBack);
    root->add(nodeText);
    currentTime=SDL_GetTicks();
    menuDelay=currentTime;

    //Get sound
    openSound=soundCollect->getSound(sOpen);
    moveSound=soundCollect->getSound(sCoin);
}

//**********************************************************************//

InventoryMenu::~InventoryMenu(){
    delete root;

    delete currentMaterial;
    delete materialBack;
}

//**********************************************************************//

void InventoryMenu::visualization(Context & cv){
    if(activateMenu)
        root->visualization(cv);
}

//**********************************************************************//

void InventoryMenu::updateState(GameState & gameState){
    vec3f posHero;
    if(!gameState.movie->isActivated() && !gameState.deadMenu->isActivate() && !gameState.pauseMenu->isActivate()
       && !gameState.camera->isViewMode()){
        float time=gameState.time;
        ControllerManager * controller=gameState.controller;

        if(time-currentTime>200)
            currentTime=time-50;

        if(controller->checkButton(cINVENTORY) && menuDelay<(time-600)){
            activateMenu=!activateMenu;
            menuDelay=time;
            openSound->play();
        }

        currentTime+=time-currentTime;
    }
}
