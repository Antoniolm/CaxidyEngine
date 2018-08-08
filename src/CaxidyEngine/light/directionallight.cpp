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


#include "directionallight.h"

namespace CaxidyEngine {
    
DirectionalLight::DirectionalLight()
{
    //ctor
}

//**********************************************************************//

DirectionalLight::~DirectionalLight()
{
    //dtor
}

//**********************************************************************//

DirectionalLight::DirectionalLight(const DirectionalLight & aLight){
    position=aLight.position;
    ambient=aLight.ambient;
    diffuse=aLight.diffuse;
    specular=aLight.specular;
}

//**********************************************************************//

DirectionalLight::DirectionalLight(const vec3f & aPos,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular){
    position=aPos;
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;
}

//**********************************************************************//

DirectionalLight::DirectionalLight(const rapidjson::Value & lightFeature){
    position=vec3f(lightFeature["position"][0].GetFloat(), lightFeature["position"][1].GetFloat(), lightFeature["position"][2].GetFloat());
    ambient=vec3f(lightFeature["ambient"][0].GetFloat(), lightFeature["ambient"][1].GetFloat(), lightFeature["ambient"][2].GetFloat());
    diffuse=vec3f(lightFeature["diffuse"][0].GetFloat(), lightFeature["diffuse"][1].GetFloat(), lightFeature["diffuse"][2].GetFloat());
    specular=vec3f(lightFeature["specular"][0].GetFloat(), lightFeature["specular"][1].GetFloat(), lightFeature["specular"][2].GetFloat());
}

//**********************************************************************//

void DirectionalLight::activate(GLuint shaderID){
    //Set value to uniform about light
    glUniform3f(glGetUniformLocation(shaderID, "dirLight.direction"),  position.x,  position.y, position.z);
    glUniform3f(glGetUniformLocation(shaderID, "dirLight.ambient"),  ambient.x,  ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shaderID, "dirLight.diffuse"),  diffuse.x,  diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shaderID, "dirLight.specular"), specular.x,  specular.y, specular.z);
}


//**********************************************************************//

void DirectionalLight::setParameters(const vec3f & aDir,const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular){
    position=aDir;
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;
}

} // CaxidyEngine
