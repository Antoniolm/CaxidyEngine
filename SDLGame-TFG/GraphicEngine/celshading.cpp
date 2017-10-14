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
    celTexture=new CelTexture(2048,2048);
}

//**********************************************************************//

CelShading::~CelShading()
{
    delete shader;
    delete celTexture;
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

void CelShading::generateCelTexture(GameState & gameState){
    cameraSpace.setMatrix(gameState.camera->getView());
    cameraSpace.product(gameState.camera->getPersProyection().getMatrix());

    Context context;
    context.shadow_mode=true;
    context.currentShader=shader;
    glUseProgram(context.currentShader->getProgram());
    glUniformMatrix4fv(glGetUniformLocation(context.currentShader->getProgram(), "lightSpaceMatrix"), 1, GL_FALSE, cameraSpace.getMatrix());

    celTexture->setBuffer(true);
    gameState.rootMap->visualization(context);
    celTexture->setBuffer(false);
}

//**********************************************************************//

void CelShading::activateTexture(){
    glActiveTexture(GL_TEXTURE4);
    celTexture->bindTexture();
}

//**********************************************************************//

Matrix4f & CelShading::getCameraSpace(){
    return cameraSpace;
}
