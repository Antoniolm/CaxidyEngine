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

#ifndef MATERIALSTACK_H
#define MATERIALSTACK_H

#include "material/material.h"
#include <vector>

namespace CaxidyEngine {
    
class MaterialStack
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MaterialStack();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MaterialStack();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will push a new material in the stack
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void push(Material * aMaterial);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will pop the material in the top of stack
        *    \param cont -> Number of materials that our method will pop
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void pop(int cont);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will get the material in the top
        *    \return The material in the top of the stack
        */
        //////////////////////////////////////////////////////////////////////////
        Material * getMaterial();

    protected:

    private:
        std::vector<Material*> mainStack;   //Stack of material
};

} // CaxidyEngine

#endif // MATERIALSTACK_H
