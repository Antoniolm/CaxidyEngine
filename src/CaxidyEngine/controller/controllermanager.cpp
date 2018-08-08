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


#include "controllermanager.h"

namespace CaxidyEngine {
    
ControllerManager::ControllerManager()
{
    //ctor
}

//**********************************************************************//

ControllerManager::~ControllerManager()
{
    //dtor
}

//**********************************************************************//

void ControllerManager::setState(bool value,ControllerIndex button){
    gamepadController.setState(value,button);
    keyboardController.setState(value,button);
}

//**********************************************************************//

void ControllerManager::checkEvent(SDL_Event & event){
    gamepadController.checkEvent(event);
}

//**********************************************************************//

bool ControllerManager::checkButton(ControllerIndex button){
    bool result=false;

    if(keyboardController.checkButton(button) || gamepadController.checkButton(button))
        result=true;

    return result;

}

//**********************************************************************//

void ControllerManager::catchKeyBoardState(const Uint8* currentKeyStates){
    keyboardController.catchKeyBoardState(currentKeyStates);
}

//**********************************************************************//

void ControllerManager::consumeButtons(){
    keyboardController.consumeButtons();
    gamepadController.consumeButtons();
}

} // CaxidyEngine
