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

#ifndef LIGHT_H
#define LIGHT_H

#include "../matrix/structdata.h"
#include "../context/shader.h"
#include <string>
#include <cstdlib>
#include "../../../resources/lib/rapidjson/document.h"

class Light
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Light();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our light in the currentShader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void activate(GLuint shaderID) = 0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the position in our light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(const vec3f & aPos);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the position in our light
        *   \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getPosition();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the ambient in our light
        *   \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getAmbient();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the diffuse in our light
        *   \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getDiffuse();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the specular in our light
        *   \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getSpecular();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the shininess in our light
        *   \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getShininess();

    protected:
        vec3f position; // Position of the light
        vec3f ambient;  // Ambient component of the light
        vec3f diffuse;  // Diffuse component of the light
        vec3f specular; // Specular component of the light

    private:

};

#endif // LIGHT_H
