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


#include "enemylist.h"
#include "avatar/enemy.h"
#include "avatar/rangedenemy.h"
#include "avatar/meleeenemy.h"

EnemyList::EnemyList(){
}

//**********************************************************************//

EnemyList::EnemyList(const Value & enemiesFeatures){
    assert(enemiesFeatures.IsArray());
    for(unsigned i=0;i<enemiesFeatures.Size();i++){
        if(strcmp(enemiesFeatures[i]["type"].GetString(),"ranged")==0){
            enemies.push_back(new RangedEnemy(enemiesFeatures[i]["life"].GetInt(),
                                              vec3f(enemiesFeatures[i]["position"][0].GetFloat(),enemiesFeatures[i]["position"][1].GetFloat(),enemiesFeatures[i]["position"][2].GetFloat()),
                                              vec3f(enemiesFeatures[i]["radioActivity"][0].GetFloat(),enemiesFeatures[i]["radioActivity"][1].GetFloat(),enemiesFeatures[i]["radioActivity"][2].GetFloat())));
        }
        else{
            enemies.push_back(new MeleeEnemy(enemiesFeatures[i]));
        }
    }
}

//**********************************************************************//

EnemyList::~EnemyList()
{
    for(vector<Enemy *>::iterator it = enemies.begin() ; it != enemies.end(); ++it){
        delete (*it);
    }
}

//**********************************************************************//

void EnemyList::add(Enemy * enemy){
    enemies.push_back(enemy);
}

//**********************************************************************//

void EnemyList::visualization(Context & cv){
    for(unsigned i=0;i<enemies.size();i++)
        enemies[i]->visualization(cv);
}

//**********************************************************************//

void EnemyList::updateState(GameState & gameState){
    vector<Enemy*>::iterator it=enemies.begin();
    while(it!=enemies.end()){ //loop for enemies
        (*it)->updateState(gameState);
        if((*it)->getLife()<=0.0){ //if the enemy is dead
            enemies.erase(it);
        }
        else //if not dead it++;
            it++;
    }
}

//**********************************************************************//

vector<Enemy *> & EnemyList::getEnemies(){
    return enemies;
}

//**********************************************************************//

Enemy * EnemyList::getEnemy(int index){
    return enemies[index];
}

//**********************************************************************//

int EnemyList::getNumEnemy(){
    return enemies.size();
}
