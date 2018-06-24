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

#include "materialstack.h"

MaterialStack::MaterialStack()
{
    //ctor
}

//**********************************************************************//

MaterialStack::~MaterialStack()
{
    //dtor
}

//**********************************************************************//

void MaterialStack::push(Material * aMaterial){
    mainStack.push_back(aMaterial);
}

//**********************************************************************//

void MaterialStack::pop(int cont){
    int tam=mainStack.size()-1;
    int iter=0;
    for(int i=tam;i>0 && iter<cont;i--){
        mainStack.pop_back();
        iter++;
    }
}

//**********************************************************************//
Material * MaterialStack::getMaterial(){
    return mainStack[mainStack.size()-1];
}
