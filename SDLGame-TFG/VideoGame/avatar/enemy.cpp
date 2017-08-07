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

#include "enemy.h"
#include "../GraphicEngine/ia/iaenemy.h"

Enemy::~Enemy()
{
}

//**********************************************************************//

void Enemy::visualization(Context & cv){
    if(position.x>cv.minVisualPosition.x && position.x<cv.maxVisualPosition.x
       && position.y>cv.minVisualPosition.y && position.y<cv.maxVisualPosition.y)
            root->visualization(cv);

    if(activatedDialog){
        currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
        currentText->visualization(cv);
    }
}

//**********************************************************************//

void Enemy::updateState(GameState & gameState){

}

//**********************************************************************//

void Enemy::activatedEnemy(bool value){
    enemyActivate=value;
}

//**********************************************************************//

bool Enemy::isActivate(){
    return enemyActivate;
}

//**********************************************************************//

void Enemy::setRadioActivity(vec3f radio){
    radioActivity=radio;
}

//**********************************************************************//

vec3f Enemy::getRadioActivity(){
    return radioActivity;
}

//**********************************************************************//

 float Enemy::getLife(){
    return life;
 }

 //**********************************************************************//

 void Enemy::takeDamage(vec3f posAvatar,avatarDirection dirAvatar,vec3f posHero,float value,const vector<Enemy *> & enemies){
    //check Distance
    float distance=sqrt(pow(position.x-posAvatar.x,2.0)+pow(position.z-posAvatar.z,2.0));

    if(detectHit(posAvatar,dirAvatar) && dmgDelay<(currentTime-250) && distance<1.0){
        addLife(value);
        stringstream convert;
        int lastValue;

        if(activatedDialog){
            string currentValue=currentText->getMessage();
            lastValue=atoi(currentValue.c_str());
            value+=lastValue;
        }
        convert << value;

        activatedDialog=true;
        currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
        currentText->setMessage(convert.str());
        currentText->init();

        dmgDelay=currentTime;

        if(!isImpacted && canImpact(dirAvatar,enemies))
            activeImpact(dirAvatar);

        enemySound[1]->play(sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0)));

        //Check if was activated
        if(!enemyActivate)
            enemyActivate=true;
    }
 }

 //**********************************************************************//

void Enemy::takeDamage(float value,vec3f posHero){
    addLife(value);

    stringstream convert;
    int lastValue;

    if(activatedDialog){
        string currentValue=currentText->getMessage();
        lastValue=atoi(currentValue.c_str());
        value+=lastValue;
    }

    convert << value;

    activatedDialog=true;
    currentText->setPosition(vec3f(position.x,position.y+1.5f,position.z));
    currentText->setMessage(convert.str());
    currentText->init();

    enemySound[1]->play(sqrt(pow(position.x-posHero.x,2.0)+pow(position.z-posHero.z,2.0)));
 }

