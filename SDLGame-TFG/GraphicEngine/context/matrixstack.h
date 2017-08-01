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

#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include "matrix/matrix4f.h"
#include <vector>
#include "shader.h"

class MatrixStack
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MatrixStack();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MatrixStack();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will push a new Matrix in the stack
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void push();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will pop the matrix in the top of stack
        *    \param cont -> Number of matrix that our method will pop
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void pop(int cont);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will activate the currentMatrix
        *    \param Shader -> the program where our transform will be activated
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will asign the identity matrix to the currentMatrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void asignIdentity();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between the currentMatrix and the matrix parameter
        *    \param mat -> this matrix4f will push in our stack
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void cMatrix(const Matrix4f & mat );

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between the currentMatrix and a translation matrix
        *    \param sx,sy,sz -> Value for a new transformation matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void cTraslation( const float dx, const float dy, const float dz ) ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between the currentMatrix and a scale matrix
        *    \param sx,sy,sz -> Value for a new transformation matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void cScale ( const float sx, const float sy, const float sz ) ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will make the product between the currentMatrix and a rotation matrix
        *    \param ang_gra,ex,ey,ez -> Value for a new transformation matrix
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void cRotation ( const float ang_gra,const float ex, const float ey, const float ez ) ;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the currentMatrix
        *    \return GLfloat -> the matrix
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getMatrix();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will clean our stack
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void clean();

    protected:

    private:
        Matrix4f currentMatrix;          // Current Matrix 4x4 in the stack
        std::vector<Matrix4f> mainStack; // Matrix
};

#endif // MATRIXSTACK_H
