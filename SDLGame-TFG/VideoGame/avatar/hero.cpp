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

#include "hero.h"
#include "../equipment.h"
#include "projectile.h"

Hero::Hero(const rapidjson::Value & heroFeatures)
{
    acceleratedMove=new AcceleratedMovement();
    acceleratedMove->resetState();
    direction=FORWARD;
    soul=0;
    isMoving=false;
    isMoveCollision=false;
    isFalling=false;
    isJumping=false;
    isHitting=false;
    isImpacted=false;
    isShielded=false;

    life=heroFeatures["life"].GetFloat();
    maxLife=heroFeatures["life"].GetFloat();
    damage=heroFeatures["damage"].GetFloat();
    armour=heroFeatures["armour"].GetFloat();

    currentExp=0;
    level=1;
    maxExperience=100;

    position=vec4f(heroFeatures["position"][0].GetFloat(),heroFeatures["position"][1].GetFloat(),heroFeatures["position"][2].GetFloat(),1.0);
    limitBottom=0.5;
    currentCoin=0;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();
    SoundCollection * soundCollect =SoundCollection::getInstance();

    //////////////////////////////////////////////////////
    /////           Initialize weapons               /////
    //////////////////////////////////////////////////////
    currentWeapon=new Equipment(heroFeatures["weaponMelee"]);
    currentWeapon->addLink();

    meleeWeapon=new Equipment(heroFeatures["weaponMelee"]);
    meleeWeapon->addLink();

    rangedWeapon=new Equipment(heroFeatures["weaponRanged"]);
    rangedWeapon->addLink();

    shieldEquipment=new Equipment(heroFeatures["shield"]);
    shieldEquipment->addLink();


    //////////////////////////////////////////////////////
    /////              All the sounds                /////
    //////////////////////////////////////////////////////
    heroSound.push_back(soundCollect->getSound(sWALK));
    heroSound.push_back(soundCollect->getSound(HHIT));
    heroSound.push_back(soundCollect->getSound(sSHIELD));
    heroSound.push_back(soundCollect->getSound(SHOOT));
    heroSound.push_back(soundCollect->getSound(sSWORD));
    heroSound.push_back(soundCollect->getSound(sJUMP));
    heroSound.push_back(soundCollect->getSound(sFALL));

    for(unsigned i=0;i<heroSound.size();i++)
        channelSound.push_back(-1);

    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    //Dialog for speak
    TTF_Font *font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 20);
    texts.push_back(new Text(mDIALOG,font));
    activatedTexts.push_back(false);

    //Dialog for actions
    font=TTF_OpenFont( "font/Xolonium-Regular.ttf", 40);
    texts.push_back(new Text(mADIALOG,font));
    activatedTexts.push_back(false);

    //Coin Text
    texts.push_back(new Text(mVOID,font,SDL_Color{0,255,0},false));
    activatedTexts.push_back(false);

    //Damage text
    texts.push_back(new Text(mVOID,font,SDL_Color{255,0,0},false));
    activatedTexts.push_back(false);

    //////////////////////////////////////////////////////
    /////                  LEGS                      /////
    //////////////////////////////////////////////////////

    //Create a new Movement
    Matrix4f * moveLegRight=new Matrix4f();
    moveLegRight->identity();
    moveMatrix.push_back(moveLegRight);

    Matrix4f * moveLegLeft=new Matrix4f();
    moveLegLeft->identity();
    moveMatrix.push_back(moveLegLeft);

    Matrix4f *transLeg=new Matrix4f();
    transLeg->translation(0.0,-0.3,0.0);

    Matrix4f *transLegSecond=new Matrix4f();
    transLegSecond->translation(0.0,-0.3,0.0);

    //Leg Left
    NodeSceneGraph * legLeft=new NodeSceneGraph();
    legLeft->add(moveLegLeft);
    legLeft->add(transLeg);
    legLeft->add(meshCollect->getMesh(heroFeatures["legLeft"].GetString()));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLegSecond);
    legRight->add(meshCollect->getMesh(heroFeatures["legRight"].GetString()));

    //////////////////////////////////////////////////////
    /////                  Arms                      /////
    //////////////////////////////////////////////////////


    //Create a new Movement
    Matrix4f * moveElbowRight=new Matrix4f();
    moveElbowRight->identity();
    moveMatrix.push_back(moveElbowRight);

    Matrix4f * moveElbowTRight=new Matrix4f();
    moveElbowTRight->identity();
    moveMatrix.push_back(moveElbowTRight);

    Matrix4f * moveElbowLeft=new Matrix4f();
    moveElbowLeft->identity();
    moveMatrix.push_back(moveElbowLeft);

    Matrix4f * moveElbowTLeft=new Matrix4f();
    moveElbowTLeft->identity();
    moveMatrix.push_back(moveElbowTLeft);

    Matrix4f * moveArmRight=new Matrix4f();
    moveArmRight->identity();
    moveMatrix.push_back(moveArmRight);

    Matrix4f * moveArmTRight=new Matrix4f();
    moveArmTRight->identity();
    moveMatrix.push_back(moveArmTRight);

    Matrix4f * moveArmLeft=new Matrix4f();
    moveArmLeft->identity();
    moveMatrix.push_back(moveArmLeft);

    Matrix4f * scaleHandInvert=new Matrix4f();
    scaleHandInvert->scale(1.0,1.0,-1.0);

    Matrix4f * transHand=new Matrix4f();
    transHand->translation(-0.075,-0.1,0.0);

    Matrix4f * transHandLeft=new Matrix4f();
    transHandLeft->translation(0.075,-0.1,0.0);

    Matrix4f * rotateXHand=new Matrix4f();
    rotateXHand->rotation(30,1,0,0);

    Matrix4f * rotateYHand=new Matrix4f();
    rotateYHand->rotation(180,0,1,0);

    Matrix4f * rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(180,0.0,1.0,0.0);

    Matrix4f * transElbow=new Matrix4f();
    transElbow->translation(0.0,-0.2,0.0);

    Matrix4f * transElbowSecond=new Matrix4f();
    transElbowSecond->translation(0.0,-0.2,0.0);

    Matrix4f * transArms=new Matrix4f();
    transArms->translation(0.0,-0.25,-0.1);

    Matrix4f * transArmsSecond=new Matrix4f();
    transArmsSecond->translation(0.0,-0.25,-0.1);

    //Arms
    NodeSceneGraph * handRight=new NodeSceneGraph();
    handRight->add(transElbow);
    handRight->add(moveElbowRight);
    handRight->add(moveElbowTRight);
    handRight->add(transHand);
    handRight->add(meshCollect->getMesh(heroFeatures["handRight"].GetString()));
    handRight->add(currentWeapon);

    NodeSceneGraph * handLeft=new NodeSceneGraph();
    handLeft->add(transElbowSecond);
    handLeft->add(moveElbowLeft);
    handLeft->add(moveElbowTLeft);
    handLeft->add(transHandLeft);
    handLeft->add(rotateYHand);
    handLeft->add(meshCollect->getMesh(heroFeatures["handLeft"].GetString()));
    handLeft->add(shieldEquipment);

    //Shoulder
    NodeSceneGraph * shoulderLeft=new NodeSceneGraph();
    shoulderLeft->add(meshCollect->getMesh(heroFeatures["arm"].GetString()));

    NodeSceneGraph * shoulderRight=new NodeSceneGraph();
    shoulderRight->add(rotateShoulder);
    shoulderRight->add(meshCollect->getMesh(heroFeatures["arm"].GetString()));

    //Arm left
    NodeSceneGraph * ArmLeft=new NodeSceneGraph();
    ArmLeft->add(transArms);
    ArmLeft->add(moveArmLeft);
    ArmLeft->add(handLeft);
    ArmLeft->add(shoulderLeft);

    //Arm Right
    NodeSceneGraph * ArmRight=new NodeSceneGraph();
    ArmRight->add(transArmsSecond);
    ArmRight->add(moveArmRight);
    ArmRight->add(moveArmTRight);
    ArmRight->add(handRight);
    ArmRight->add(shoulderRight);

    //////////////////////////////////////////////////////
    /////         Construction of the hero           /////
    //////////////////////////////////////////////////////

    Matrix4f * moveBodyHead=new Matrix4f();
    moveBodyHead->identity();
    moveMatrix.push_back(moveBodyHead);

    Matrix4f * moveTBodyHead=new Matrix4f();
    moveTBodyHead->identity();
    moveMatrix.push_back(moveTBodyHead);

    //Movement for our hero
    moveAvatar= new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(moveAvatar);

    Matrix4f *transLegScene=new Matrix4f();
    transLegScene->translation(-0.25,0.0,0.0);

    Matrix4f *transLegSceneI=new Matrix4f();
    transLegSceneI->translation(0.125,0.0,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.5,0.5,0.5);

    Matrix4f * trasnArms=new Matrix4f();
    trasnArms->translation(-0.5,0.0,0.0);

    Matrix4f *trasnArmsI=new Matrix4f();
    trasnArmsI->translation(0.25,0.415,0.1);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,0.7,0.0);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.0,0.05,0.0);

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    headNode->add(meshCollect->getMesh(heroFeatures["head"].GetString()));

    NodeSceneGraph * chest_Arms_HeadNode=new NodeSceneGraph();
    chest_Arms_HeadNode->add(transChest);
    chest_Arms_HeadNode->add(moveTBodyHead);
    chest_Arms_HeadNode->add(moveBodyHead);
    chest_Arms_HeadNode->add(headNode);
    chest_Arms_HeadNode->add(meshCollect->getMesh(heroFeatures["body"].GetString()));
    chest_Arms_HeadNode->add(trasnArmsI);
    chest_Arms_HeadNode->add(ArmLeft);
    chest_Arms_HeadNode->add(trasnArms);
    chest_Arms_HeadNode->add(ArmRight);

    root->add(materialCollect->getMaterial(heroFeatures["material"].GetString()));
    root->add(chest_Arms_HeadNode);
    root->add(transLegSceneI);
    root->add(legLeft);
    root->add(transLegScene);
    root->add(legRight);
    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
    hitDelay=currentTime;
    dmgDelay=currentTime;
    shieldDelay=currentTime;
    swapDelay=currentTime;
    shootDelay=currentTime;
    swordDelay=currentTime;

    //Init all animations of our hero
    initAnimation();
}

