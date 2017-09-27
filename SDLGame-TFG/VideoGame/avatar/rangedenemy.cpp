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

#include "rangedenemy.h"
#include "../rootmapgame.h"

RangedEnemy::RangedEnemy(){

}

//**********************************************************************//

RangedEnemy::RangedEnemy(const Value & enemyFeatures)
{
    life=enemyFeatures["life"].GetInt();
    maxLife=enemyFeatures["life"].GetInt();
    experience=enemyFeatures["exp"].GetInt();

    IA=new IARangedEnemy();
    secondIA=new IAMeleeEnemy();

    position=vec4f(enemyFeatures["position"][0].GetFloat(),
                   enemyFeatures["position"][1].GetFloat(),
                   enemyFeatures["position"][2].GetFloat(),1.0);

    radioActivity=vec3f(enemyFeatures["radioActivity"][0].GetFloat(),
                        enemyFeatures["radioActivity"][1].GetFloat(),
                        enemyFeatures["radioActivity"][2].GetFloat());

    acceleratedMove=new AcceleratedMovement();
    acceleratedMove->resetState();
    direction=FORWARD;
    isMoving=false;
    isFalling=false;
    isJumping=false;
    isHitting=false;
    isImpacted=false;
    isShielded=false;
    enemyActivate=false;
    limitBottom=0.5;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    MaterialCollection * materialCollect =MaterialCollection::getInstance();

    //////////////////////////////////////////////////////
    /////           Initialize weapon               /////
    //////////////////////////////////////////////////////
    weapon=new Equipment(enemyFeatures["weapon"]);

    //////////////////////////////////////////////////////
    /////              All the sounds                /////
    //////////////////////////////////////////////////////
    SoundCollection * soundCollect =SoundCollection::getInstance();

    enemySound.push_back(soundCollect->getSound(sWALK));
    enemySound.push_back(soundCollect->getSound(EHIT));
    enemySound.push_back(soundCollect->getSound(SHOOT));

    //////////////////////////////////////////////////////
    /////             Initialize text                /////
    //////////////////////////////////////////////////////
    TTF_Font *font=TTF_OpenFont( enemyFeatures["textFont"].GetString(), enemyFeatures["textSize"].GetInt());
    SDL_Color color= {255,0,0};
    currentText=new Text(mVOID,font,color,false);
    activatedDialog=false;

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
    legLeft->add(meshCollect->getMesh(enemyFeatures["leg"].GetString()));

    //Leg Right
    NodeSceneGraph * legRight=new NodeSceneGraph();
    legRight->add(moveLegRight);
    legRight->add(transLegSecond);
    legRight->add(meshCollect->getMesh(enemyFeatures["leg"].GetString()));

    //////////////////////////////////////////////////////
    /////                  Arms                      /////
    //////////////////////////////////////////////////////


    //Create a new Movement
    Matrix4f * moveElbowRight=new Matrix4f();
    moveElbowRight->identity();
    moveMatrix.push_back(moveElbowRight);

    Matrix4f * moveElbowLeft=new Matrix4f();
    moveElbowLeft->identity();
    moveMatrix.push_back(moveElbowLeft);

    Matrix4f * moveArmRight=new Matrix4f();
    moveArmRight->identity();
    moveMatrix.push_back(moveArmRight);

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

    Matrix4f * transArms=new Matrix4f();
    transArms->translation(0.0,-0.15,-0.1);

    Matrix4f * transElbowSecond=new Matrix4f();
    transElbowSecond->translation(0.0,-0.2,0.0);

    Matrix4f * transArmsSecond=new Matrix4f();
    transArmsSecond->translation(0.0,-0.15,-0.1);

    //Arms
    NodeSceneGraph * handRight=new NodeSceneGraph();
    handRight->add(transElbow);
    handRight->add(moveElbowRight);
    handRight->add(transHand);
    handRight->add(meshCollect->getMesh(enemyFeatures["hand"].GetString()));
    handRight->add(weapon);

    NodeSceneGraph * handLeft=new NodeSceneGraph();
    handLeft->add(transElbowSecond);
    handLeft->add(moveElbowLeft);
    handLeft->add(transHandLeft);
    handLeft->add(rotateYHand);
    handLeft->add(meshCollect->getMesh(enemyFeatures["hand"].GetString()));

    //Arm left
    NodeSceneGraph * ArmLeft=new NodeSceneGraph();
    ArmLeft->add(transArms);
    ArmLeft->add(moveArmLeft);
    ArmLeft->add(handLeft);


    //Arm Right
    NodeSceneGraph * ArmRight=new NodeSceneGraph();
    ArmRight->add(transArmsSecond);
    ArmRight->add(moveArmRight);
    ArmRight->add(handRight);

    //////////////////////////////////////////////////////
    /////         Construction of the hero           /////
    //////////////////////////////////////////////////////

    //Movement for our hero
    moveAvatar= new Matrix4f();
    moveAvatar->translation(position.x,position.y,position.z);

    root=new NodeSceneGraph();
    root->add(moveAvatar);

    Matrix4f *transLegScene=new Matrix4f();
    transLegScene->translation(-0.2,0.0,0.0);

    Matrix4f *transLegSceneI=new Matrix4f();
    transLegSceneI->translation(0.1,0.0,0.0);

    Matrix4f * scaleHero=new Matrix4f();
    scaleHero->scale(0.5,0.5,0.5);

    Matrix4f * trasnArms=new Matrix4f();
    trasnArms->translation(-0.3,0.0,0.0);

    Matrix4f *trasnArmsI=new Matrix4f();
    trasnArmsI->translation(0.15,0.3,0.15);

    Matrix4f *transHead=new Matrix4f();
    transHead->translation(0.0,0.5,0.0);

    Matrix4f *transChest=new Matrix4f();
    transChest->translation(0.15,0.15,0.0);

    Matrix4f *transChestArm=new Matrix4f();
    transChestArm->translation(0.0,0.05,-0.15);

    NodeSceneGraph * chestNode=new NodeSceneGraph();
    chestNode->add(transChest);
    chestNode->add(meshCollect->getMesh(enemyFeatures["body"].GetString()));

    NodeSceneGraph * headNode=new NodeSceneGraph();
    headNode->add(transHead);
    headNode->add(meshCollect->getMesh(enemyFeatures["head"].GetString()));

    NodeSceneGraph * chest_ArmsNode=new NodeSceneGraph();
    chest_ArmsNode->add(transChestArm);
    chest_ArmsNode->add(chestNode);
    chest_ArmsNode->add(trasnArmsI);
    chest_ArmsNode->add(ArmLeft);
    chest_ArmsNode->add(trasnArms);
    chest_ArmsNode->add(ArmRight);

    root->add(materialCollect->getMaterial(enemyFeatures["material"].GetString()));
    root->add(headNode);
    root->add(chest_ArmsNode);
    root->add(transLegSceneI);
    root->add(legLeft);
    root->add(transLegScene);
    root->add(legRight);
    currentTime=SDL_GetTicks();
    jumpDelay=currentTime;
    dmgDelay=currentTime;
    hitDelay=currentTime;
    IADelay=currentTime;
    currentMove.first=FORWARD;
    currentMove.second=vec3f();

    initAnimation();
}

