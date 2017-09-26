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

#include "gamestatechild.h"

GameStateChild::GameStateChild()
{
    rootMap=0;
    movie=0;
}

//**********************************************************************//

GameStateChild::~GameStateChild()
{
    //dtor
}

//**********************************************************************//

void GameStateChild::initPlay(GLuint shaderID){
    rootMap->activatedLight(shaderID);
    rootMap->activatedObjectGroup();

    rootMap->getHero()->setCoin(SavedManager::getInstance()->getCoin());

    refPoint=rootMap->getHero()->getPosition();
    movie=rootMap->getMovie();

    SavedManager * saveManager=SavedManager::getInstance();
                   saveManager->load(true);

    //Set the level of the hero
    rootMap->getHero()->setLevelParameters(saveManager->getCurrentExp(),saveManager->getMaxExp(),saveManager->getLevel());

    //Set the equipment of the hero
    rootMap->getHero()->setEquipment(inventoryMenu->getEquippetItem(0));
    rootMap->getHero()->setEquipment(inventoryMenu->getEquippetItem(1));
    rootMap->getHero()->setEquipment(inventoryMenu->getEquippetItem(2));

    if(movie->isActivate()){
        movie->setPosition(vec3f(refPoint.x,refPoint.y+6.77,refPoint.z+11));
        movie->activateAllTexture();
    }
}