//**********************************************************************//

Hero::~Hero()
{
    for(vector<Text *>::iterator it = texts.begin() ; it != texts.end(); ++it){
        delete (*it);
    }

    for(vector<Projectile *>::iterator it = projectiles.begin() ; it != projectiles.end(); ++it){
        delete (*it);
    }

    delete root;
}

//**********************************************************************//

void Hero::visualization(Context & cv){
    root->visualization(cv);

    ////////////////////////////
    //DRAW texts
    ////////////////////////////
    for(unsigned i=0;i<texts.size();i++)
        if(activatedTexts[i])
            texts[i]->visualization(cv);

    ////////////////////////////
    //DRAW PROJECTILES
    ////////////////////////////
    vector<Projectile *>::iterator it;
    for(it=projectiles.begin();it!=projectiles.end();it++){
        (*it)->visualization(cv);
    }

    //Update visual range
    cv.minVisualPosition=vec3f(position.x-11,position.y-11,position.z);
    cv.maxVisualPosition=vec3f(position.x+11,position.y+11,position.z);
}

//**********************************************************************//

void Hero::updateState(GameState & gameState){
    bool hasMove=true;

    avatarDirection heroDir=direction;
    vec3f moveHero;
    currentMap=gameState.rootMap;
    ControllerManager * controller=gameState.controller;

    float time=gameState.time;
    RootMapGame * rootMap=dynamic_cast<RootMapGame *>(gameState.rootMap);

    if(time-currentTime>200)
        currentTime=time-50;

    //Case-> Push Left bottom
    if(controller->checkButton(cLEFT) && !controller->checkButton(cDOWN) && !controller->checkButton(cUP)){
        if(!isJumping && !isFalling){
            moveHero.x=-3.0;moveHero.z=0.0;
        }
        else{
            moveHero.x=-4.0;moveHero.z=0.0;
        }
        heroDir=LEFTWARD;
    }
    //Case-> Push Right bottom
    else if(controller->checkButton(cRIGHT) && !controller->checkButton(cDOWN) && !controller->checkButton(cUP)){
        if(!isJumping && !isFalling){
            moveHero.x=3.0;moveHero.z=0.0;
        }
        else{
            moveHero.x=4.0;moveHero.z=0.0;
        }
        heroDir=RIGHTWARD;
    }
    //Case-> Push Up bottom
    else if(controller->checkButton(cUP) && !controller->checkButton(cLEFT) && !controller->checkButton(cRIGHT)){
        if(!isJumping && !isFalling){
            moveHero.x=0.0;moveHero.z=-3.0;
        }
        else{
            moveHero.x=0.0;moveHero.z=-4.0;
        }
        heroDir=BACKWARD;
    }
    //Case-> Push Down bottom
    else if(controller->checkButton(cDOWN) && !controller->checkButton(cLEFT) && !controller->checkButton(cRIGHT)){
        if(!isJumping && !isFalling){
            moveHero.x=0.0;moveHero.z=3.0;
        }
        else{
            moveHero.x=0.0;moveHero.z=4.0;
        }
        heroDir=FORWARD;
    }
    //Case-> Push Dowm-Left bottoms
    else if(controller->checkButton(cDOWN) && controller->checkButton(cLEFT) ){
        if(!isJumping && !isFalling){
            moveHero.x=-2.0;moveHero.z=2.0;
        }
        else{
            moveHero.x=-3.0;moveHero.z=3.0;
        }
        heroDir=FOR_LEFTWARD;
    }
    //Case-> Push Dowm-Right bottoms
    else if(controller->checkButton(cDOWN) && controller->checkButton(cRIGHT) ){
        if(!isJumping && !isFalling){
            moveHero.x=2.0;moveHero.z=2.0;
        }
        else{
            moveHero.x=3.0;moveHero.z=3.0;
        }
        heroDir=FOR_RIGHTWARD;
    }
    //Case-> Push Up-Left bottoms
    else if(controller->checkButton(cUP) && controller->checkButton(cLEFT)){
        if(!isJumping && !isFalling){
            moveHero.x=-2.0;moveHero.z=-2.0;
        }
        else{
            moveHero.x=-3.0;moveHero.z=-3.0;
        }
        heroDir=BACK_LEFTWARD;
    }
    //Case-> Push Up-Right bottoms
    else if(controller->checkButton(cUP) && controller->checkButton(cRIGHT) ){
        if(!isJumping && !isFalling){
            moveHero.x=2.0;moveHero.z=-2.0;
        }
        else{
            moveHero.x=3.0;moveHero.z=-3.0;
        }
        heroDir=BACK_RIGHTWARD;
    }
    else{ //Case-> If not move
        hasMove=false;
        if(!isJumping && !isFalling){
            noMove();
        }
        heroSound[0]->stop(channelSound[0]);
        channelSound[0]=-1;
    }

    //Case-> Push S bottom to jump
    if(controller->checkButton(cJUMP) && !isJumping && !isFalling && !isImpacted && !isShielded && jumpDelay<(time-600) ){
        activeJump(vec3f(0.0f,15.0,0.0f),vec3f(0.0f,5.0f,0.0f));
        jumpDelay=time;
        channelSound[5]=heroSound[5]->play();
    }

    //Case-> Push L bottom to hit
    if(controller->checkButton(cATTACK) && !isShielded && soul==0){ //If hero is hitting
        if(!isHitting){
            animations.resetAnimation(1);
            animations.resetAnimation(5);
        }
        isHitting=true;
        hitDelay=time;
    }
    else { // If hero is not hitting -> resetAnimation
        if(hitDelay<(time-250) && currentWeapon->getEquipType()==MELEE){
            hitDelay=time;
            isHitting=false;
        }
        else if(hitDelay<(time-750) && currentWeapon->getEquipType()==RANGED){
            hitDelay=time;
            isHitting=false;
        }
    }

    //Case-> Push W bottom to shield
    if(controller->checkButton(cSHIELD) && !isHitting && soul==0){ //If hero is shielding
        isShielded=true;
        if(hasMove)
            animations.activate(3); //Activate animation
        else
            animations.activate(2); //Activate animation
    }
    else { //if not
        isShielded=false;
    }

    //Case-> Push Q bottom to swap weapon
    if(controller->checkButton(cSWAPWEAPON) && !isHitting && swapDelay<(time-500) ){ //If hero is shielding
        switch(currentWeapon->getEquipType()){
            case MELEE:
                currentWeapon->setEquip((*rangedWeapon));
            break;
            case RANGED:
                currentWeapon->setEquip((*meleeWeapon));
            break;
        }
        swapDelay=time;
    }

    //Move the body
    if(hasMove && !isImpacted && !isHitting){
        avatarDirection lastDir=direction;
        moveBody(moveHero,heroDir);
        if(!heroSound[0]->isPlaying(channelSound[0]))
            channelSound[0]=heroSound[0]->play();
        if(isShielded)
            changeDirection(lastDir);
    }

    //If the jump is activate
    if(isJumping){
        jump(time);
        animations.activate(4);
        heroSound[0]->stop(channelSound[0]);
        channelSound[0]=-1;
    }
    //If the jump is not activate
    else {
        bool isFallAux=isFalling;
        ObjectScene * object=gravity(time);

        if(!isShielded){
            animations.activate(5);
        }
        if(object!=0 && object->getDamage()!=0.0 && dmgDelay<(time-400)){ //If the object do damage
            takeDamage(object->getDamage());
            dmgDelay=time;
        }

        if(object!=0 && isFallAux)
            channelSound[6]=heroSound[6]->play();
    }

    //If the jump is activate
    if(isImpacted){
        impactMove(time);
    }

    //Check enemies for attack
    if(isHitting){
        vector<Enemy *> enemies=rootMap->getEnemyList()->getEnemies();
        vec3f posEnemy;float distance;
        int currentIndexAnimation;

        //Check the type of weapon
        switch(currentWeapon->getEquipType()){
            case MELEE: //If is the sword

                animations.activate(1);
                currentIndexAnimation=(animations.getAnimation())->getScriptState(7);
                if((currentIndexAnimation==0 || currentIndexAnimation==2 || currentIndexAnimation==4) && swordDelay<(time-250)){

                    //if the hero is in a hit animation not a rest animation
                    for(unsigned i=0;i<enemies.size();i++){ //Loop for all the enemies
                        posEnemy=enemies[i]->getPosition(); //Calculate the distance
                        distance=sqrt(pow(position.x-posEnemy.x,2.0)+pow(position.z-posEnemy.z,2.0));

                        if(distance<=1.0 && (position.y>posEnemy.y-1 && position.y<posEnemy.y+1)){//If is near
                            enemies[i]->takeDamage(position,direction,position,-(damage+currentWeapon->getDamage()
                                                                               +shieldEquipment->getDamage()),enemies); //Hit enemy
                        }
                    }
                    channelSound[4]=heroSound[4]->play();
                    swordDelay=time;
                }

            break;

            case RANGED: //if is the crossbow

                animations.activate(6);
                ScriptLMD * animationHit=animations.getAnimation();
                if(animationHit->getScriptState(6)==1 && shootDelay<(time-700)){
                    shootDelay=time;
                    projectiles.push_back(createProjectile(-(damage+currentWeapon->getDamage()
                                                           +shieldEquipment->getDamage())));
                    channelSound[3]=heroSound[3]->play();
                }
            break;
        }
    }


    //Update our vec4f position
    position=moveAvatar->product(vec4f());

    ////////////////////////////
    //UPDATE ANIMATION
    ////////////////////////////
    if(isMoving && !isFalling && !isJumping && !isHit() && !isImpacted && !isShielded){
        animations.activate(0);
    }
    if(!isMoving && !isFalling && !isJumping && !isHitting && !isImpacted && !isShielded){
        animations.activate(-1);
    }
    if(isHitting){
        switch(currentWeapon->getEquipType()){
            case MELEE: animations.activate(1);
            break;
            case RANGED: animations.activate(6);
            break;
            case eSHIELD:
            break;
        }
    }
    if(soul!=0){
        if(hasMove)
            animations.activate(8);
        else
            animations.activate(7);
    }

    if(animations.getState()!=-1){
        animations.update(time-currentTime);
        ScriptLMD * animation=animations.getAnimation();
        for(unsigned i=0;i<moveMatrix.size();i++)
                moveMatrix[i]->setMatrix(animation->readMatrix(i).getMatrix());
    }
    else noMove();

    ////////////////////////////
    //UPDATE TEXT
    ////////////////////////////
    for(unsigned i=0;i<texts.size();i++)
        if(activatedTexts[i])
            texts[i]->setPosition(vec3f(position.x,position.y+1.75f,position.z));

    //If hero does not take a coin in the last 300 ms
    if(coinDelay<time-700)
        activateDialog(false,2);
    currentTime+=(time-currentTime);

    //If hero does not take a coin in the last 300 ms
    if(dmgDelay<time-1200)
        activateDialog(false,3);

    ////////////////////////////
    //UPDATE PROJECTILES
    ////////////////////////////
    vector<Projectile *>::iterator it=projectiles.begin();

    while(it!=projectiles.end()){

        (*it)->updateState(gameState);
        if(!(*it)->isLive()){
            it=projectiles.erase(it);
        }
        else
            it++;
    }
}

