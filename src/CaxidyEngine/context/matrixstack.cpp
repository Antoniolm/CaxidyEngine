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

#include "matrixstack.h"

namespace CaxidyEngine {
    
MatrixStack::MatrixStack()
{

}

//**********************************************************************//

MatrixStack::~MatrixStack()
{
    //dtor
}

//**********************************************************************//

void MatrixStack::push(){
    currentMatrix.identity();
    Matrix4f newMatrix(currentMatrix);
    mainStack.push_back(newMatrix);
}

//**********************************************************************//

void MatrixStack::pop(int cont){
    int tam=mainStack.size()-1;
    int iter=0;
    for(int i=tam;i>0 && iter<cont;i--){
        mainStack.pop_back();
        iter++;
    }
}

//**********************************************************************//

void MatrixStack::activate(GLuint shaderID){
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"transform"),1,GL_FALSE,getMatrix().getMatrix());
}

//**********************************************************************//

void MatrixStack::asignIdentity(){
    currentMatrix.identity();
}

//**********************************************************************//

void MatrixStack::cMatrix(const Matrix4f & mat ){

    Matrix4f newMatrix(mat);
    mainStack.push_back(mat);

}

//**********************************************************************//

void MatrixStack::cTraslation( const float dx, const float dy, const float dz ){
    Matrix4f auxMatrix;
    auxMatrix.translation(dx,dy,dz);
    mainStack.push_back(auxMatrix);
}

//**********************************************************************//

void MatrixStack::cScale ( const float sx, const float sy, const float sz ){
    Matrix4f auxMatrix;
    auxMatrix.scale(sx,sy,sz);
    mainStack.push_back(auxMatrix);
}

//**********************************************************************//

void MatrixStack::cRotation ( const float ang_gra,const float ex, const float ey, const float ez ){
    Matrix4f auxMatrix;
    auxMatrix.rotation(ang_gra,ex,ey,ez);
    mainStack.push_back(auxMatrix);
}

//**********************************************************************//

void MatrixStack::clean(){
    mainStack.clear();
}

//**********************************************************************//

Matrix4f & MatrixStack::getMatrix(){
   currentMatrix.identity();
   Matrix4f matrix;
   for(int i=mainStack.size()-1;i>=0;i--)
        currentMatrix.product(mainStack[i].getMatrix());
    return currentMatrix;
}

} // CaxidyEngine
