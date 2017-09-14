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
#include "../VideoGame/inventory.h"
#include "collection/meshcollection.h"

InventoryMenu::InventoryMenu(vec3f initPos,vec3f dItem,string fileName){

    currentOption=0;
    currentItemX=0;
    currentItemY=0;
    currentLevel=0;

    currentLife=0;
    currentDmg=0;
    currentArmour=0;

    lastSelection=0;

    activateMenu=false;
    isConfirming=false;
    MeshCollection * meshCollect=MeshCollection::getInstance();
    materialCollect=MaterialCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();
    initialPosition=initPos;
    distItem=dItem;
    inventory=new Inventory(6,3);

    //////////////////
    // Texts

    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf",20);
    SDL_Color color= {255,255,255};
    damageItemText=new Text(mVOID,font,color,false);
    armourItemText=new Text(mVOID,font,color,false);
    lifeItemText=new Text(mVOID,font,color,false);
    nameItemText=new Text(mVOID,font,color,false);

    levelText=new Text(mVOID,font,color,false);
    lifeText=new Text(mVOID,font,color,false);
    damageText=new Text(mVOID,font,color,false);
    armourText=new Text(mVOID,font,color,false);

    /////////////////
    //Create interface

    currentMaterial=new Material(vec3f(0.6f, 0.6f, 0.6f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/selectItem.png");
    materialBack=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,fileName.c_str());
    confirmMaterial=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/cfmDelete.png");
    materialCurrentMaterial=materialCollect->getMaterial(mVOID);
    materialEquipped=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/equipItem.png");

    initInfoItem();

    positionMenu=new Matrix4f();
    positionMenu->identity();

    Matrix4f * betweenMenu=new Matrix4f();
    betweenMenu->translation(0.0,0.0,-0.2);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ///////////////////////
    //Text
    selectedPosition=new Matrix4f();
    selectedPosition->translation(-0.273,0.44,0.8);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.083,0.535,0.1);

    NodeSceneGraph * nodeText=new NodeSceneGraph(false,true);
    nodeText->add(selectedPosition);
    nodeText->add(scaleMenu);
    nodeText->add(currentMaterial);
    nodeText->add(meshCollect->getMesh(TEXT));

    ////////////////////////
    // Equipped item
    equippedItem[0]=new Matrix4f();
    equippedItem[0]->translation(-0.272,0.455,0.9);

    Matrix4f * scaleItem=new Matrix4f();
    scaleItem->scale(0.074,0.48,0.1);

    NodeSceneGraph * equippedx0=new NodeSceneGraph(false,true);
    equippedx0->add(equippedItem[0]);
    equippedx0->add(scaleItem);
    equippedx0->add(materialEquipped);
    equippedx0->add(meshCollect->getMesh(TEXT));

    equippedItem[1]=new Matrix4f();
    equippedItem[1]->translation(-0.062,0.455,0.9);

    NodeSceneGraph * equippedx1=new NodeSceneGraph(false,true);
    equippedx1->add(equippedItem[1]);
    equippedx1->add(scaleItem);
    equippedx1->add(materialEquipped);
    equippedx1->add(meshCollect->getMesh(TEXT));

    equippedItem[2]=new Matrix4f();
    equippedItem[2]->translation(0.142,0.455,0.9);

    NodeSceneGraph * equippedx2=new NodeSceneGraph(false,true);
    equippedx2->add(equippedItem[2]);
    equippedx2->add(scaleItem);
    equippedx2->add(materialEquipped);
    equippedx2->add(meshCollect->getMesh(TEXT));


    ////////////////////////
    // Image profile
    Matrix4f * positionImgItem=new Matrix4f();
    positionImgItem->translation(-0.827,0.0535,0.8);

    scaleMenu=new Matrix4f();
    scaleMenu->scale(0.041,0.263,0.1);

    NodeSceneGraph * imgItem=new NodeSceneGraph(false,true);
    imgItem->add(positionImgItem);
    imgItem->add(scaleMenu);
    imgItem->add(materialCurrentMaterial);
    imgItem->add(meshCollect->getMesh(TEXT));


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
    root->add(imgItem);
    root->add(equippedx0);
    root->add(equippedx1);
    root->add(equippedx2);

    ////////////////////////////
    // Confirm material

    Matrix4f * betweenMenuCInt=new Matrix4f();
    betweenMenuCInt->translation(0.2,0.4,0.9);

    Matrix4f * scaleConfMat=new Matrix4f();
    scaleConfMat->scale(0.25,0.5,1.0);

    confirmInterface=new NodeSceneGraph(false,true);
    confirmInterface->add(positionMenu);
    confirmInterface->add(rotationMenu);
    confirmInterface->add(betweenMenuCInt);
    confirmInterface->add(scaleConfMat);
    confirmInterface->add(confirmMaterial);
    confirmInterface->add(meshCollect->getMesh(TEXT));

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
    delete confirmMaterial;
    delete materialEquipped;

    delete damageItemText;
    delete armourItemText;
    delete lifeItemText;
    delete nameItemText;

    delete levelText;
    delete lifeText;
    delete damageText;
    delete armourText;

    delete inventory;
}

