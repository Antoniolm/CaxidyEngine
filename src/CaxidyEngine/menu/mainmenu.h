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

#ifndef MAINMENU_H
#define MAINMENU_H

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

enum MainMenuOption{
    START,
    CONTINUE,
    CONTROLS,
    OPTION,
    EXIT
};

using namespace std;

class MainMenu : public Menu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MainMenu(vec3f initPos,string fileName);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MainMenu();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new texture and that texture has a functionality (MainMenuOption)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(string fileName,MainMenuOption aOption);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will activate our menu
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the user was a saved progress or not
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setHasSave(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the current option selected in the mainmenu
        *    \return MainMenuOption
        */
        //////////////////////////////////////////////////////////////////////////
        MainMenuOption getOptionSelected();

    protected:

    private:
        vector<MainMenuOption> actionOption; // Vector of option of the menu
        Sound * openSound;                   // Sound for open an option
        Sound * moveSound;                   // Sound for movement
        Sound * ambientSound;                   // Sound for movement
        bool hasSave;
};

#endif // MAINMENU_H
