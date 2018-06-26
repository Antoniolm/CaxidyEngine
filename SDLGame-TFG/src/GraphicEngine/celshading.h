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

#ifndef CELSHADING_H
#define CELSHADING_H

#include "gamestate.h"
#include "celtexture.h"
#include "context/shader.h"
#include "context/context.h"
#include "matrix/matrix4f.h"
#include "camera.h"
#include "matrix/structdata.h"

class CelShading
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        CelShading(Shader * aShader);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~CelShading();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will set the shader that will use the cel shading
        *   \param * aShader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setShader(Shader * aShader);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will get the shader that will use the cel shading
        *   \return Shader *
        */
        //////////////////////////////////////////////////////////////////////////
        Shader * getShader();

        void generateSilhouette(GameState & gameState);

    protected:

    private:
        Shader * shader;               //Shader for shadow generation
};

#endif // CELSHADING_H
