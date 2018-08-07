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

#ifndef SHADOWTEXTURE_H
#define SHADOWTEXTURE_H

#include "material/texture.h"

class ShadowTexture : public Texture
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ShadowTexture(GLuint width = 1024,GLuint height = 1024);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ShadowTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will bind that texture in our current Shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
    	void bindTexture();

    	//////////////////////////////////////////////////////////////////////////
        /**
        *   It will indicate if the user will use or not our shadow buffer
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setShadowBuffer(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return our frame buffer
        *   \return GLuint
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getFrameBuffer();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return the id of our shadow texture
        *   \return GLuint
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will set the size of our depth texture
        *   @param width -> the width of our texture
        *   @param height -> the height of our texture
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setSize(GLuint width = 1024,GLuint height = 1024);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return the height of our texture
        *   \return GLuint
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getHeight();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return the width of our texture
        *   \return GLuint
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getWidth();
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create a openGL texture
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createTexture();

        GLuint depthMapFBO;   // Frame buffer of depth texture
        GLuint depthMap;      // Texture of depth
        GLuint shadowHeight;  // Height of shadow texture
        GLuint shadowWidth;   // Width of shadow texture
};

#endif // SHADOWTEXTURE_H
