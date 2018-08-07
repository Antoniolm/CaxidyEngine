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

#ifndef CONTEXT_H
#define CONTEXT_H

#include "matrixstack.h"
#include "matrix/structdata.h"
#include "collection/materialcollection.h"
#include "GraphicEngine/object3d.h"
#include "materialstack.h"
#include "light/light.h"
#include "shader.h"
#include <vector>

class MaterialStack;
class Object3D;
class Context
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Context();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Context();

        unsigned int visualization_mode;    // Visualization mode
        unsigned camera_mode;               // camera mode
        bool shadow_mode;                   // flag shadow mode
        bool celShading_mode;               // flag cel shading mode
        MatrixStack matrixStack;            // Stack of matrix
        MaterialStack materialStack;        // Stack of material
        Shader * currentShader;             // Current shader
        Matrix4f currentTransf;             // current Matrix
        MaterialIndex currentMaterialIndex; // Current material inde
        vec3f minVisualPosition;            // Max visualization position
        vec3f maxVisualPosition;            // Min visualization position


    protected:

    private:
};

#endif // CONTEXT_H
