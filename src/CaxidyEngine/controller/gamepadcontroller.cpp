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

#include "gamepadcontroller.h"

namespace CaxidyEngine {

GamepadController::GamepadController()
{
    for(int i=0;i<12;i++){
        buttons[i]=false;
        stateButtons[i]=false;
    }
    controller=0;

    for(int i=0;i<SDL_NumJoysticks();i++){
        if(SDL_IsGameController(i)){
            controller=SDL_GameControllerOpen(i);
            std::cout<< "---Gamepad connected---"<<std::endl;
            if( controller ) {
                joy = SDL_GameControllerGetJoystick( controller );
            }
        }
    }
}

//**********************************************************************//

GamepadController::~GamepadController()
{
    if(controller!=0)
        SDL_GameControllerClose(controller);
}

//**********************************************************************//

void GamepadController::checkEvent(SDL_Event & event){

    switch(event.type){
        case SDL_CONTROLLERBUTTONDOWN:
            setButton(true,event.cbutton.button);
        break;
        case SDL_CONTROLLERBUTTONUP: // If player release a button of his game controller
            setButton(false,event.cbutton.button);
        break;
        case SDL_CONTROLLERDEVICEADDED:
            addGamepad(event.cdevice.which);
            break;

        case SDL_CONTROLLERDEVICEREMOVED:
            removeGamepad();
            break;
    }

    //////////////////////
    //Check joystick
    //////////////////////
    Sint16 x_move = SDL_JoystickGetAxis(joy, 0);
    Sint16 y_move = SDL_JoystickGetAxis(joy, 1);

    updateJoystickMove(x_move,y_move);
}

//**********************************************************************//

void GamepadController::setButton(bool value,Uint8 button){
    switch(button){
        case SDL_CONTROLLER_BUTTON_A:
            buttons[cACTION]=value;
            stateButtons[cACTION]=value;
            break;
        case SDL_CONTROLLER_BUTTON_B:
            buttons[cJUMP]=value;
            stateButtons[cJUMP]=value;
            break;
        case SDL_CONTROLLER_BUTTON_Y:
            buttons[cSWAPWEAPON]=value;
            stateButtons[cSWAPWEAPON]=value;
            break;
        case SDL_CONTROLLER_BUTTON_X:
            buttons[cINVENTORY]=value;
            stateButtons[cINVENTORY]=value;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            buttons[cUP]=value;
            stateButtons[cUP]=value;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            buttons[cDOWN]=value;
            stateButtons[cDOWN]=value;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            buttons[cLEFT]=value;
            stateButtons[cLEFT]=value;
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            buttons[cRIGHT]=value;
            stateButtons[cRIGHT]=value;
            break;
        case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
            buttons[cSHIELD]=value;
            stateButtons[cSHIELD]=value;
            break;
        case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
            buttons[cATTACK]=value;
            stateButtons[cATTACK]=value;
            break;
        case SDL_CONTROLLER_BUTTON_START:
            buttons[cPAUSE]=value;
            stateButtons[cPAUSE]=value;
            break;
        case SDL_CONTROLLER_BUTTON_BACK:
            buttons[cVIEW]=value;
            stateButtons[cVIEW]=value;
            break;
    }

}

//**********************************************************************//

void GamepadController::updateJoystickMove(Sint16 x,Sint16 y){
    if(y<-10000 && ( x>-10000 && x<10000)){
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }
    else if(y>10000 && ( x>-10000 && x<10000)){
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }
    else if(x<-10000 && ( y>-10000 && y<10000)){
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }
    else if(x>10000 && ( y>-10000 && y<10000)){
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }
    else if(y<-10000 && x<-10000){
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }
    else if(y<-10000 && x>10000){
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }
    else if(y>10000 && x<-10000){
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }
    else if(y>10000 && x>10000){
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(true,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    }
    else{
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_UP);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_DOWN);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_LEFT);
        setButton(false,SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    }
}

//**********************************************************************//

void GamepadController::addGamepad(int id){
    if(SDL_IsGameController(id)){
        controller=SDL_GameControllerOpen(id);
        std::cout<< "---Gamepad connected---"<<std::endl;
        if( controller ) {
            joy = SDL_GameControllerGetJoystick( controller );
        }
    }
}

//**********************************************************************//

void GamepadController::removeGamepad(){
    std::cout<< "---Gamepad disconnected---"<<std::endl;
    SDL_GameControllerClose(controller);
    controller=0; joy=0;
}

} // CaxidyEngine
