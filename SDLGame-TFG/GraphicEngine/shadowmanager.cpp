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

#include "shadowmanager.h"

ShadowManager::ShadowManager(Shader * aShader){
    lightCamera=new Camera();
    shader=aShader;
    depthTexture=new ShadowTexture();
}

//**********************************************************************//

ShadowManager::~ShadowManager(){
    delete lightCamera;
    delete shader;
    delete depthTexture;
}

//**********************************************************************//

void ShadowManager::setOrthoProjection(float left,float right,float bottom,float top,float nearPro,float farPro){
    lightCamera->setOrthographicProjection(left,right,bottom,top,nearPro,farPro);
}

//**********************************************************************//

void ShadowManager::setCamera(vec3f posLight,vec3f targetLight, vec3f upLight){
    lightCamera->setCamera(posLight,targetLight,upLight);
    lightCamera->createCamera();
}

//**********************************************************************//

Camera * ShadowManager::getCamera(){
    return lightCamera;
}

//**********************************************************************//

void ShadowManager::setShader(Shader * aShader){
    shader=aShader;
}

//**********************************************************************//

Shader * ShadowManager::getShader(){
    return shader;
}

//**********************************************************************//

void ShadowManager::generateShadow(GameState & gameState){
    lightSpace.setMatrix(lightCamera->getView());
    lightSpace.product(lightCamera->getOrthoProyection().getMatrix());

    Context context;
    context.shadow_mode=true;
    context.currentShader=shader;
    glUseProgram(context.currentShader->getProgram());
    glUniformMatrix4fv(glGetUniformLocation(context.currentShader->getProgram(), "lightSpaceMatrix"), 1, GL_FALSE, lightSpace.getMatrix());

    depthTexture->setShadowBuffer(true);
    gameState.rootMap->visualization(context);
    depthTexture->setShadowBuffer(false);
}

//**********************************************************************//

void ShadowManager::activateShadowTexture(){
    depthTexture->bindTexture();
}

//**********************************************************************//

Matrix4f & ShadowManager::getLightSpace(){
    return lightSpace;
}
