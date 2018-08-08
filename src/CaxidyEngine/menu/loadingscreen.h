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

#ifndef LOADINGSCREEN_H
#define LOADINGSCREEN_H

#include "menu.h"
#include "collection/meshcollection.h"
#include "collection/materialcollection.h"
#include <string>

namespace CaxidyEngine {
    
class LoadingScreen : public Menu
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        LoadingScreen(vec3f initPosition, float delay, std::string fileName);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~LoadingScreen();

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
        *    It will add a new texture
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void add(std::string fileName);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set the delay of our animation
        *    @param aniDelay -> the new delay of our animation
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setDelay(float aniDelay);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the delay of our animation
        *    \return float
        */
        //////////////////////////////////////////////////////////////////////////
        float getDelay();
    protected:

    private:
        float animationDelay;  // Delay between animations
};

} // CaxidyEngine

#endif // LOADINGSCREEN_H