//**********************************************************************//

void Hero::enableSound(bool value){
    for(unsigned i=0;i<heroSound.size();i++)
        if(value && channelSound[i]!=-1  && heroSound[i]->isPause(channelSound[i]))
            heroSound[i]->resume(channelSound[i]);
        else if(!value && channelSound[i]!=-1 && heroSound[i]->isPlaying(channelSound[i]))
            heroSound[i]->pause(channelSound[i]);
}

//**********************************************************************//

void Hero::setDialog(string message,int index){
    texts[index]->setPosition(vec3f(position.x,position.y+1.75f,position.z));
    texts[index]->setMessage(message);
    texts[index]->init();

    if(index==1){
        texts[1]->setScaleDialog(vec3f(0.25,0.9,0.5));
        texts[1]->setScaleText(vec3f(0.0,0.0,0.0));
    }
}

//**********************************************************************//

void Hero::activateDialog(bool value,int index){
    activatedTexts[index]=value;
}

//**********************************************************************//

void Hero::setCoin(int value){
    currentCoin=value;
}

//**********************************************************************//

void Hero::setSoul(Soul * aSoul){
    soul=aSoul;
}

//**********************************************************************//

void Hero::setLevelParameters(int cExp, int maxExp,int lvl){
    currentExp=cExp;
    maxExperience=maxExp;
    level=lvl;

    maxLife+=(level-1)*10;
    life=maxLife;
    damage+=(level-1)*2;
    armour+=(level-1)*2;
}

