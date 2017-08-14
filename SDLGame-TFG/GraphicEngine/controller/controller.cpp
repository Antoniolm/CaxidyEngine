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

#include "controller.h"

//**********************************************************************//

Controller::~Controller()
{
    //dtor
}

//**********************************************************************//

void Controller::setState(bool value,ControllerIndex button){
    buttons[button]=value;
    if(!value)
        stateButtons[button]=false;
}

//**********************************************************************//

void Controller::checkEvent(SDL_Event & event){}

//**********************************************************************//

bool Controller::checkButton(ControllerIndex button){
    bool result=false;
    bool resultState=false;

    switch(button){
        case cUP:
            result=buttons[cUP];
            resultState=stateButtons[cUP];
        break;
        case cDOWN:
            result=buttons[cDOWN];
            resultState=stateButtons[cDOWN];
        break;
        case cRIGHT:
            result=buttons[cRIGHT];
            resultState=stateButtons[cRIGHT];
        break;
        case cLEFT:
            result=buttons[cLEFT];
            resultState=stateButtons[cLEFT];
        break;
        case cACTION:
            result=buttons[cACTION];
            resultState=stateButtons[cACTION];
        break;
        case cJUMP:
            result=buttons[cJUMP];
            resultState=stateButtons[cJUMP];
        break;
        case cATTACK:
            result=buttons[cATTACK];
            resultState=stateButtons[cATTACK];
        break;
        case cSHIELD:
            result=buttons[cSHIELD];
            resultState=stateButtons[cSHIELD];
        break;
        case cSWAPWEAPON:
            result=buttons[cSWAPWEAPON];
            resultState=stateButtons[cSWAPWEAPON];
        break;
        case cPAUSE:
            result=buttons[cPAUSE];
            resultState=stateButtons[cPAUSE];
        break;
        case cVIEW:
            result=buttons[cVIEW];
            resultState=stateButtons[cVIEW];
        break;
        case cINVENTORY:
            result=buttons[cINVENTORY];
            resultState=stateButtons[cINVENTORY];
        break;

    }


    return result && resultState;

}

//**********************************************************************//

void Controller::catchKeyBoardState(const Uint8* currentKeyStates){}

//**********************************************************************//

void Controller::consumeButtons(){
    for(int i=0;i<11;i++)
        stateButtons[i]=false;
}