//**********************************************************************//

RangedEnemy::~RangedEnemy()
{
    delete root;
    delete currentText;

    for(vector<Projectile *>::iterator it = projectiles.begin() ; it != projectiles.end(); ++it){
        delete (*it);
    }
}

//**********************************************************************//

void RangedEnemy::visualization(Context & cv){
    if(position.x>cv.minVisualPosition.x && position.x<cv.maxVisualPosition.x
       && position.y>cv.minVisualPosition.y && position.y<cv.maxVisualPosition.y)
            root->visualization(cv);

    if(activatedDialog){
        currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
        currentText->visualization(cv);
    }

    vector<Projectile *>::iterator it;
    for(it=projectiles.begin();it!=projectiles.end();it++){
        (*it)->visualization(cv);
    }
}

//**********************************************************************//

void RangedEnemy::updateState(GameState & gameState){
    vec3f aux;
    RootMap * rootMap=gameState.rootMap;
    float time=gameState.time;

    currentMap=rootMap;
    Hero * hero=dynamic_cast<RootMapGame*>(gameState.rootMap)->getHero();
    vec3f posHero=hero->getPosition();
    vec3f distance=vec3f(position.x,position.y,position.z)-posHero;

    if(time-currentTime>200)
        currentTime=time-50;

    //check if the enemy will be activated in this frame
    if((distance.x>-radioActivity.x && distance.x<radioActivity.x)&&(distance.y>-radioActivity.y && distance.y<radioActivity.y)&&(distance.z>-radioActivity.z && distance.z<radioActivity.z)){
        enemyActivate=true;
    }

    if(enemyActivate){ //If enemy is activated
        if(IADelay<(time-50)){ //Delay IA
            if(sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0))>4.0) //if enemy escape from the hero
                currentMove=secondIA->nextPosition(vec3f(position.x,position.y,position.z),posHero,dynamic_cast<RootMapGame*>(gameState.rootMap)->getEnemyList());

            else //if enemy follow the hero
                currentMove=IA->nextPosition(vec3f(position.x,position.y,position.z),posHero,dynamic_cast<RootMapGame*>(gameState.rootMap)->getEnemyList());

            IADelay=time;
        }
        if((currentMove.second.x!=0.0 || currentMove.second.y!=0.0 || currentMove.second.z!=0.0)&& !isImpacted){ //IA-> is not near of our hero

            if(!moveBody(currentMove.second,currentMove.first) && !isJumping && !isFalling && jumpDelay<(time-1000)
                && sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0))>4.0){ //If not move -> enemy jump

                activeJump(vec3f(0.0,12.0,0.0),vec3f(0.0,5.0,0.0));
                jumpDelay=time;
            }
            isHitting=false;
        }
        else {  //If is not near of the target
            //shot arrow
            changeDirection(currentMove.first);
            isHitting=true;
        }

        if(isImpacted) //if is impacted
            impactMove(time);

        if(isJumping){
            jump(time);
        }
        else{
            ObjectScene * object=gravity(time);
            if(object!=0 && object->getDamage()!=0.0 && dmgDelay<(time-400)){ //If the object do damage
                takeDamage(object->getDamage(),posHero);
                dmgDelay=time;
            }
        }
    }

    if(dmgDelay<(time-300))
        activatedDialog=false;


    //Update our vec4f position
    position=moveAvatar->product(vec4f());

    ////////////////////////////
    //UPDATE ANIMATION
    ////////////////////////////
    if(isMoving && !isFalling && !isJumping && !isHitting){
        animations.activate(0);
    }
    else if(isHitting){
        animations.activate(1);
        ScriptLMD * animationHit=animations.getAnimation();
        if(animationHit->getScriptState(4)==1 && hitDelay<(time-700)){ //Hit an arrow
            projectiles.push_back(createProjectile(weapon->getDamage()));
            hitDelay=time;
            enemySound[2]->play(sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0)));
        }
    }

    animations.update(time-currentTime);

    ScriptLMD * animatio=animations.getAnimation();
    for(unsigned i=0;i<moveMatrix.size();i++)
        moveMatrix[i]->setMatrix(animatio->readMatrix(i).getMatrix());

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


    currentTime+=(time-currentTime);
}

