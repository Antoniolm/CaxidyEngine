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

#include "pointlight.h"

namespace CaxidyEngine {

PointLight::PointLight()
{
    //ctor
}

//**********************************************************************//

PointLight::~PointLight()
{
    //dtor
}

//**********************************************************************//

PointLight::PointLight(const PointLight & aLight){
    position=aLight.position;
    ambient=aLight.ambient;
    diffuse=aLight.diffuse;
    specular=aLight.specular;

    constant=aLight.constant;
    linear=aLight.linear;
    quadratic=aLight.quadratic;
}

//**********************************************************************//

PointLight::PointLight(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,
    float aConstant,float aLinear,float aQuadratic, std::string nlight){
    position=aPos;
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;

    constant=aConstant;
    linear=aLinear;
    quadratic=aQuadratic;

    nLight=nlight;
}

//**********************************************************************//

PointLight::PointLight(const rapidjson::Value & lightFeature){
    position=vec3f(lightFeature["position"][0].GetFloat(), lightFeature["position"][1].GetFloat(), lightFeature["position"][2].GetFloat());
    ambient=vec3f(lightFeature["ambient"][0].GetFloat(), lightFeature["ambient"][1].GetFloat(), lightFeature["ambient"][2].GetFloat());
    diffuse=vec3f(lightFeature["diffuse"][0].GetFloat(), lightFeature["diffuse"][1].GetFloat(), lightFeature["diffuse"][2].GetFloat());
    specular=vec3f(lightFeature["specular"][0].GetFloat(), lightFeature["specular"][1].GetFloat(), lightFeature["specular"][2].GetFloat());

    constant=lightFeature["constant"].GetFloat();
    linear=lightFeature["linear"].GetFloat();
    quadratic=lightFeature["quadratic"].GetFloat();

    nLight=lightFeature["channel"].GetString();
}

//**********************************************************************//

void PointLight::activate(GLuint shaderID){
    glUniform3f(glGetUniformLocation(shaderID,("pointLights[" + nLight + "].position").c_str()),  position.x,  position.y, position.z);
    glUniform3f(glGetUniformLocation(shaderID,("pointLights[" + nLight + "].ambient").c_str()),  ambient.x,  ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shaderID,("pointLights[" + nLight + "].diffuse").c_str()),  diffuse.x,  diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shaderID,("pointLights[" + nLight + "].specular").c_str()), specular.x,  specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shaderID,("pointLights[" + nLight + "].constant").c_str()), constant);
    glUniform1f(glGetUniformLocation(shaderID,("pointLights[" + nLight + "].linear").c_str()), linear);
    glUniform1f(glGetUniformLocation(shaderID,("pointLights[" + nLight + "].quadratic").c_str()), quadratic);
}

//**********************************************************************//

void PointLight::setParameters(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aConstant,float aLinear,float aQuadratic){
    position=aPos;
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;

    constant=aConstant;
    linear=aLinear;
    quadratic=aQuadratic;
}

//**********************************************************************//

float PointLight::getConstant(){
    return constant;
}

//**********************************************************************//

float PointLight::getlinear(){
    return linear;
}

//**********************************************************************//

float PointLight::getQuadratic(){
    return quadratic;
}

} // CaxidyEngine
