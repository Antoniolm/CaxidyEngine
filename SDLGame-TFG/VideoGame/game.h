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

#ifndef GAME_H
#define GAME_H

#include "../GraphicEngine/window.h"
#include "../GraphicEngine/context/context.h"
#include "../GraphicEngine/nodescenegraph.h"
#include "../GraphicEngine/sound/sound.h"
#include "../GraphicEngine/matrix/matrixstatic.h"
#include "../GraphicEngine/matrix/linearmovement.h"
#include "../GraphicEngine/matrix/axisrotation.h"
#include "../GraphicEngine/rootmap.h"
#include "rootmapgame.h"
#include "gamestatechild.h"
#include "../GraphicEngine/camera.h"
#include "../GraphicEngine/matrix/structdata.h"
#include "../GraphicEngine/text.h"
#include "../GraphicEngine/controller/controllermanager.h"
#include "../GraphicEngine/profile.h"
#include "../GraphicEngine/notification.h"
#include "../GraphicEngine/gamestate.h"
#include "../GraphicEngine/savedmanager.h"
#include "../GraphicEngine/optionmanager.h"
#include "herostate.h"
#include "../GraphicEngine/shadowtexture.h"
#include "../GraphicEngine/shadowmanager.h"
#include "../GraphicEngine/celshading.h"
#include "inventory.h"
#include "projectile.h"
#include "avatar/hero.h"
#include "../GraphicEngine/Menu/mainmenu.h"
#include "inventorymenugame.h"
#include <sstream>
class Game
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Game();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    Method will contain the main loop of the videoGame
        *    In that loop will have the detection of keyboard events
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void loop();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will set if the game is closed or not
        *    @param value -> Bool that said us if the game is closing or not
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void setClose(bool value);

        static Game * getInstance(){
            if(instance == NULL)
                instance = new Game();

            return instance;
        }


    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor  */
        //////////////////////////////////////////////////////////////////////////
        Game();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will create the RootMapGame
        *    @param option -> new Game or Continue flag
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void createRootMap(MainMenuOption option);

        static Game* instance;          // Instance of game
        Window * window;                // Window object
        OptionManager * options;        // Option Manager
        GameStateChild gameState;       // State of the game
        HeroState * heroState;          // State of the hero
        Notification * notiGamePad;     // Notification of connected game pad
        ShadowManager * shadowManager;  // Shadow shader
        CelShading * celShading;
        Context context;                // OpenGL context
        bool isClosing;                 // Flag to close game
};

#endif // GAME_H
