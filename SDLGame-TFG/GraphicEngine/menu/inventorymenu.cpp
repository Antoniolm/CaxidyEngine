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

#include "inventorymenu.h"

InventoryMenu::InventoryMenu(vec3f initPos,vec3f dItem,string fileName,Inventory & inv){

    currentOption=0;
    currentItemX=0;
    currentItemY=0;
    activateMenu=false;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();
    initialPosition=initPos;
    distItem=dItem;
    inventory=&inv;

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/selectItem.png");
    materialBack=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,fileName.c_str());

    positionMenu=new Matrix4f();
    positionMenu->identity();

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.2);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ///////////////////////
    //Text
    selectedPosition=new Matrix4f();
    selectedPosition->translation(-0.275,0.442,0.8);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.088,0.535,0.1);

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
            if(activateMenu){
                posHero=gameState.rootMap->getHero()->getPosition();
                positionMenu->translation(posHero.x+initialPosition.x,posHero.y+initialPosition.y,posHero.z+initialPosition.z);

                //Consume the current events -> User has to push again the buttons
                controller->setState(false,cUP);
                controller->setState(false,cDOWN);
                controller->setState(false,cLEFT);
                controller->setState(false,cRIGHT);
                controller->setState(false,cINVENTORY);
            }
        }

        if(activateMenu){
            Matrix4f * auxMatrix=new Matrix4f();
            if(controller->checkButton(cUP) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentItemY-=1;
                menuDelay=time;
                auxMatrix->translation(0.0f,distItem.y,0.0f);
                selectedPosition->product(auxMatrix->getMatrix());
                moveSound->play();
            }
            if(controller->checkButton(cDOWN) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentItemY+=1;
                menuDelay=time;
                auxMatrix->translation(0.0f,-distItem.y,0.0f);
                selectedPosition->product(auxMatrix->getMatrix());
                moveSound->play();
            }
            if(controller->checkButton(cLEFT) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentItemX-=1;
                menuDelay=time;
                auxMatrix->translation(-distItem.x,0.0,0.0f);
                selectedPosition->product(auxMatrix->getMatrix());
                moveSound->play();
            }
            if(controller->checkButton(cRIGHT) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentItemX+=1;
                menuDelay=time;
                auxMatrix->translation(distItem.x,0.0,0.0f);
                selectedPosition->product(auxMatrix->getMatrix());
                moveSound->play();
            }

        }

        currentTime+=time-currentTime;
    }
}
