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
}

CelShading::~CelShading()
{
    delete shader;
}


void CelShading::activate(GameState & gameState){
    glCullFace(GL_FRONT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader->getProgram()); //We use the program now

    gameState.camera->activateCamera(shader->getProgram());
    gameState.camera->activatePerspecProjection(shader->getProgram());

}

void CelShading::disactivate(){
    glCullFace(GL_BACK);
}
