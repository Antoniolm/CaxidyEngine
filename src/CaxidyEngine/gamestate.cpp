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

#include "gamestate.h"

GameState::GameState()
{
    rootMap=0;
    movie=0;
}

//**********************************************************************//

GameState::~GameState(){
    delete controller;
    delete rootMap;
    delete pauseMenu;
    delete mainMenu;
    delete deadMenu;
    delete creditScreen;
    delete loadScreen;
    delete optionMenu;
    delete controlMenu;
    delete inventoryMenu;

    delete camera;
    delete speakingSketch;
}

//**********************************************************************//

void GameState::initPlay(GLuint shaderID){
}

//**********************************************************************//

void GameState::updatePlay(){
    movie->updateState(*this);
    pauseMenu->updateState(*this);
    inventoryMenu->updateState(*this);
    deadMenu->updateState(*this);

    rootMap->updateState(*this);

    speakingSketch->updateState(*this);
}

//**********************************************************************//

void GameState::updateLoading(GLuint shaderID){
    time=SDL_GetTicks();
    camera->setPosition(vec3f(0.0,0.0,0.0),shaderID);
    loadScreen->updateState(*this);

    camera->activateOrthoProjection(shaderID);
}

//**********************************************************************//

void GameState::updateCredit(GLuint shaderID){
    time=SDL_GetTicks();
    camera->setPosition(vec3f(0.0,0.0,0.0),shaderID);
    creditScreen->updateState(*this);

    camera->activateOrthoProjection(shaderID);
}

//**********************************************************************//

void GameState::updateMenu(GLuint shaderID){
    time=SDL_GetTicks();
    camera->setPosition(vec3f(0.0,0.0,0.0),shaderID);
    mainMenu->updateState(*this);
    optionMenu->updateState(*this);
    controlMenu->updateState(*this);

    camera->activateOrthoProjection(shaderID);
}
