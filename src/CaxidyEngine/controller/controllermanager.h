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


#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include "controller.h"
#include "keyboardcontroller.h"
#include "gamepadcontroller.h"

class ControllerManager
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ControllerManager();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ControllerManager();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will change the state of a button of our controller
        *    @param value -> the state of our button
        *    @param button -> the index of the button that our want to change
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setState(bool value,ControllerIndex button);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will update the event/buttons of our gamepadcontroller
        *    @param event -> our current event
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void checkEvent(SDL_Event & event);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will check a button of our system
        *    @param  button -> the index of the button that our want to check
        *    \return bool -> true if the buttons is down - false if is down
        */
        //////////////////////////////////////////////////////////////////////////
        bool checkButton(ControllerIndex button);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the current state of our keyboard
        *    @param currentKeyStates -> the state of our keyboard
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void catchKeyBoardState(const Uint8* currentKeyStates);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will consume all our buttons.(used to change map )
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void consumeButtons();

    protected:

    private:
        KeyboardController keyboardController;  // Keyboard controller
        GamepadController gamepadController;    // Game pad controller
};

#endif // CONTROLLERMANAGER_H
