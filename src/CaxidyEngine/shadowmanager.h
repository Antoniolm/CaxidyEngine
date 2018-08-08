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

#ifndef SHADOWMANAGER_H
#define SHADOWMANAGER_H

#include "shadowtexture.h"
#include "context/shader.h"
#include "matrix/matrix4f.h"
#include "camera.h"
#include "matrix/structdata.h"

namespace CaxidyEngine {

class ShadowManager
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ShadowManager(Shader * aShader);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ShadowManager();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   Set the value for the light projection of our shadow manager
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
        *   Set the light camera of our shadow manager
        *   \param posLight -> Position of the camera
        *   \param targetLight -> Target of the camera
        *   \param upLight -> The inclination of the camera
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setCamera(vec3f posLight,vec3f targetLight, vec3f upLight);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will get the light camera of our shadow manager
        *   \return camera *
        */
        //////////////////////////////////////////////////////////////////////////
        Camera * getCamera();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will set the shader that will use our shadow manager
        *   \param * aShader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setShader(Shader * aShader);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will get the shader that will use our shadow manager
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
        *   It will get the light space of our shadow manage
        *   \return Matrix4f &
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getLightSpace();
    protected:

    private:
        Shader * shader;                //Shader for shadow generation
        Camera * lightCamera;           //Camera of the light to generate shadow
        Matrix4f lightSpace;            //Space of the light to generate shadow
        ShadowTexture * depthTexture;   //Texture with the depth of the scene

};

} // CaxidyEngine 

#endif // SHADOWMANAGER_H
