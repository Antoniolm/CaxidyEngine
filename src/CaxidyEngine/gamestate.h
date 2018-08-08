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

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "controller/controllermanager.h"
#include "menu/menu.h"
#include "menu/pausemenu.h"
#include "menu/mainmenu.h"
#include "menu/deadmenu.h"
#include "menu/creditscreen.h"
#include "menu/optionmenu.h"
#include "menu/controlmenu.h"
#include "menu/loadingscreen.h"
#include "menu/moviescreen.h"
#include "menu/inventorymenu.h"
#include "speakingsketch.h"
#include "rootmap.h"
#include "camera.h"

namespace CaxidyEngine {
    
class DeadMenu;
class CreditScreen;
class LoadingScreen;
class MainMenu;
class PauseMenu;
class OptionMenu;
class ControlMenu;
class MovieScreen;
class InventoryMenu;
class Camera;
class SpeakingSketch;
class GameState
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        GameState();

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~GameState();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will init the match
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        virtual void initPlay(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will update the match
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updatePlay();

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will update the loading screen
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateLoading(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will update the credit screen
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateCredit(GLuint shaderID);

        //////////////////////////////////////////////////////////////////////////
        /**
        *   It will update the main menu
        *   @param shaderID -> the id of our current activated shader
        *   \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateMenu(GLuint shaderID);

        float time;                     // Time of the application
        ControllerManager * controller; // Manager of the controllers
        RootMap * rootMap;              // Map/Scene of the video game
        PauseMenu * pauseMenu;          // Menu of pause
        MainMenu * mainMenu;            // Main menu
        DeadMenu * deadMenu;            // Menu of death
        CreditScreen * creditScreen;    // Screen of credit
        OptionMenu * optionMenu;        // Menu of options
        ControlMenu * controlMenu;      // Menu of controls
        LoadingScreen * loadScreen;     // Screen of load
        MovieScreen * movie;            // Screen of movie
        InventoryMenu * inventoryMenu;  // Inventory menu
        SpeakingSketch * speakingSketch;// SpeakingSketch
        Camera * camera;                // Camera of the video game
        vec3f refPoint;                 // Point of reference


    protected:

    private:
};

} // CaxidyEngine 

#endif // GAMESTATE_H
