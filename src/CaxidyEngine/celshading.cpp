// *********************************************************************
// **
// ** Copyright (C) 2017-2018 Antonio David L�pez Machado
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

namespace CaxidyEngine {
    
CelShading::CelShading(Shader * aShader)
{
    shader=aShader;
}

//**********************************************************************//

CelShading::~CelShading()
{
    delete shader;
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

void CelShading::generateSilhouette(GameState & gameState){

    Context context;
    context.currentShader=shader;

    glCullFace(GL_FRONT);
        context.celShading_mode=true;

    glUseProgram(context.currentShader->getProgram());
    
    gameState.camera->activateCamera(context.currentShader->getProgram());
    gameState.rootMap->activatedLight(context.currentShader->getProgram());

    gameState.camera->activatePerspecProjection(context.currentShader->getProgram());

    gameState.rootMap->visualization(context);

    glCullFace(GL_BACK);
    context.celShading_mode=false;
}

} // CaxidyEngine 
