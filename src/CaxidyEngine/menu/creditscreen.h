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


#ifndef CREDITSCREEN_H
#define CREDITSCREEN_H

#include "CaxidyEngine/object3d.h"
#include "CaxidyEngine/rootmap.h"
#include "context/context.h"
#include "mesh/mesh.h"
#include "CaxidyEngine/nodescenegraph.h"
#include "material/texture.h"
#include "material/material.h"
#include "sound/sound.h"
#include "menu.h"
#include "CaxidyEngine/profile.h"
#include "mainmenu.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "collection/soundcollection.h"
#include <string>

class CreditScreen : public Menu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor
        *    @param initialPos -> Initial position of our menu
        *    @param fileName -> the name of the file with the texture of our menu
        */
        //////////////////////////////////////////////////////////////////////////
        CreditScreen(vec3f initialPos,string fileName);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~CreditScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will activate our menu
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new texture
        *    @param fileName -> the name of the file that our menu will be use
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(string fileName);

    protected:

    private:
        vec3f initialPosition; // Initial position of the menu
        Sound * openSound;     // Sound for open an option
        Sound * moveSound;     // Sound for movement
};

#endif // CREDITSCREEN_H