//**********************************************************************//

void Hero::setInfoParameters(int clife, int cDamage,int cArmour){
    maxLife=clife;
    damage=cDamage;
    armour=cArmour;
}

//**********************************************************************//

void Hero::addExperience(int value){
    currentExp+=value;
    if(currentExp>=maxExperience){
        currentExp=currentExp%maxExperience;
        level++;
        maxExperience=level*100;

        maxLife+=10;
        life=maxLife;
        damage+=2;
        armour+=2;
    }
}
//**********************************************************************//

void Hero::setEquipment(Equipment * anEquip){

    if(anEquip->getEquipType()==RANGED){
        rangedWeapon->setEquip(*anEquip);
    }

    else if(anEquip->getEquipType()==MELEE){
        meleeWeapon->setEquip(*anEquip);
    }
    else
        shieldEquipment->setEquip(*anEquip);


    if(currentWeapon->getEquipType()==anEquip->getEquipType())
        currentWeapon->setEquip(*anEquip);


}

//**********************************************************************//

void Hero::noMove(){
    animations.resetAnimation(0);
    for(unsigned i=0;i<moveMatrix.size();i++)
        moveMatrix[i]->identity();
    isMoving=false;
    animations.activate(-1);
}

//**********************************************************************//

bool Hero::isHit(){
    return isHitting;
}

//**********************************************************************//

bool Hero::isJump(){
    return isJumping;
}

//**********************************************************************//

bool Hero::isFall(){
    return isFalling;
}

//**********************************************************************//

 float Hero::getLife(){
    return life;
 }

//**********************************************************************//

 int Hero::getCoin(){
    return currentCoin;
 }

//**********************************************************************//

int Hero::getExp(){
    return currentExp;
}

//**********************************************************************//

int Hero::getMaxExp(){
    return maxExperience;
}

//**********************************************************************//

