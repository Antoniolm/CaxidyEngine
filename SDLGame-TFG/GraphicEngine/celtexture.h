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

#ifndef CELTEXTURE_H
#define CELTEXTURE_H

#include "material/texture.h"

class CelTexture : public Texture
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        CelTexture(GLuint aWidth = 1024,GLuint aHeight = 1024);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~CelTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will bind that texture in our current Shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
    	void bindTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create a openGL texture
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will indicate if the user will use or not our frame buffer
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setBuffer(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return our frame buffer
        *   \return GLuint
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getFrameBuffer();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return the id of our cel texture
        *   \return GLuint
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will set the size of our cel texture
        *   @param width -> the width of the texture
        *   @param height -> the height of the texture
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setSize(GLuint aWidth = 1024,GLuint aHeight = 1024);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return the height of the texture
        *   \return GLuint
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getHeight();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will return the width of the texture
        *   \return GLuint
        */
        //////////////////////////////////////////////////////////////////////////
        GLuint getWidth();

    protected:

    private:
        GLuint celMapFBO;   // Frame buffer of depth texture
        GLuint celMap;      // Texture of depth
        GLuint height;  // Height of shadow texture
        GLuint width;   // Width of shadow texture
};

#endif // CELTEXTURE_H
