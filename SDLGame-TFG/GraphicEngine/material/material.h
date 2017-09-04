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

#ifndef MATERIAL_H
#define MATERIAL_H

#include "matrix/structdata.h"
#include <string>
#include "./collection/materialcollection.h"
#include "texture.h"
#include "context/shader.h"

using namespace std;


class Material
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Material();

        //////////////////////////////////////////////////////////////////////////
        /** Copy constructor */
        //////////////////////////////////////////////////////////////////////////
        Material(const Material & aMaterial);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters*/
        //////////////////////////////////////////////////////////////////////////
        Material(const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aShini,const string & aFileTextur,const string & aFileBumpTextur="",MaterialIndex aIndex=mVOID);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Material();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our material in our current Shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the ambient in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setAmbient(const vec3f & anAmbient);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the diffuse in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDiffuse(const vec3f & aDiffuse);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the specular in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setSpecular(const vec3f &aSpecular);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the shininess in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setShininess(float aShini);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the texture in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setTexture(const string & aFileTextur);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the texture in ourmaterial
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setTexture(Texture * aTexture);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set the texture in ourmaterial
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setBumpTexture(Texture * aBTexture);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the ambient in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getAmbient();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the diffuse in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getDiffuse();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the specular in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f getSpecular();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the shininess in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        float getShininess();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the texture in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        Texture * getTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the bump texture in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        Texture * getBumpTexture();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the index in our material
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        MaterialIndex getIndex();

        void setMaterial(const Material & material);

    protected:

    private:
        vec3f ambient;          // Ambient component
        vec3f diffuse;          // Diffuse component
        vec3f specular;         // Specular component
        float shininess;        // Shininess component
        Texture * texture;      // Texture of the material
        Texture * bumpTexture;  // bump texture of the material
        MaterialIndex index;    // Index of the material
};

#endif // MATERIAL_H
