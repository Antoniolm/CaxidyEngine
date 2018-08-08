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

#ifndef MATRIX4FDYNAMIC_H
#define MATRIX4FDYNAMIC_H

#include "matrix4f.h"

namespace CaxidyEngine {
    
class Matrix4fDynamic
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Matrix4fDynamic();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the Matrix4xf. That change need the
        *    current time in our application
        *    \return the new state of the matrix4f
        */
        //////////////////////////////////////////////////////////////////////////
        virtual Matrix4f & updateState(float time)=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will reset our currentMatrix to initial state
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void resetState()=0;

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the currentMatrix
        *    \return Matrix4f &
        */
        //////////////////////////////////////////////////////////////////////////
        Matrix4f & getMatrix();

    protected:
        Matrix4f currentMatrix; // Matrix 4x4

    private:
};

} // CaxidyEngine

#endif // MATRIX4FDYNAMIC_H
