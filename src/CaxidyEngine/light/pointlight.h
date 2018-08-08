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


#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "light.h"

namespace CaxidyEngine {

class PointLight : public Light
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        PointLight();

        //////////////////////////////////////////////////////////////////////////
        /** Copy constructor */
        //////////////////////////////////////////////////////////////////////////
        PointLight(const PointLight & aLight);

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with parameters */
        //////////////////////////////////////////////////////////////////////////
        PointLight(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,
            float aConstant,float aLinear,float aQuadratic, std::string nlight="0");

        //////////////////////////////////////////////////////////////////////////
        /** Constructor with json */
        //////////////////////////////////////////////////////////////////////////
        PointLight(const rapidjson::Value & lightFeature);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~PointLight();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will activate our light in the currentShader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will set a point light
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setParameters(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aConstant,float aLinear,float aQuadratic);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the constant value in our light
        *   \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getConstant();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the linear value in our light
        *   \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getlinear();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   This method will get the quadratic value in our light
        *   \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getQuadratic();

    protected:

    private:
        float constant;   // Constant component
        float linear;     // linear component
        float quadratic;  // Quadratic component
        std::string nLight;    // Number of light
};

} // CaxidyEngine

#endif // POINTLIGHT_H
