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


#ifndef GAMESTATECHILD_H
#define GAMESTATECHILD_H

#include "GraphicEngine/gamestate.h"

class GameStateChild : public GameState
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        GameStateChild();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~GameStateChild();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will init the match
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void initPlay(GLuint shaderID);

    protected:

    private:
};

#endif // GAMESTATECHILD_H
