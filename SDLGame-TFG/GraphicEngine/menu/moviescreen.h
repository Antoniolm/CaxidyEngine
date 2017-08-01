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

#ifndef MOVIESCREEN_H
#define MOVIESCREEN_H

#include "menu.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include "collection/soundcollection.h"
#include "../lib/rapidjson/document.h"

using namespace rapidjson;

class GameState;
class MovieScreen : public Menu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        MovieScreen(const Value & movieFeatures);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~MovieScreen();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & cv);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the movie is activated or not
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setActivate(bool value);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return if the movie is activated or not
        *    \return bool
        */
        //////////////////////////////////////////////////////////////////////////
        bool isActivated();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will activate all the texture of our movie (require when our rootMap
        *    is created in a thread)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void activateAllTexture();

        void enableSound(bool value);
    protected:

    private:
        vector<string> textures;    // Vector of textures of the movie screen
        Sound * actionSound;        // Action sound of the screen
        Sound * ambientSound;       // Ambient sound of the screen
};

#endif // MOVIESCREEN_H

