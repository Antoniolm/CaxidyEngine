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

#include <stdio.h>
#include "game.h"
#include <iostream>
#include "SDL2/SDL_mixer.h"
#include "GraphicEngine/ColladaParser/ColladaData.h"
#include "GraphicEngine/ColladaParser/ColladaLoader.h"

int main(int argc, char* args[])
{
    // ColladaLoader collada_loader("resources/geometries/model.dae");
    Game * game=Game::getInstance();
    game->loop();
    delete game;
    cout<< "The game was deleted"<<endl;

	return 0;
}