//**********************************************************************//

Projectile * RangedEnemy::createProjectile(float damage){
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

 void RangedEnemy::initAnimation(){

    /////////////////////////////////
    // ANIMATION MOVE
    /////////////////////////////////
    ///////////////////
    // LEG
    //////////////////
    ScriptLMD * animation=new ScriptLMD();
    OscillateRotation * oscillateLeg=new OscillateRotation(true,40,0,1,150,vec3f(1,0,0),2);
    OscillateRotation * oscillateLegSecond=new OscillateRotation(false,0,-20,1,50,vec3f(1,0,0),1);
    MatrixStatic * notMove=new MatrixStatic();

    //Movement to the first leg
    MatrixScript * LegScriptLeft=new MatrixScript();
    LegScriptLeft->add(0.5,oscillateLeg);
    LegScriptLeft->add(0.5,oscillateLegSecond);


    //Movement to the second leg
    MatrixScript * LegScriptRight=new MatrixScript();
    LegScriptRight->add(0.5,oscillateLegSecond);
    LegScriptRight->add(0.5,oscillateLeg);

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
    ElbowScriptLeft->add(0.5,notMove);
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,oscillateShoulder);
    ArmScriptLeft->add(0.5,notMove);

    //Movement to the second arm
    MatrixScript * ElbowScriptRight=new MatrixScript();
    MatrixScript * ArmScriptRight=new MatrixScript();
    ElbowScriptRight->add(0.5,notMove);
    ElbowScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,notMove);
    ArmScriptRight->add(0.5,oscillateShoulder);


    //Add the script to our animation
    animation->add(ElbowScriptRight);
    animation->add(ElbowScriptLeft);
    animation->add(ArmScriptRight);
    animation->add(ArmScriptLeft);

    animations.add(animation);

    /////////////////////////////////
    // ANIMATION HIT
    /////////////////////////////////
    ///////////////////
    // LEG
    //////////////////
    animation=new ScriptLMD();
    oscillateLeg=new OscillateRotation(true,40,0,1,150,vec3f(1,0,0),2);
    oscillateLegSecond=new OscillateRotation(false,0,-20,1,50,vec3f(1,0,0),1);

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

    ///////////////////
    // ARM
    //////////////////
    //Matrix4fDinamic
    OscillateRotation * shoulderCharge=new OscillateRotation(true,160,90,90,500,vec3f(1.0,0.0,0),1);
    Matrix4f * rotShoulder=new Matrix4f();
    rotShoulder->rotation(90,1.0,0.0,0.0);

    MatrixStatic * staticShoulder=new MatrixStatic(*rotShoulder);

    //Movement to the first arm
    ElbowScriptLeft=new MatrixScript();
    ArmScriptLeft=new MatrixScript();
    ElbowScriptLeft->add(0.5,notMove);
    ArmScriptLeft->add(0.5,notMove);

    //Movement to the second arm
    ElbowScriptRight=new MatrixScript();
    ArmScriptRight=new MatrixScript();

    ElbowScriptRight->add(0.65,notMove);
    ArmScriptRight->add(1.0,staticShoulder);
    ArmScriptRight->add(0.25,shoulderCharge);
    ArmScriptRight->add(0.25,notMove);


    //Add the script to our animation
    animation->add(ElbowScriptRight); //4
    animation->add(ElbowScriptLeft);  //5
    animation->add(ArmScriptRight);   //6
    animation->add(ArmScriptLeft);    //7

    animations.add(animation);
 }
