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

#include "material.h"

Material::Material()
{
    texture=0;
    ambient=vec3f();
    diffuse=vec3f();
    specular=vec3f();
    shininess=0;
    bumpTexture=0;
    index=mVOID;
}

//**********************************************************************//

Material::Material(const Material & aMaterial){
    ambient=aMaterial.ambient;
    diffuse=aMaterial.diffuse;
    specular=aMaterial.specular;
    shininess=aMaterial.shininess;

    texture=new Texture((*aMaterial.texture));

    if(aMaterial.bumpTexture!=0)
        bumpTexture=new Texture((*aMaterial.bumpTexture));
    else
        bumpTexture=0;

    index=aMaterial.index;
}

//**********************************************************************//

Material::Material(const vec3f & anAmbient,const vec3f & aDiffuse,const vec3f &aSpecular,float aShini,const string & aFileTextur,const string & aFileBumpTextur,MaterialIndex aIndex){
    ambient=anAmbient;
    diffuse=aDiffuse;
    specular=aSpecular;
    shininess=aShini;
    index=aIndex;

    bumpTexture=0;
    if(aFileBumpTextur!="")
        bumpTexture=new Texture(aFileBumpTextur);

    texture=0;
    if(aFileTextur!="")
        texture=new Texture(aFileTextur);
}

//**********************************************************************//

Material::~Material()
{
    if(texture!=0)
        delete texture;
}

//**********************************************************************//

void Material::activate(GLuint shaderID){
    //Bind the texture
    texture->bindTexture();

    //Set value to uniform about material
    glUniform3f(glGetUniformLocation(shaderID, "material.ambient"),  ambient.x,  ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shaderID, "material.diffuse"),  diffuse.x,  diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shaderID, "material.specular"), specular.x,  specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shaderID, "material.shininess"),    shininess);

    glUniform1i(glGetUniformLocation(shaderID, "normalMapping"), false);
    if(bumpTexture!=0){
        glUniform1i(glGetUniformLocation(shaderID, "normalMapping"), true);
        bumpTexture->bindTexture(1);
    }
}

//**********************************************************************//

void Material::setAmbient(const vec3f & anAmbient){
    ambient=anAmbient;
}

//**********************************************************************//

void Material::setDiffuse(const vec3f & aDiffuse){
    diffuse=aDiffuse;
}

//**********************************************************************//

void Material::setSpecular(const vec3f &aSpecular){
    specular=aSpecular;
}

//**********************************************************************//

void Material::setShininess(float aShini){
    shininess=aShini;
}

//**********************************************************************//

void Material::setTexture(const string & aFileTextur){
    texture=0;
    if(aFileTextur!="")
        texture=new Texture(aFileTextur);
}

//**********************************************************************//

void Material::setTexture(Texture * aTexture){
    texture=aTexture;
}

//**********************************************************************//

void Material::setBumpTexture(Texture * aBTexture){
    bumpTexture=aBTexture;
}

//**********************************************************************//

vec3f Material::getAmbient(){
    return ambient;
}

//**********************************************************************//

vec3f Material::getDiffuse(){
    return diffuse;
}

//**********************************************************************//

vec3f Material::getSpecular(){
    return specular;
}

//**********************************************************************//

float Material::getShininess(){
    return shininess;
}

//**********************************************************************//

Texture * Material::getTexture(){
    return texture;
}

//**********************************************************************//

Texture * Material::getBumpTexture(){
    return bumpTexture;
}

//**********************************************************************//

MaterialIndex Material::getIndex(){
    return index;
}

//**********************************************************************//

void Material::setMaterial(const Material & material){

    ambient=material.ambient;
    diffuse=material.diffuse;
    specular=material.specular;
    shininess=material.shininess;

    texture->setTexture((*material.texture));

    if(material.bumpTexture!=0)
        bumpTexture=new Texture((*material.bumpTexture));
    else
        bumpTexture=0;


    index=material.index;

}
