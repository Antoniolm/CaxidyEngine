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

#ifndef TEXTREGION_H
#define TEXTREGION_H

#include "../GraphicEngine/region.h"
#include "matrix/structdata.h"
#include "SDL2/SDL.h"
#include "../GraphicEngine/ia/ianpc.h"
#include "rootmapgame.h"
#include "gamestatechild.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class TextRegion : public Region
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**Json constructor */
        //////////////////////////////////////////////////////////////////////////
        TextRegion(const Value & regionFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~TextRegion();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will change the time between dialogs of our textRegion.
        *    @param value -> the new time between dialogs
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setTimeBWstate(float value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will get the time between dialogs of our textRegion.
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getTimeBWstate();

    protected:

    private:
        bool lastState;     // Flag if the state is the last of the texts
        IANpc stateMachine; // State machine that manage the texts of the conversation
        float timeBWstate;  // Time between text of the conversation
        float currentTime;  // Current time of the application
        float textDelay;    // Delay of the conversation
};

#endif // TEXTREGION_H
