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

#include "menu.h"
#include "CaxidyEngine/gamestate.h"
#include "context/context.h"
#include "mesh/mesh.h"
#include "CaxidyEngine/nodescenegraph.h"
#include "material/texture.h"
#include "material/material.h"
#include "CaxidyEngine/profile.h"
#include "sound/sound.h"

namespace CaxidyEngine {
    
Menu::~Menu()
{
    //dtor
}

//**********************************************************************//

void Menu::addOption(Texture * aTexture){
    options.push_back(aTexture);
}

//**********************************************************************//

void Menu::setPosition(vec3f aPosition){
    positionMenu->translation(aPosition.x,aPosition.y,aPosition.z);
}

//**********************************************************************//

void Menu::visualization(Context & cv){}

//**********************************************************************//

void Menu::updateState(GameState & gameState){}

//**********************************************************************//

bool Menu::isActivate(){
    return activateMenu;
}

} // CaxidyEngine
