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

#include "inventorymenugame.h"
#include "rootmapgame.h"

InventoryMenuGame::InventoryMenuGame(){
    //ctor
}

//**********************************************************************//

InventoryMenuGame::InventoryMenuGame(vec3f initPos,vec3f dItem,string fileName){

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
    materialCurrentMaterial=new Material(vec3f(1.0f, 1.0f, 1.0f),vec3f(1.0f, 0.5f, 0.5f),vec3f(0.5f, 0.5f, 0.5f),32.0f,"./textures/void.png");
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
    selectedPosition->translation(-0.273,0.44,0.82);

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
    positionImgItem->translation(-0.83,0.059,0.8);

    scaleMenu=new Matrix4f();
    scaleMenu->scale(0.044,0.265,0.1);

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


InventoryMenuGame::~InventoryMenuGame()
{
    //dtor
}

//**********************************************************************//

void InventoryMenuGame::visualization(Context & cv){
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

void InventoryMenuGame::updateState(GameState & gameState){

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
                moveSound->stop();
                vec3f posHero=gameState.camera->getPosition();

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

                Hero * hero=dynamic_cast<RootMapGame*>(gameState.rootMap)->getHero();
                //Current Level
                if(hero->getLevel()!=currentLevel){
                    currentLevel=hero->getLevel();

                    std::stringstream levelStream;
                    levelStream<< currentLevel;
                    levelText->setMessage(levelStream.str());
                    levelText->init(750.0,60.0);
                }

                //Current Life
                if(hero->getMaxLife()!=currentLife){
                    currentLife=hero->getMaxLife();

                    std::stringstream lifeStream;
                    lifeStream<< currentLife;
                    lifeText->setMessage(lifeStream.str());
                    lifeText->init(750.0,60.0);
                }

                //Current Damage
                if(hero->getDamage()!=currentDmg){
                    currentDmg=hero->getDamage();

                    std::stringstream dmgStream;
                    dmgStream<< currentDmg;
                    damageText->setMessage(dmgStream.str());
                    damageText->init(750.0,60.0);
                }

                //Current Armour
                if(hero->getArmour()!=currentArmour){
                    currentArmour=hero->getArmour();

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

            //If the user push the action move on the menu and is not removing a equip
            if(controller->checkButton(cACTION) && !isConfirming &&  menuDelay<(time-300)){
                if(inventory->equipItem(currentItemX,currentItemY)){
                    Equipment * equip=inventory->getItem(currentItemX,currentItemY);

                    //gameState.rootMap->getHero()->setEquipment(equip);
                    equippedItem[equip->getEquipType()]->translation(-0.273+(currentItemX*distItem.x),0.455-(currentItemY*distItem.y),0.9f);
                    moveSound->play();
                }
                menuDelay=time;
            }

            //If the user push the action move on the menu and is removing a equip
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
                    moveSound->play();

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

