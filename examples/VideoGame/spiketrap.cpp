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

#include "spiketrap.h"
#include "rootmapgame.h"

SpikeTrap::SpikeTrap(const Value & spikeFeatures)
{
    position=vec4f(spikeFeatures["position"][0].GetFloat(),spikeFeatures["position"][1].GetFloat(),spikeFeatures["position"][2].GetFloat(),1.0);
    damage=spikeFeatures["damage"].GetFloat();

    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();
    SoundCollection * soundCollect= SoundCollection::getInstance();

    activatedTrap=soundCollect->getSound(sATRAP);
    animationSound=soundCollect->getSound(sNTRAP);

    Matrix4f * transObject=new Matrix4f();
    transObject->translation(position.x,position.y,position.z);

    transActivate=new Matrix4f();
    transActivate->identity();

    root=new NodeSceneGraph();
    root->add(transObject);
    root->add(transActivate);
    root->add(materialCollect->getMaterial(mSPIKE));
    root->add(meshCollect->getMesh(SPIKE));

    currentTime=SDL_GetTicks();
    hitDelay=currentTime;
    delayTime=currentTime;
    desactivatedDelay=currentTime;
    activated=false;
    delayActivated=false;

    initAnimation();

}

//**********************************************************************//

SpikeTrap::~SpikeTrap()
{
    delete root;
}


//**********************************************************************//

void SpikeTrap::visualization(Context & cv){
    if(position.x>cv.minVisualPosition.x && position.x<cv.maxVisualPosition.x
       && position.y>cv.minVisualPosition.y && position.y<cv.maxVisualPosition.y)
        root->visualization(cv);
}

//**********************************************************************//

void SpikeTrap::updateState(GameState & gameState ){
    float time=gameState.time;
    Hero * hero=dynamic_cast<RootMapGame*>(gameState.rootMap)->getHero();

    if(time-currentTime>200) currentTime=time-50;

    vec3f posHero=hero->getPosition();
    float distance=sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0));

    vector<Enemy *> enemies=dynamic_cast<RootMapGame*>(gameState.rootMap)->getEnemyList()->getEnemies();
    std::vector<int> enemiesIn=checkEnemies(enemies);

    //if hero is near of a disactivated trap
    if(!activated && ((distance<=0.75 && (position.y>posHero.y-1 && position.y<posHero.y)) || !enemiesIn.empty() ) ){
        activated=true;
        delayActivated=true;
        delayTime=time;
        desactivatedDelay=time;
        animationUp->resetState();
        animationDown->resetState();
        transActivate->identity();
        activatedTrap->play(distance);
    }

    if(activated && desactivatedDelay<(time-2100) && (distance>0.75 || !enemiesIn.empty() )){ //if hero is far of an activated trap
        activated=false;
        delayActivated=false;
        animationSound->play(distance);
    }

    bool updateHitDelay=false;
    if(activated){ // if is activated
        if(!delayActivated){ //If is not in delayTime

            //Check hero
            if(distance<=0.75 && (position.y>posHero.y-1 && position.y<posHero.y) && hitDelay<(time-400)){
                hero->takeDamage(damage);
                updateHitDelay=true;
            }

            //Check enemy
            if(!enemiesIn.empty() && hitDelay<(time-400)){
                updateHitDelay=true;

                for(int i=0;i<enemiesIn.size();i++){
                    enemies[enemiesIn[i]]->takeDamage(damage,posHero);
                }
            }

            if(updateHitDelay) //Update hitdelay
                hitDelay=time;
        }
        else { //If is in delayTime
            if(delayTime<(time-600)){
                delayActivated=false;
                animationSound->play(distance);
            }
        }
    }

    ////////////////////////////////
    // Updated animation
    if(activated && !delayActivated && animationUp->getScriptState(0)!=1){
        animationUp->updateState(time-currentTime);
        transActivate->product(animationUp->readMatrix(0).getMatrix());
    }
    else if(!activated && animationDown->getScriptState(0)!=1){
        animationDown->updateState(time-currentTime);
        transActivate->product(animationDown->readMatrix(0).getMatrix());
    }
    else if(animationDown->getScriptState(0)==1){
        transActivate->identity();
    }


    currentTime+=time-currentTime;
}

//**********************************************************************//

void SpikeTrap::setDamage(float value){
    damage=value;
}

//**********************************************************************//

float SpikeTrap::getDamage(){
    return damage;
}

//**********************************************************************//

bool SpikeTrap::isActivated(){
    return activated;
}

//**********************************************************************//

void SpikeTrap::initAnimation(){
    //////////////////////////////////////
    //Animation up
    animationUp=new ScriptLMD();

    LinearMovement * movementUp=new LinearMovement(0.0,7.0,0.0);
    MatrixStatic * notMove=new MatrixStatic();

    MatrixScript * scriptUp=new MatrixScript();

    scriptUp->add(0.12,movementUp);
    scriptUp->add(0.5,notMove);

    animationUp->add(scriptUp);


    /////////////////////////////
    //Animation down
    animationDown=new ScriptLMD();

    LinearMovement * movementDown=new LinearMovement(0.0,-7.0,0.0);

    MatrixScript * scriptDown=new MatrixScript();

    scriptDown->add(0.12,movementDown);
    scriptDown->add(0.5,notMove);

    animationDown->add(scriptDown);
}

//**********************************************************************//
std::vector<int> SpikeTrap::checkEnemies(std::vector<Enemy *> & enemies){

    float distance;
    vec3f posEnemy;

    std::vector<int> result;

    for(int i=0;i<enemies.size();i++){
        posEnemy=enemies[i]->getPosition();
        distance=sqrt(pow(position.x-posEnemy.x,2.0)+pow(position.z-posEnemy.z,2.0));

        if(distance<=0.75 && (position.y>posEnemy.y-1 && position.y<posEnemy.y)){
            result.push_back(i);
        }
    }

    return result;
}
