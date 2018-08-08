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

#include "scriptlmd.h"

namespace CaxidyEngine {

ScriptLMD::ScriptLMD()
{
    //ctor
}

//**********************************************************************//

ScriptLMD::~ScriptLMD(){
}

//**********************************************************************//

 void ScriptLMD::add(MatrixScript * aMatrix){
    script.push_back(aMatrix);
 }

//**********************************************************************//

void ScriptLMD::updateState(float time){
    std::vector<MatrixScript*>::iterator it;

    for(it=script.begin();it!=script.end();it++){
        (*it)->updateState(time);
    }
}

//**********************************************************************//

Matrix4f ScriptLMD::readMatrix(int index){
    return script[index]->getMatrix();
}

//**********************************************************************//

int ScriptLMD::getScriptState(int index){
    return script[index]->getState();
}

//**********************************************************************//

void ScriptLMD::resetState(){
    std::vector<MatrixScript *>::iterator it;
    for(it=script.begin();it!=script.end();it++){
        (*it)->resetState();
    }
}

//**********************************************************************//

int ScriptLMD::getNumState(){
    return script.size();
}

} // CaxidyEngine
