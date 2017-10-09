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

#include "gamestate.h"
#include "shadowtexture.h"
#include "context/shader.h"
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
        *   Set the value for the light projection of the cel shading
        *   \param left
        *   \param right
        *   \param bottom
        *   \param top
        *   \param near
        *   \param far
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setOrthoProjection(float left,float right,float bottom,float top,float nearPro,float farPro);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the light camera of the cel shading
        *   \param posLight -> Position of the camera
        *   \param targetLight -> Target of the camera
        *   \param upLight -> The inclination of the camera
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setCamera(vec3f posLight,vec3f targetLight, vec3f upLight);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will get the light camera of the cel shading
        *   \return camera *
        */
        //////////////////////////////////////////////////////////////////////////
        Camera * getCamera();

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

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will generate the shadow of our scene
        *   \param & gameState
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void generateShadow(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will activate the shadow texture of our scene
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateShadowTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will get the light space of the cel shading
        *   \return Matrix4f &
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getCameraSpace();

    protected:

    private:
        Shader * shader;               //Shader for shadow generation
        Camera * camera;               //Camera of the light to generate shadow
        Matrix4f cameraSpace;          //Space of the light to generate shadow
        ShadowTexture * depthTexture;  //Texture with the depth of the scene
};

#endif // CELSHADING_H
