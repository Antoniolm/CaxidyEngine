// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David L�pez Machado
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

#ifndef JUMPBUTTONGAME_H
#define JUMPBUTTONGAME_H

#include "GraphicEngine/voxels/jumpbutton.h"
#include "rapidjson/document.h"

using namespace rapidjson;

class JumpButtonGame : public JumpButton
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   Constructor
        *   @param buttonFeatures -> the value json that contain all the information of the jump button object
        */
        //////////////////////////////////////////////////////////////////////////
        JumpButtonGame(const Value & buttonFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~JumpButtonGame();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);

    protected:

    private:

};

#endif // JUMPBUTTONGAME_H

