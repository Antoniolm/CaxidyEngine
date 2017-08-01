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

#include "keyboardcontroller.h"

KeyboardController::KeyboardController()
{
    for(int i=0;i<11;i++)
        stateButtons[i]=false;
}

//**********************************************************************//

KeyboardController::~KeyboardController()
{
    //dtor
}

//**********************************************************************//

void KeyboardController::catchKeyBoardState(const Uint8* currentKeyStates){

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_w)] || currentKeyStates[SDL_GetScancodeFromKey(SDLK_UP)]) buttons[cUP]=true;
    else{
        buttons[cUP]=false;
        stateButtons[cUP]=true;
    }

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_s)] || currentKeyStates[SDL_GetScancodeFromKey(SDLK_DOWN)]) buttons[cDOWN]=true;
    else{
        buttons[cDOWN]=false;
        stateButtons[cDOWN]=true;
    }

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_a)] || currentKeyStates[SDL_GetScancodeFromKey(SDLK_LEFT)]) buttons[cLEFT]=true;
    else {
        buttons[cLEFT]=false;
        stateButtons[cLEFT]=true;
    }

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_d)] || currentKeyStates[SDL_GetScancodeFromKey(SDLK_RIGHT)]) buttons[cRIGHT]=true;
    else {
        buttons[cRIGHT]=false;
        stateButtons[cRIGHT]=true;
    }

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_e)]) buttons[cACTION]=true;
    else {
        buttons[cACTION]=false;
        stateButtons[cACTION]=true;
    }

    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_i)]) buttons[cSHIELD]=true;
    else {
        buttons[cSHIELD]=false;
        stateButtons[cSHIELD]=true;
    }
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_k)]) buttons[cJUMP]=true;
    else {
        buttons[cJUMP]=false;
        stateButtons[cJUMP]=true;
    }
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_l)]) buttons[cATTACK]=true;
    else {
        buttons[cATTACK]=false;
        stateButtons[cATTACK]=true;
    }
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_q)]) buttons[cSWAPWEAPON]=true;
    else {
        buttons[cSWAPWEAPON]=false;
        stateButtons[cSWAPWEAPON]=true;
    }
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_ESCAPE)]) buttons[cPAUSE]=true;
    else {
        buttons[cPAUSE]=false;
        stateButtons[cPAUSE]=true;
    }
    if(currentKeyStates[SDL_GetScancodeFromKey(SDLK_v)]) buttons[cVIEW]=true;
    else {
        buttons[cVIEW]=false;
        stateButtons[cVIEW]=true;
    }
}