int Hero::getLevel(){
    return level;
}

//**********************************************************************//

int Hero::getDamage(){
    return damage;
}

//**********************************************************************//

int Hero::getArmour(){
    return armour;
}

//**********************************************************************//

Soul * Hero::getSoul(){
    return soul;
 }

//**********************************************************************//

 Equipment * Hero::getEquip(int aType){
    Equipment * equip=0;

    switch((EquipmentType)aType){
        case RANGED:
            equip=rangedWeapon;
            break;

        case MELEE:
            equip=meleeWeapon;
            break;

        case eSHIELD:
            equip=shieldEquipment;
            break;
    }

    return equip;

 }

//**********************************************************************//

 Equipment * Hero::getCurrentWeapon(){
    return currentWeapon;
 }


//**********************************************************************//

 void Hero::addCoin(int value){
    currentCoin+=value;
    int lastValue;
    coinDelay=currentTime;
    stringstream convert;

    if(activatedTexts[2]){ //if is activate the text ->//Join values
        string currentValue=texts[2]->getMessage();
        lastValue=atoi(currentValue.c_str());
        value+=lastValue;
    }

    convert << value;
    setDialog("+"+convert.str(),2);

    activateDialog(true,2);
 }

//**********************************************************************//

 void Hero::takeDamage(vec3f posAvatar,avatarDirection dirAvatar,float value){
     //check if the hero is shielding
     bool canShield=false;
    if(isShielded && detectShield(posAvatar,direction)) canShield=true;

    //check Distance
    float distance=sqrt(pow(position.x-posAvatar.x,2.0)+pow(position.z-posAvatar.z,2.0));

    if(detectHit(posAvatar,dirAvatar)&& dmgDelay<(currentTime-700) && !canShield && distance<1.0){

        //Calculate the damage that the hero will take
        addLife(value+(armour+currentWeapon->getArmour()+shieldEquipment->getArmour()));

        stringstream convert;
        if(activatedTexts[3]){ //if is activate the text ->//Join values
            int lastValue;
            string currentValue=texts[3]->getMessage();
            lastValue=atoi(currentValue.c_str());
            value+=lastValue;
        }
        dmgDelay=currentTime;

        convert << value;
        setDialog(convert.str(),3);

        activateDialog(true,3);
        if(!isImpacted) //if hero is not impacted in this moment
            activeImpact(dirAvatar);

        if(life>0)
            channelSound[1]=heroSound[1]->play();
    }
    if(detectHit(posAvatar,dirAvatar) && shieldDelay<(currentTime-700) && canShield && distance<1.0){
        channelSound[2]=heroSound[2]->play();
        shieldDelay=currentTime;
    }
 }

 //**********************************************************************//

 void Hero::takeDamage(float value){

    addLife(value);
    stringstream convert;
    if(activatedTexts[3]){  //if is activate the text ->//Join values
        int lastValue;
        string currentValue=texts[3]->getMessage();
        lastValue=atoi(currentValue.c_str());
        value+=lastValue;
    }
    dmgDelay=currentTime;

    convert << value;
    setDialog(convert.str(),3);

    activateDialog(true,3);

    if(life>0)
        channelSound[1]=heroSound[1]->play();
 }

//**********************************************************************//

Projectile * Hero::createProjectile(float damage){
    vec3f posProject;
    vec3f velocityProject;
    avatarDirection dirProject=RIGHTWARD;

    switch(direction){
        case FORWARD:
                posProject=vec3f(position.x,position.y,position.z+0.5);
                velocityProject=vec3f(0.0,0.0,4.0);
                dirProject=FORWARD;
            break;
        case BACKWARD:
                posProject=vec3f(position.x,position.y,position.z-0.5);
                velocityProject=vec3f(0.0,0.0,-4.0);
                dirProject=BACKWARD;
            break;
        case LEFTWARD:
                posProject=vec3f(position.x-0.5,position.y,position.z);
                velocityProject=vec3f(-4.0,0.0,0.0);
                dirProject=LEFTWARD;
            break;
        case RIGHTWARD:
                posProject=vec3f(position.x+0.5,position.y,position.z);
                velocityProject=vec3f(4.0,0.0,0.0);
                dirProject=RIGHTWARD;
            break;
        case FOR_LEFTWARD:
                posProject=vec3f(position.x-0.5,position.y,position.z+0.5);
                velocityProject=vec3f(-4.0,0.0,4.0);
                dirProject=FOR_LEFTWARD;
            break;
        case FOR_RIGHTWARD:
                posProject=vec3f(position.x+0.5,position.y,position.z+0.5);
                velocityProject=vec3f(4.0,0.0,4.0);
                dirProject=FOR_RIGHTWARD;
            break;
        case BACK_LEFTWARD:
                posProject=vec3f(position.x-0.5,position.y,position.z-0.5);
                velocityProject=vec3f(-4.0,0.0,-4.0);
                dirProject=BACK_LEFTWARD;
            break;
        case BACK_RIGHTWARD:
                posProject=vec3f(position.x+0.5,position.y,position.z-0.5);
                velocityProject=vec3f(4.0,0.0,-4.0);
                dirProject=BACK_RIGHTWARD;

            break;
    }

    return new Projectile(posProject,velocityProject,dirProject,damage,"ARROW","mARCHENEMY");
}


