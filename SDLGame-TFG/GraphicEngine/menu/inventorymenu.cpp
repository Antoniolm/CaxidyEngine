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

    //////////////////////////////////
    //Shape for every item of the inventory

    /*vector<Material *> auxVector;

    for(int i=0;i<inventory->getSizeY();i++){
        for(int j=0;j<inventory->getSizeX();j++){
            auxVector.push_back(new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/TEX_crystal.png"));
        }
        itemView.push_back(auxVector);
        auxVector.clear();
    }

    Matrix4f * selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.275,0.442,0.8);

    Matrix4f * scaleItem=new Matrix4f();
    scaleItem->scale(0.075,0.525,0.1);

    NodeSceneGraph * items0x0=new NodeSceneGraph(false,true);
    items0x0->add(selectedPositionItem);
    items0x0->add(scaleItem);
    items0x0->add(itemView[0][0]);
    items0x0->add(meshCollect->getMesh(TEXT));

    //0.208f,0.288f,0.0f
    NodeSceneGraph * items0x1=new NodeSceneGraph(false,true);
    items0x1->add(selectedPositionItem);
    items0x1->add(scaleItem);
    items0x1->add(itemView[0][1]);
    items0x1->add(meshCollect->getMesh(TEXT));

    NodeSceneGraph * matrixItems=new NodeSceneGraph(false,true);
    matrixItems->add(items0x0);
    matrixItems->add(items0x1);*/


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
    //root->add(matrixItems);
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
    delete inventory;

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
            bool hasMovement=false;

            if(controller->checkButton(cUP) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentItemY-=1;
                menuDelay=time;

                if(currentItemY<0){
                    auxMatrix->translation(0.0f,-distItem.y*(inventory->getSizeY()-1),0.0f);
                    currentItemY=inventory->getSizeY()-1;
                }
                else
                    auxMatrix->translation(0.0f,distItem.y,0.0f);

                hasMovement=true;
            }
            if(controller->checkButton(cDOWN) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentItemY+=1;
                menuDelay=time;

                if(currentItemY==inventory->getSizeY()){
                    auxMatrix->translation(0.0f,distItem.y*(inventory->getSizeY()-1),0.0f);
                    currentItemY=0;
                }
                else
                    auxMatrix->translation(0.0f,-distItem.y,0.0f);

                hasMovement=true;
            }
            if(controller->checkButton(cLEFT) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentItemX-=1;
                menuDelay=time;

                if(currentItemX<0){
                    auxMatrix->translation(distItem.x*(inventory->getSizeX()-1),0.0f,0.0f);
                    currentItemX=inventory->getSizeX()-1;
                }
                else
                    auxMatrix->translation(-distItem.x,0.0,0.0f);

                hasMovement=true;
            }
            if(controller->checkButton(cRIGHT) && menuDelay<(time-300)){ //If the user push the action move on the menu
                currentItemX+=1;
                menuDelay=time;

                if(currentItemX==inventory->getSizeX()){
                    auxMatrix->translation(-distItem.x*(inventory->getSizeX()-1),0.0f,0.0f);
                    currentItemX=0;
                }
                else
                    auxMatrix->translation(distItem.x,0.0,0.0f);

                hasMovement=true;
            }

            if(hasMovement){
                selectedPosition->product(auxMatrix->getMatrix());
                moveSound->play();
            }

        }

        currentTime+=time-currentTime;
    }
}

//**********************************************************************//

bool InventoryMenu::addEquip(Equipment * aEquip){
    bool result=false;

    pair<int,int> positionSlot = inventory->emptySlot();
    if( positionSlot.first!=-1){
        result=true;
        inventory->addItem(positionSlot.first,positionSlot.second,aEquip);

        //Change texture
    }

    return result;
}
