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

#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include "object3d.h"
#include "rootmap.h"
#include "text.h"
#include "context/context.h"
#include "mesh/mesh.h"
#include "nodescenegraph.h"
#include "material/texture.h"
#include "material/material.h"
#include "sound/sound.h"
#include "menu.h"
#include "profile.h"
#include "mainmenu.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "collection/soundcollection.h"
#include "optionmanager.h"
#include "window.h"
#include <cstdlib>

using namespace std;

class OptionMenu : public Menu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        OptionMenu(vec3f posMenu,string mat,string currentMat, string matBack);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~OptionMenu();

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
        *    It will set the position of our menu
        *    @param aPosition -> the new position of our menu
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setPosition(vec3f aPosition);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will activate our menu
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activate();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add a new texture of the options
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(string fileName);

    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will update the option of the menu
        *   @param option -> option to update
        *   @param value -> the new value of that option
        */
        //////////////////////////////////////////////////////////////////////////
        void updateOption(int option,string value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will initialize the options of the menu
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void initOptions();

        vector<pair<int,int> > resolution; //Vector of resolutions
        int indexResolution;    // Index for the current resolution
        bool window;            // False -> full screen
        int volume;             // Current volume
        Text * resolText;       // Text for current resolution
        Text * windText;        // Text for current window mode
        Text * volText;         // Text for current volume
        Sound * openSound;      // Sound for open an option
        Sound * moveSound;      // Sound for movement
        Material * material;    // Material for background
};

#endif // OPTIONMENU_H
