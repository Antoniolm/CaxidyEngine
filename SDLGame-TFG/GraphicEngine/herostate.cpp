// *********************************************************************
// **
// ** Copyright (C) 2016-2017 Antonio David López Machado
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

#include "herostate.h"

HeroState::HeroState(){
    currentCoin=-10;
    currentLife=110;
    currentExp=0;
    currentLevel=0;

    isLevelUp=false;

    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 20);
    SDL_Color color= {0,255,0};
    coinText=new Text(mVOID,font,color,false);

    levelUp=new Text(mVOID,font,color,false);
    levelUp->setMessage("¡Level Up!");
    levelUp->init(1000.0,80.0);

    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();

    position=vec4f(0.0,6.70,11.0,1.0);

    positionState=new Matrix4f();
    positionState->translation(position.x,position.y,position.z);

    Matrix4f * rotationMenu=new Matrix4f();
    rotationMenu->rotation(20,1.0,0.0,0.0);

    ////////////////////////
    // Exp Node
    Matrix4f * positionExp=new Matrix4f();
    positionExp->translation(-0.125,-0.04,0.05);

    scaleExp=new Matrix4f();
    scaleExp->scale(0.0,0.7,1.0);

    Matrix4f * positiontoScale=new Matrix4f();
    positiontoScale->translation(0.125,0.0,0.0);

    NodeSceneGraph * nodeExp=new NodeSceneGraph(false,true);
    nodeExp->add(positionExp);
    nodeExp->add(scaleExp);
    nodeExp->add(positiontoScale);
    nodeExp->add(materialCollect->getMaterial(mEXP));
    nodeExp->add(meshCollect->getMesh(TEXT));

    ///////////////////////
    //Life Node

    Matrix4f * positionLife=new Matrix4f();
    positionLife->translation(-0.125,0.025,0.05);

    scaleLife=new Matrix4f();
    scaleLife->scale(1.0,1.0,1.0);

    positiontoScale=new Matrix4f();
    positiontoScale->translation(0.125,0.0,0.0);

    NodeSceneGraph * nodeLife=new NodeSceneGraph(false,true);
    nodeLife->add(positionLife);
    nodeLife->add(scaleLife);
    nodeLife->add(positiontoScale);
    nodeLife->add(materialCollect->getMaterial(mLIFE));
    nodeLife->add(meshCollect->getMesh(TEXT));

    Matrix4f * positionText=new Matrix4f();
    positionText->translation(-0.65,0.0,0.0);

    Matrix4f * scaleMenu=new Matrix4f();
    scaleMenu->scale(0.3,0.4,1.0);

    NodeSceneGraph * nodeLifeBar=new NodeSceneGraph(false,true);
    nodeLifeBar->add(positionText);
    nodeLifeBar->add(scaleMenu);
    nodeLifeBar->add(materialCollect->getMaterial(mLIFEBAR));
    nodeLifeBar->add(meshCollect->getMesh(TEXT));
    nodeLifeBar->add(nodeLife);
    nodeLifeBar->add(nodeExp);

    ///////////////////////
    //Coin Node
    Matrix4f * positionCoin=new Matrix4f();
    positionCoin->translation(+0.65,0.0,0.0);

    Matrix4f * scaleCoin=new Matrix4f();
    scaleCoin->scale(0.03,0.3,1.0);

    NodeSceneGraph * nodeCrystal=new NodeSceneGraph(false,true);
    nodeCrystal->add(positionCoin);
    nodeCrystal->add(scaleCoin);
    nodeCrystal->add(materialCollect->getMaterial(mCRYSDRAW));
    nodeCrystal->add(meshCollect->getMesh(TEXT));

    root=new NodeSceneGraph(false,true);
    root->add(positionState);
    root->add(rotationMenu);
    root->add(nodeCrystal);
    root->add(nodeLifeBar);
    currentTime=SDL_GetTicks();
    delayTime=currentTime;
}

//**********************************************************************//

HeroState::~HeroState(){
    delete root;
    delete coinText;
    delete levelUp;
}

//**********************************************************************//

void HeroState::visualization(Context & cv){
    if(visibleState){
        root->visualization(cv);
        coinText->visualization(cv);
    }
    if(isLevelUp){
        levelUp->visualization(cv);
    }
}

//**********************************************************************//

void HeroState::updateState(GameState & gameState){
    Hero * hero=gameState.rootMap->getHero();
    vec3f posHero=hero->getPosition();
    visibleState=true;
    float time=gameState.time;

    positionState->translation(posHero.x,posHero.y+7.4,posHero.z+10.6);
    coinText->setPosition(vec3f(posHero.x+0.74,posHero.y+7.4,posHero.z+10.6));
    levelUp->setPosition(vec3f(posHero.x-0.59,posHero.y+7.3,posHero.z+10.65));

    int heroLife=hero->getLife();
    int heroExp=hero->getExp();
    int heroCoin=hero->getCoin();
    int heroLevel=hero->getLevel();

    if(gameState.inventoryMenu->isActivate() || gameState.pauseMenu->isActivate() || gameState.deadMenu->isActivate()
       || gameState.camera->isSpeakMode() || gameState.camera->isMoveSpeakMode())
        visibleState=false;

    //if the life was changed
    if(currentLife!=heroLife && heroLife>=0){
        scaleLife->scale((float)heroLife/(float)hero->getMaxLife(),1.0,1.0);
    }

    //If the experience value was changes
    if(currentExp!=heroExp || currentLevel!=heroLevel){

        if(currentLevel!=heroLevel){
            isLevelUp=true;
            delayTime=currentTime;
        }

        currentMaxExp=hero->getMaxExp();

        scaleExp->scale((float)heroExp/(float)currentMaxExp,0.7,1.0);
    }

     if(delayTime<(time-1500)){
        isLevelUp=false;
     }

    //if the value of coin was changed
    if(currentCoin!=heroCoin){
        std::stringstream coin;
        coin<< heroCoin;
        coinText->setMessage(coin.str());
        coinText->init(500.0,40.0);
    }

    currentLife=heroLife;
    currentExp=heroExp;
    currentCoin=heroCoin;
    currentLevel=heroLevel;

    currentTime+=time-currentTime;
}
