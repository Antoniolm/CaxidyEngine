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
    selectedPosition->translation(-0.272,0.439,0.8);

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
    root->add(createMatrixItems());
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
            else{
                selectedPosition->translation(-0.272,0.439,0.8);
                currentItemX=0;
                currentItemY=0;
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

            //Remove item
            if(controller->checkButton(cJUMP) && menuDelay<(time-300)){
                if(inventory->removeItem(currentItemX,currentItemY)){
                    itemView[currentItemY][currentItemX]->setTexture("./textures/void.png");
                    moveSound->play();
                }
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
    if( positionSlot.first!=-1){ //If the inventory is not full
        result=true;
        inventory->addItem(positionSlot.first,positionSlot.second,aEquip);

        //Change texture
        itemView[positionSlot.second][positionSlot.first]->setTexture(aEquip->getImageProfile());
    }

    return result;
}

//**********************************************************************//

void InventoryMenu::clearInventory(){

    for(int i=0;i<inventory->getSizeY();i++){
        for(int j=0;j<inventory->getSizeX();j++){
            if(inventory->removeItem(j,i))
                itemView[i][j]->setTexture("./textures/void.png");
        }
    }
}

//**********************************************************************//

NodeSceneGraph * InventoryMenu::createMatrixItems(){
    //////////////////////////////////
    //Shape for every item of the inventory
    MeshCollection * meshCollect =MeshCollection::getInstance();

    for(int i=0;i<inventory->getSizeY();i++){
        for(int j=0;j<inventory->getSizeX();j++){
            itemView[i][j]=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/void.png");
        }
    }

    Matrix4f * selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.272,0.439,0.8);

    Matrix4f * scaleItem=new Matrix4f();
    scaleItem->scale(0.074,0.48,0.1);

    NodeSceneGraph * items0x0=new NodeSceneGraph(false,true);
    items0x0->add(selectedPositionItem);
    items0x0->add(scaleItem);
    items0x0->add(itemView[0][0]);
    items0x0->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][1]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.062,0.439,0.8);

    NodeSceneGraph * items0x1=new NodeSceneGraph(false,true);
    items0x1->add(selectedPositionItem);
    items0x1->add(scaleItem);
    items0x1->add(itemView[0][1]);
    items0x1->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][2]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.142,0.439,0.8);

    NodeSceneGraph * items0x2=new NodeSceneGraph(false,true);
    items0x2->add(selectedPositionItem);
    items0x2->add(scaleItem);
    items0x2->add(itemView[0][2]);
    items0x2->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][3]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.345,0.439,0.8);

    NodeSceneGraph * items0x3=new NodeSceneGraph(false,true);
    items0x3->add(selectedPositionItem);
    items0x3->add(scaleItem);
    items0x3->add(itemView[0][3]);
    items0x3->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][4]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.555,0.439,0.8);

    NodeSceneGraph * items0x4=new NodeSceneGraph(false,true);
    items0x4->add(selectedPositionItem);
    items0x4->add(scaleItem);
    items0x4->add(itemView[0][4]);
    items0x4->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[0][5]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.757,0.439,0.8);

    NodeSceneGraph * items0x5=new NodeSceneGraph(false,true);
    items0x5->add(selectedPositionItem);
    items0x5->add(scaleItem);
    items0x5->add(itemView[0][5]);
    items0x5->add(meshCollect->getMesh(TEXT));


    ///////////////////////////////////////////////////////////////////
    // Row 2

    /////////////////////////
    // Item[1][0]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.272,0.15,0.8);

    NodeSceneGraph * items1x0=new NodeSceneGraph(false,true);
    items1x0->add(selectedPositionItem);
    items1x0->add(scaleItem);
    items1x0->add(itemView[1][0]);
    items1x0->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][1]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.062,0.15,0.8);

    NodeSceneGraph * items1x1=new NodeSceneGraph(false,true);
    items1x1->add(selectedPositionItem);
    items1x1->add(scaleItem);
    items1x1->add(itemView[1][1]);
    items1x1->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][2]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.142,0.15,0.8);

    NodeSceneGraph * items1x2=new NodeSceneGraph(false,true);
    items1x2->add(selectedPositionItem);
    items1x2->add(scaleItem);
    items1x2->add(itemView[1][2]);
    items1x2->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][3]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.345,0.15,0.8);

    NodeSceneGraph * items1x3=new NodeSceneGraph(false,true);
    items1x3->add(selectedPositionItem);
    items1x3->add(scaleItem);
    items1x3->add(itemView[1][3]);
    items1x3->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][4]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.555,0.15,0.8);

    NodeSceneGraph * items1x4=new NodeSceneGraph(false,true);
    items1x4->add(selectedPositionItem);
    items1x4->add(scaleItem);
    items1x4->add(itemView[1][4]);
    items1x4->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[1][5]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.757,0.15,0.8);

    NodeSceneGraph * items1x5=new NodeSceneGraph(false,true);
    items1x5->add(selectedPositionItem);
    items1x5->add(scaleItem);
    items1x5->add(itemView[1][5]);
    items1x5->add(meshCollect->getMesh(TEXT));

    ///////////////////////////////////////////////////////////////////
    // Row 3

    /////////////////////////
    // Item[2][0]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.272,-0.139,0.8);

    NodeSceneGraph * items2x0=new NodeSceneGraph(false,true);
    items2x0->add(selectedPositionItem);
    items2x0->add(scaleItem);
    items2x0->add(itemView[2][0]);
    items2x0->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][1]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(-0.062,-0.139,0.8);

    NodeSceneGraph * items2x1=new NodeSceneGraph(false,true);
    items2x1->add(selectedPositionItem);
    items2x1->add(scaleItem);
    items2x1->add(itemView[2][1]);
    items2x1->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][2]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.142,-0.139,0.8);

    NodeSceneGraph * items2x2=new NodeSceneGraph(false,true);
    items2x2->add(selectedPositionItem);
    items2x2->add(scaleItem);
    items2x2->add(itemView[2][2]);
    items2x2->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][3]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.345,-0.139,0.8);

    NodeSceneGraph * items2x3=new NodeSceneGraph(false,true);
    items2x3->add(selectedPositionItem);
    items2x3->add(scaleItem);
    items2x3->add(itemView[2][3]);
    items2x3->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][4]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.555,-0.139,0.8);

    NodeSceneGraph * items2x4=new NodeSceneGraph(false,true);
    items2x4->add(selectedPositionItem);
    items2x4->add(scaleItem);
    items2x4->add(itemView[2][4]);
    items2x4->add(meshCollect->getMesh(TEXT));

    /////////////////////////
    // Item[2][5]

    selectedPositionItem=new Matrix4f();
    selectedPositionItem->translation(0.757,-0.139,0.8);

    NodeSceneGraph * items2x5=new NodeSceneGraph(false,true);
    items2x5->add(selectedPositionItem);
    items2x5->add(scaleItem);
    items2x5->add(itemView[2][5]);
    items2x5->add(meshCollect->getMesh(TEXT));


    //Create matrix

    NodeSceneGraph * matrixItems=new NodeSceneGraph(false,true);
    matrixItems->add(items0x0);
    matrixItems->add(items0x1);
    matrixItems->add(items0x2);
    matrixItems->add(items0x3);
    matrixItems->add(items0x4);
    matrixItems->add(items0x5);

    matrixItems->add(items1x0);
    matrixItems->add(items1x1);
    matrixItems->add(items1x2);
    matrixItems->add(items1x3);
    matrixItems->add(items1x4);
    matrixItems->add(items1x5);

    matrixItems->add(items2x0);
    matrixItems->add(items2x1);
    matrixItems->add(items2x2);
    matrixItems->add(items2x3);
    matrixItems->add(items2x4);
    matrixItems->add(items2x5);


    return matrixItems;
}

