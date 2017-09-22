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

#ifndef CELSHADING_H
#define CELSHADING_H

#include "context/shader.h"
#include "gamestate.h"

class CelShading
{
    public:
        CelShading(Shader * aShader);

        virtual ~CelShading();


        void activate(GameState & gameState);
        void disactivate();
    protected:

    private:

        Shader * shader;
};

#endif // CELSHADING_H
