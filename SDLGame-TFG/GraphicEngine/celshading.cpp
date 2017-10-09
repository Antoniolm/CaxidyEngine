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

#include "celshading.h"

CelShading::CelShading(Shader * aShader)
{
    shader=aShader;
    camera=new Camera();
    shader=aShader;
    depthTexture=new ShadowTexture(2048,2048);
}

//**********************************************************************//

CelShading::~CelShading()
{
    delete camera;
    delete shader;
    delete depthTexture;
}

//**********************************************************************//

void CelShading::setOrthoProjection(float left,float right,float bottom,float top,float nearPro,float farPro){
    camera->setOrthographicProjection(left,right,bottom,top,nearPro,farPro);
}

//**********************************************************************//

void CelShading::setCamera(vec3f posLight,vec3f targetLight, vec3f upLight){
    camera->setCamera(posLight,targetLight,upLight);
    camera->createCamera();
}

//**********************************************************************//

Camera * CelShading::getCamera(){
    return camera;
}

//**********************************************************************//

void CelShading::setShader(Shader * aShader){
    shader=aShader;
}

//**********************************************************************//

Shader * CelShading::getShader(){
    return shader;
}

//**********************************************************************//

void CelShading::generateShadow(GameState & gameState){
    cameraSpace.setMatrix(camera->getView());
    cameraSpace.product(camera->getOrthoProyection().getMatrix());

    Context context;
    context.shadow_mode=true;
    context.currentShader=shader;
    glUseProgram(context.currentShader->getProgram());
    glUniformMatrix4fv(glGetUniformLocation(context.currentShader->getProgram(), "lightSpaceMatrix"), 1, GL_FALSE, cameraSpace.getMatrix());

    depthTexture->setShadowBuffer(true);
    gameState.rootMap->visualization(context);
    depthTexture->setShadowBuffer(false);
}

//**********************************************************************//

void CelShading::activateShadowTexture(){
    depthTexture->bindTexture();
}

//**********************************************************************//

Matrix4f & CelShading::getCameraSpace(){
    return cameraSpace;
}
