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


#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "light.h"

namespace CaxidyEngine {
    
class DirectionalLight : public Light
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        DirectionalLight();

        //////////////////////////////////////////////////////////////////////////
        /** Copy constructor */
        //////////////////////////////////////////////////////////////////////////
        DirectionalLight(const DirectionalLight & aLight);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters */
        //////////////////////////////////////////////////////////////////////////
        DirectionalLight(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with json */
        //////////////////////////////////////////////////////////////////////////
        DirectionalLight(const rapidjson::Value & lightFeature);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~DirectionalLight();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our light in the currentShader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set a directional light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(const vec3f & aDir,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular);

    protected:

    private:
};

} // CaxidyEngine

#endif // DIRECTIONALLIGHT_H
