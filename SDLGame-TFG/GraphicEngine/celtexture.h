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
        CelTexture();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~CelTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create a openGL texture
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createTexture();

    protected:

    private:
        GLuint celMapFBO;   // Frame buffer of depth texture
        GLuint celMap;      // Texture of depth
        GLuint shadowHeight;  // Height of shadow texture
        GLuint shadowWidth;   // Width of shadow texture
};

#endif // CELTEXTURE_H