//**********************************************************************//
//                              PRIVATE                                 //
//**********************************************************************//

 void Hero::initAnimation(){

    //////////////////////////////////
    // 0- Move Animation
    /////////////////////////////////
    ScriptLMD * animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    OscillateRotation * oscillateLeg=new OscillateRotation(true,30,0,1,150,vec3f(1,0,0),2);
    OscillateRotation * oscillateLegSecond=new OscillateRotation(false,0,-30,1,150,vec3f(1,0,0),1);
    MatrixStatic * notMove=new MatrixStatic();

    //Movement to the first leg
    MatrixScript * LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.3,oscillateLeg);
    LegScriptLeft->add(0.3,oscillateLegSecond);


    //Movement to the second leg
    MatrixScript * LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.3,oscillateLegSecond);
    LegScriptRight->add(0.3,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    OscillateRotation * oscillateShoulder=new OscillateRotation(true,60,0,1,250,vec3f(1.0,0.0,0),2);

    //Movement to the first arm
    MatrixScript * ElbowScriptLeft=new MatrixScript();
    MatrixScript * ArmScriptLeft=new MatrixScript();
    MatrixScript * ElbowScriptTLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,oscillateShoulder);
    ArmScriptLeft->add(0.5,notMove);
    ElbowScriptTLeft->add(0.5,notMove);

    //Movement to the second arm
    MatrixScript * ElbowScriptRight=new MatrixScript();
    MatrixScript * ArmScriptRight=new MatrixScript();
    MatrixScript * ArmScriptTRight=new MatrixScript();
    MatrixScript * ElbowScriptTRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,oscillateShoulder);
    ArmScriptTRight->add(0.5,notMove);
    ElbowScriptTRight->add(0.5,notMove);


    //Add the script to our animation
    animation->add(ElbowScriptRight);
    animation->add(ElbowScriptTRight);
    animation->add(ElbowScriptLeft);
    animation->add(ElbowScriptTLeft);
    animation->add(ArmScriptRight);
    animation->add(ArmScriptTRight);
    animation->add(ArmScriptLeft);


    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic
    OscillateRotation * oscillateBody=new OscillateRotation(true,5,0,1,25,vec3f(0,1,0),1);
    OscillateRotation * oscillateBodySecond=new OscillateRotation(false,0,-5,1,25,vec3f(0,1,0),1);

    Matrix4f * transBody=new Matrix4f();
    transBody->translation(0,0.05,0);
    MatrixStatic * staticBody=new MatrixStatic(*transBody);

    Matrix4f * transBodySecond=new Matrix4f();
    transBodySecond->translation(0,-0.05,0);
    MatrixStatic * staticBodySecond=new MatrixStatic(*transBodySecond);

    //Movement body
    MatrixScript * bodyScript=new MatrixScript();
    bodyScript->add(0.3,oscillateBody);
    bodyScript->add(0.3,oscillateBodySecond);

    MatrixScript * bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);

    /////////////////////////////////
    // 1- ANIMATION HIT
    /////////////////////////////////
    animation=new ScriptLMD();

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.5,notMove);
    LegScriptLeft->add(0.5,notMove);

    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.5,notMove);
    LegScriptRight->add(0.5,notMove);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    //Matrix4fDinamic
    ///////////////////
    // ARM
    //////////////////
    OscillateRotation * shoulderCharge=new OscillateRotation(false,140,0,140,500,vec3f(1.0,0.0,0),1);
    OscillateRotation * shoulderAttack=new OscillateRotation(false,70,-70,70,500,vec3f(0.0,1.0,0),1);
    OscillateRotation * shoulderAttackInvert=new OscillateRotation(true,70,-70,-70,500,vec3f(0.0,1.0,0),1);
    Matrix4f * rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(90,1.0,0.0,0.0);

    Matrix4f * rotateElbow=new Matrix4f();
    rotateElbow->rotation(90,0.0,1.0,0.0);

    Matrix4f * rotateElbow2=new Matrix4f();
    rotateElbow2->rotation(-90,1.0,0.0,0.0);

    Matrix4f * rotateElbowThirdAttack=new Matrix4f();
    rotateElbowThirdAttack->rotation(-90,0.0,1.0,0.0);

    Matrix4f * rotateBWAttack=new Matrix4f();
    rotateBWAttack->rotation(-30,0.0,1.0,0.0);

    Matrix4f * transElbow=new Matrix4f();
    transElbow->translation(0.0,-0.5,0.0);

    //rotateElbow->product(rotateElbow2->getMatrix());

    MatrixStatic *staticShoulder=new MatrixStatic(*rotateShoulder);
    MatrixStatic *staticElbow=new MatrixStatic(*rotateElbow2);
    MatrixStatic *staticTransElbow=new MatrixStatic(*rotateElbow);
    MatrixStatic *staticRotateThirdAttack=new MatrixStatic(*rotateElbowThirdAttack);
    MatrixStatic *staticBWAttack=new MatrixStatic(*rotateBWAttack);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ArmScriptTRight=new MatrixScript();
    ElbowScriptTRight=new MatrixScript();

    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptRight->add(0.25,staticTransElbow);
    ElbowScriptRight->add(0.25,staticTransElbow);
    ElbowScriptRight->add(0.25,staticRotateThirdAttack);
    ElbowScriptRight->add(0.5,notMove);

    ElbowScriptTRight->add(0.5,notMove);
    ElbowScriptTRight->add(0.25,staticElbow);
    ElbowScriptTRight->add(0.25,staticElbow);
    ElbowScriptTRight->add(0.25,staticElbow);
    ElbowScriptTRight->add(0.5,notMove);

    ArmScriptRight->add(0.25,shoulderCharge);
    ArmScriptRight->add(0.25,notMove);
    ArmScriptRight->add(0.25,shoulderAttack);
    ArmScriptRight->add(0.25,staticBWAttack);
    ArmScriptRight->add(0.25,shoulderAttackInvert);
    ArmScriptRight->add(0.5,notMove);

    ArmScriptTRight->add(0.25,notMove);
    ArmScriptTRight->add(0.25,notMove);
    ArmScriptTRight->add(0.25,staticShoulder);
    ArmScriptTRight->add(0.25,staticShoulder);
    ArmScriptTRight->add(0.25,staticShoulder);
    ArmScriptTRight->add(0.5,notMove);

    //Add the script to our animation
    animation->add(ElbowScriptRight);  //2
    animation->add(ElbowScriptTRight); //3
    animation->add(ElbowScriptLeft);   //4
    animation->add(ElbowScriptTLeft);  //5
    animation->add(ArmScriptRight);    //6
    animation->add(ArmScriptTRight);   //7
    animation->add(ArmScriptLeft);     //8


    ///////////////////
    // BODY
    //////////////////
    oscillateBody=new OscillateRotation(true,20,0,0,100,vec3f(0,1,0),1);
    oscillateBodySecond=new OscillateRotation(false,0,-20,0,100,vec3f(0,1,0),1);

    Matrix4f * rotBody=new Matrix4f();
    rotBody->rotation(-20,0.0,1.0,0.0);

    //rotateElbow->product(rotateElbow2->getMatrix());

    MatrixStatic *staticRotBody=new MatrixStatic(*rotBody);

    //Move body
    bodyScript=new MatrixScript();
    bodyScript->add(0.5,notMove);
    bodyScript->add(0.25,oscillateBodySecond);
    bodyScript->add(0.25,staticRotBody);
    bodyScript->add(0.25,oscillateBody);
    bodyScript->add(0.5,notMove);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.5,notMove);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);

    /////////////////////////////////
    // 2- ANIMATION SHIELD - NO WALK
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.3,notMove);
    LegScriptLeft->add(0.3,notMove);

    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.3,notMove);
    LegScriptRight->add(0.3,notMove);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    shoulderCharge=new OscillateRotation(false,0,-40,1,250,vec3f(1.0,0.0,0),1);
    rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(90,1.0,0.0,0.0);

    rotateElbow=new Matrix4f();
    rotateElbow->rotation(60,0.0,0.0,1.0);

    Matrix4f * TransElbow=new Matrix4f();
    TransElbow->translation(-0.25,-0.15,-0.15);

    staticShoulder=new MatrixStatic(*rotateShoulder);
    staticElbow=new MatrixStatic(*rotateElbow);
    MatrixStatic * staticTrans=new MatrixStatic(*TransElbow);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();

    ElbowScriptLeft->add(0.5,staticElbow);
    ArmScriptLeft->add(0.5,staticShoulder);
    ElbowScriptTLeft->add(0.5,staticTrans);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ElbowScriptTRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ArmScriptTRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptTRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,notMove);
    ArmScriptTRight->add(0.5,notMove);


    //Add the script to our animation
    animation->add(ElbowScriptRight);  //4
    animation->add(ElbowScriptTRight); //7
    animation->add(ElbowScriptLeft);   //5
    animation->add(ElbowScriptTLeft);  //7
    animation->add(ArmScriptRight);
    animation->add(ArmScriptTRight);
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    oscillateBody=new OscillateRotation(true,5,0,1,25,vec3f(0,1,0),1);
    oscillateBodySecond=new OscillateRotation(false,0,-5,1,25,vec3f(0,1,0),1);

    //Move body
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.3,notMove);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);

    /////////////////////////////////
    // 3- ANIMATION SHIELD - WALK
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    oscillateLeg=new OscillateRotation(true,30,0,1,150,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-30,1,150,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.3,oscillateLeg);
    LegScriptLeft->add(0.3,oscillateLegSecond);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.3,oscillateLegSecond);
    LegScriptRight->add(0.3,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    shoulderCharge=new OscillateRotation(false,0,-40,1,250,vec3f(1.0,0.0,0),1);
    rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(90,1.0,0.0,0.0);

    rotateElbow=new Matrix4f();
    rotateElbow->rotation(60,0.0,0.0,1.0);

    TransElbow=new Matrix4f();
    TransElbow->translation(-0.25,-0.15,-0.15);

    staticShoulder=new MatrixStatic(*rotateShoulder);
    staticElbow=new MatrixStatic(*rotateElbow);
    staticTrans=new MatrixStatic(*TransElbow);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();

    ElbowScriptLeft->add(0.5,staticElbow);
    ArmScriptLeft->add(0.5,staticShoulder);
    ElbowScriptTLeft->add(0.5,staticTrans);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ElbowScriptTRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ArmScriptTRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptTRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,notMove);
    ArmScriptTRight->add(0.5,notMove);


    //Add the script to our animation
    animation->add(ElbowScriptRight);  //4
    animation->add(ElbowScriptTRight); //7
    animation->add(ElbowScriptLeft);   //5
    animation->add(ElbowScriptTLeft);  //7
    animation->add(ArmScriptRight);
    animation->add(ArmScriptTRight);
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    oscillateBody=new OscillateRotation(true,5,0,1,25,vec3f(0,1,0),1);
    oscillateBodySecond=new OscillateRotation(false,0,-5,1,25,vec3f(0,1,0),1);

    //Move body
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,oscillateBody);
    bodyScript->add(0.3,oscillateBodySecond);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);

    /////////////////////////////////
    // 4- ANIMATION JUMP
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    oscillateLeg=new OscillateRotation(true,30,0,1,300,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-30,1,300,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.15,oscillateLeg);
    LegScriptLeft->add(0.15,oscillateLegSecond);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.15,oscillateLegSecond);
    LegScriptRight->add(0.15,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    Matrix4f * armJumpMatrix=new Matrix4f();
    armJumpMatrix->rotation(60,1,0,0);
    MatrixStatic * staticArm=new MatrixStatic(*armJumpMatrix);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();

    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,staticArm);
    ElbowScriptTLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,staticArm);


    //Add the script to our animation
    animation->add(ElbowScriptRight);  //4
    animation->add(ElbowScriptTRight); //7
    animation->add(ElbowScriptLeft);   //5
    animation->add(ElbowScriptTLeft);  //7
    animation->add(ArmScriptRight);
    animation->add(ArmScriptTRight);
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic

    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);


    //Movement to the first arm
    bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,notMove);


    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);


    /////////////////////////////////
    // 5- ANIMATION GRAVITY
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    oscillateLeg=new OscillateRotation(true,30,0,1,300,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-30,1,300,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.15,oscillateLeg);
    LegScriptLeft->add(0.15,oscillateLegSecond);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.15,oscillateLegSecond);
    LegScriptRight->add(0.15,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    armJumpMatrix=new Matrix4f();
    armJumpMatrix->rotation(30,0,0,1);
    MatrixStatic * staticArmRight=new MatrixStatic(*armJumpMatrix);

    armJumpMatrix=new Matrix4f();
    armJumpMatrix->rotation(-30,0,0,1);
    MatrixStatic * staticArmLeft=new MatrixStatic(*armJumpMatrix);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();

    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,staticArmLeft);
    ElbowScriptTLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,staticArmRight);


    //Add the script to our animation
    animation->add(ElbowScriptRight);  //4
    animation->add(ElbowScriptTRight); //7
    animation->add(ElbowScriptLeft);   //5
    animation->add(ElbowScriptTLeft);  //7
    animation->add(ArmScriptRight);
    animation->add(ArmScriptTRight);
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic

    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);


    //Movement to the first arm
    bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,notMove);


    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);


    /////////////////////////////////
    // 6- ANIMATION HIT-RANGED
    /////////////////////////////////
    animation=new ScriptLMD();
    oscillateLeg=new OscillateRotation(true,40,0,1,150,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-20,1,50,vec3f(1,0,0),1);
    notMove=new MatrixStatic();

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.5,notMove);
    LegScriptLeft->add(0.5,notMove);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.5,notMove);
    LegScriptRight->add(0.5,notMove);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    //Matrix4fDinamic
    ///////////////////
    // ARM
    //////////////////
    shoulderCharge=new OscillateRotation(true,160,90,90,500,vec3f(1.0,0.0,0),1);
    Matrix4f * rotShoulder=new Matrix4f();
    rotShoulder->rotation(90,1.0,0.0,0.0);

    staticShoulder=new MatrixStatic(*rotShoulder);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ElbowScriptTRight=new MatrixScript();

    ElbowScriptRight->add(0.65,notMove);
    ElbowScriptTRight->add(0.65,notMove);
    ArmScriptRight->add(0.5,staticShoulder);
    ArmScriptRight->add(0.25,shoulderCharge);
    ArmScriptRight->add(0.25,staticShoulder);

    //Add the script to our animation
    animation->add(ElbowScriptRight);  //2
    animation->add(ElbowScriptTRight); //3
    animation->add(ElbowScriptLeft);   //4
    animation->add(ElbowScriptTLeft);  //5
    animation->add(ArmScriptRight);    //6
    animation->add(ArmScriptTRight);
    animation->add(ArmScriptLeft);     //7


    ///////////////////
    // BODY
    //////////////////
    //Movement to the first arm
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.3,notMove);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);


    /////////////////////////////////
    // 7- ANIMATION SOUL IN ARMS - NO WALK
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    oscillateLeg=new OscillateRotation(true,30,0,1,150,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-30,1,150,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.3,notMove);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.3,notMove);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(70,1.0,0.0,0.0);

    Matrix4f * rotateShoulderYLeft=new Matrix4f();
    rotateShoulderYLeft->rotation(20,0.0,0.0,1.0);
    rotateShoulderYLeft->product(rotateShoulder->getMatrix());

    Matrix4f * rotateShoulderYRight=new Matrix4f();
    rotateShoulderYRight->rotation(-20,0.0,0.0,1.0);
    rotateShoulderYRight->product(rotateShoulder->getMatrix());

    MatrixStatic * staticShoulderLeft=new MatrixStatic(*rotateShoulderYLeft);
    MatrixStatic * staticShoulderRight=new MatrixStatic(*rotateShoulderYRight);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,staticShoulderLeft);
    ElbowScriptTLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ArmScriptTRight=new MatrixScript();
    ElbowScriptTRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,staticShoulderRight);
    ArmScriptTRight->add(0.5,notMove);
    ElbowScriptTRight->add(0.5,notMove);


    //Add the script to our animation
    animation->add(ElbowScriptRight);
    animation->add(ElbowScriptTRight);
    animation->add(ElbowScriptLeft);
    animation->add(ElbowScriptTLeft);
    animation->add(ArmScriptRight);
    animation->add(ArmScriptTRight);
    animation->add(ArmScriptLeft);


    ///////////////////
    // BODY
    //////////////////
    //Movement body
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,notMove);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.3,notMove);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);


    /////////////////////////////////
    // 8- ANIMATION SOUL IN ARMS - WALK
    /////////////////////////////////
    animation=new ScriptLMD();
    ///////////////////
    // LEG
    //////////////////
    oscillateLeg=new OscillateRotation(true,30,0,1,150,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-30,1,150,vec3f(1,0,0),1);

    //Movement to the first leg
    LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.3,oscillateLeg);
    LegScriptLeft->add(0.3,oscillateLegSecond);


    //Movement to the second leg
    LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.3,oscillateLegSecond);
    LegScriptRight->add(0.3,oscillateLeg);

    //Add the script to our animation
    animation->add(LegScriptRight);
    animation->add(LegScriptLeft);

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    rotateShoulder=new Matrix4f();
    rotateShoulder->rotation(70,1.0,0.0,0.0);

    rotateShoulderYLeft=new Matrix4f();
    rotateShoulderYLeft->rotation(20,0.0,0.0,1.0);
    rotateShoulderYLeft->product(rotateShoulder->getMatrix());

    rotateShoulderYRight=new Matrix4f();
    rotateShoulderYRight->rotation(-20,0.0,0.0,1.0);
    rotateShoulderYRight->product(rotateShoulder->getMatrix());

    staticShoulderLeft=new MatrixStatic(*rotateShoulderYLeft);
    staticShoulderRight=new MatrixStatic(*rotateShoulderYRight);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptTLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,staticShoulderLeft);
    ElbowScriptTLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();
    ArmScriptTRight=new MatrixScript();
    ElbowScriptTRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,staticShoulderRight);
    ArmScriptTRight->add(0.5,notMove);
    ElbowScriptTRight->add(0.5,notMove);


    //Add the script to our animation
    animation->add(ElbowScriptRight);
    animation->add(ElbowScriptTRight);
    animation->add(ElbowScriptLeft);
    animation->add(ElbowScriptTLeft);
    animation->add(ArmScriptRight);
    animation->add(ArmScriptTRight);
    animation->add(ArmScriptLeft);


    ///////////////////
    // BODY
    //////////////////
    //Matrix4fDinamic
    oscillateBody=new OscillateRotation(true,5,0,1,25,vec3f(0,1,0),1);
    oscillateBodySecond=new OscillateRotation(false,0,-5,1,25,vec3f(0,1,0),1);

    transBody=new Matrix4f();
    transBody->translation(0,0.05,0);
    staticBody=new MatrixStatic(*transBody);

    transBodySecond=new Matrix4f();
    transBodySecond->translation(0,-0.05,0);
    staticBodySecond=new MatrixStatic(*transBodySecond);

    //Movement body
    bodyScript=new MatrixScript();
    bodyScript->add(0.3,oscillateBody);
    bodyScript->add(0.3,oscillateBodySecond);

    bodyTScript=new MatrixScript();
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);
    bodyTScript->add(0.15,staticBody);
    bodyTScript->add(0.15,staticBodySecond);

    animation->add(bodyScript);
    animation->add(bodyTScript);

    animations.add(animation);
 }