//**********************************************************************//

void InventoryMenu::visualization(Context & cv){
    if(activateMenu){
        root->visualization(cv);

        damageItemText->visualization(cv);
        armourItemText->visualization(cv);
        lifeItemText->visualization(cv);
        nameItemText->visualization(cv);

        levelText->visualization(cv);
        lifeText->visualization(cv);
        damageText->visualization(cv);
        armourText->visualization(cv);

        if(isConfirming)
            confirmInterface->visualization(cv);
    }

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
                //posHero=gameState.rootMap->getHero()->getPosition();
                posHero=gameState.camera->getPosition();

                //Adjust the position of the menu and its information text
                positionMenu->translation(posHero.x+initialPosition.x,posHero.y+initialPosition.y,posHero.z+initialPosition.z);
                nameItemText->setPosition(vec3f(posHero.x+initialPosition.x-0.65,posHero.y+initialPosition.y+0.8,posHero.z+initialPosition.z+1.4));
                lifeItemText->setPosition(vec3f(posHero.x+initialPosition.x-0.7,posHero.y+initialPosition.y+0.6,posHero.z+initialPosition.z+1.4));
                damageItemText->setPosition(vec3f(posHero.x+initialPosition.x-0.7,posHero.y+initialPosition.y+0.5,posHero.z+initialPosition.z+1.4));
                armourItemText->setPosition(vec3f(posHero.x+initialPosition.x-0.7,posHero.y+initialPosition.y+0.4,posHero.z+initialPosition.z+1.4));

                levelText->setPosition(vec3f(posHero.x+initialPosition.x-0.677,posHero.y+initialPosition.y+1.507,posHero.z+initialPosition.z+1.4));
                lifeText->setPosition(vec3f(posHero.x+initialPosition.x-0.677,posHero.y+initialPosition.y+1.4,posHero.z+initialPosition.z+1.4));
                damageText->setPosition(vec3f(posHero.x+initialPosition.x-0.677,posHero.y+initialPosition.y+1.3,posHero.z+initialPosition.z+1.4));
                armourText->setPosition(vec3f(posHero.x+initialPosition.x-0.677,posHero.y+initialPosition.y+1.18,posHero.z+initialPosition.z+1.4));

                //Current Level
                if(gameState.rootMap->getHero()->getLevel()!=currentLevel){
                    currentLevel=gameState.rootMap->getHero()->getLevel();

                    std::stringstream levelStream;
                    levelStream<< currentLevel;
                    levelText->setMessage(levelStream.str());
                    levelText->init(750.0,60.0);
                }

                //Current Life
                if(gameState.rootMap->getHero()->getMaxLife()!=currentLife){
                    currentLife=gameState.rootMap->getHero()->getMaxLife();

                    std::stringstream lifeStream;
                    lifeStream<< currentLife;
                    lifeText->setMessage(lifeStream.str());
                    lifeText->init(750.0,60.0);
                }

                //Current Damage
                if(gameState.rootMap->getHero()->getDamage()!=currentDmg){
                    currentDmg=gameState.rootMap->getHero()->getDamage();

                    std::stringstream dmgStream;
                    dmgStream<< currentDmg;
                    damageText->setMessage(dmgStream.str());
                    damageText->init(750.0,60.0);
                }

                //Current Armour
                if(gameState.rootMap->getHero()->getArmour()!=currentArmour){
                    currentArmour=gameState.rootMap->getHero()->getArmour();

                    std::stringstream armourStream;
                    armourStream<< currentArmour;
                    armourText->setMessage(armourStream.str());
                    armourText->init(750.0,60.0);
                }


                //Consume the current events -> User has to push again the buttons
                controller->setState(false,cUP);
                controller->setState(false,cDOWN);
                controller->setState(false,cLEFT);
                controller->setState(false,cRIGHT);
                controller->setState(false,cINVENTORY);

                changeSelectedItems();
            }
            else{
                selectedPosition->translation(-0.272,0.439,0.8);
                currentItemX=0;
                currentItemY=0;
                isConfirming=false;
            }
        }

        // If the menu is activated
        if(activateMenu){
            Matrix4f * auxMatrix=new Matrix4f();
            bool hasMovement=false;

            //If the user push the action move on the menu
            if(controller->checkButton(cUP) && !isConfirming && menuDelay<(time-300)){
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

            //If the user push the action move on the menu
            if(controller->checkButton(cDOWN) && !isConfirming && menuDelay<(time-300)){
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

            //If the user push the action move on the menu
            if(controller->checkButton(cLEFT) && !isConfirming && menuDelay<(time-300)){
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

            //If the user push the action move on the menu
            if(controller->checkButton(cRIGHT) && !isConfirming && menuDelay<(time-300)){
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

            //If the user push the action move on the menu
            if(controller->checkButton(cACTION) && !isConfirming &&  menuDelay<(time-300)){
                if(inventory->equipItem(currentItemX,currentItemY)){
                    Equipment * equip=inventory->getItem(currentItemX,currentItemY);

                    gameState.rootMap->getHero()->setEquipment(equip);
                    equippedItem[equip->getEquipType()]->translation(-0.272+(currentItemX*0.207f),0.455-(currentItemY*0.288f),0.9f);
                    moveSound->play();
                }
                menuDelay=time;
            }

            //If the user push the action move on the menu
            if(controller->checkButton(cACTION) && isConfirming &&  menuDelay<(time-300)){
                if(inventory->removeItem(currentItemX,currentItemY)){
                    itemView[currentItemY][currentItemX]->setTexture("./textures/void.png");
                    moveSound->play();
                }
                isConfirming=false;
                menuDelay=time;
            }

            //Remove item
            if(controller->checkButton(cJUMP) && menuDelay<(time-300)){
                Equipment * equip=inventory->getItem(currentItemX,currentItemY);

                //If the equip is not Null and if it is not equipped
                if(equip!=0 && !equip->isEquipped()){
                    menuDelay=time;

                    if(!isConfirming)
                        isConfirming=true;
                    else {
                        isConfirming=false;
                    }
                }
            }

            if(hasMovement){
                selectedPosition->product(auxMatrix->getMatrix());
                moveSound->play();
                changeSelectedItems();
            }

        }

        currentTime+=time-currentTime;
    }
}

//**********************************************************************//

void InventoryMenu::setInventory(const vector<Equipment*> & equipVec, const vector<vec2f> & posVec){

    for(int i=0;i<equipVec.size();i++){
        inventory->addItem(posVec[i].x,posVec[i].y,equipVec[i]);

        //Change texture
        itemView[(int)posVec[i].y][(int)posVec[i].x]->setMaterial(*materialCollect->getMaterial(equipVec[i]->getImageProfile()));

        //If is equipped changes the mesh of equippedItem
        if(equipVec[i]->isEquipped())
            equippedItem[equipVec[i]->getEquipType()]->translation(-0.272+((int)posVec[i].x*0.207f),0.455-((int)posVec[i].y*0.288f),0.9f);
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
        itemView[positionSlot.second][positionSlot.first]->setMaterial(*materialCollect->getMaterial(aEquip->getImageProfile()));
    }

    return result;
}

//**********************************************************************//

Inventory * InventoryMenu::getInventory(){
    return inventory;
}

//**********************************************************************//

void InventoryMenu::clearInventory(){

    for(int i=0;i<inventory->getSizeY();i++){
        for(int j=0;j<inventory->getSizeX();j++){
            if(inventory->removeItem(j,i))
                itemView[i][j]->setMaterial(*materialCollect->getMaterial(mVOID));
        }
    }

    //Clear equippedItem
    equippedItem[0]->translation(-0.272,0.455,0.9f);
    equippedItem[1]->translation(-0.272+0.207f,0.455,0.9f);
    equippedItem[2]->translation(-0.272+(2*0.207f),0.455,0.9f);
}

//**********************************************************************//

Equipment * InventoryMenu::getEquippetItem(int aType){
    Equipment * result=0;

    for(int i=0;i<inventory->getSizeY() && result==0 ;i++){
        for(int j=0;j<inventory->getSizeX() && result==0 ;j++){
            Equipment * auxEquip=inventory->getItem(j,i);
            if(auxEquip!=0 && auxEquip->getEquipType()==(EquipmentType)aType && auxEquip->isEquipped())
                result=inventory->getItem(j,i);
        }
    }

    return result;
}

//**********************************************************************//

void InventoryMenu::initInfoItem(){

    nameItemText->setMessage("--");
    lifeItemText->setMessage("--");
    damageItemText->setMessage("--");
    armourItemText->setMessage("--");

    materialCurrentMaterial->setMaterial((*materialCollect->getMaterial("mVOID")));

    nameItemText->init(1250.0,80.0);
    lifeItemText->init(750.0,60.0);
    damageItemText->init(750.0,60.0);
    armourItemText->init(750.0,60.0);

}

//**********************************************************************//

void InventoryMenu::changeSelectedItems(){
    std::stringstream lifeText,armourText,damageText,nameText;

    if(!inventory->isEmpty(currentItemX,currentItemY)){

        Equipment * equip=inventory->getItem(currentItemX,currentItemY);

        lifeText<< equip->getLife();
        lifeItemText->setMessage(lifeText.str());
        lifeItemText->init(750.0,60.0);

        armourText<< equip->getArmour();
        armourItemText->setMessage(armourText.str());
        armourItemText->init(750.0,60.0);

        damageText<< equip->getDamage();
        damageItemText->setMessage(damageText.str());
        damageItemText->init(750.0,60.0);

        nameText<< equip->getName();
        nameItemText->setMessage(nameText.str());
        nameItemText->init(1250.0,80.0);

        materialCurrentMaterial->setMaterial((*materialCollect->getMaterial(equip->getImageProfile())));
        lastSelection=equip;

    }
    else {
        if(lastSelection!=0){
            initInfoItem();
        }
        lastSelection=0;
    }

}

//**********************************************************************//

NodeSceneGraph * InventoryMenu::createMatrixItems(){
    //////////////////////////////////
    //Shape for every item of the inventory
    MeshCollection * meshCollect=MeshCollection::getInstance();

    for(int i=0;i<inventory->getSizeY();i++){
        for(int j=0;j<inventory->getSizeX();j++){
            itemView[i][j]=new Material((*materialCollect->getMaterial("mVOID")));
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

