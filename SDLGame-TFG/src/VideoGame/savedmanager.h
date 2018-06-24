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

#ifndef SAVEDMANAGER_H
#define SAVEDMANAGER_H

#include "../../lib/rapidjson/document.h"
#include "../../lib/rapidjson/stringbuffer.h"
#include "../../lib/rapidjson/filereadstream.h"
#include <string>
#include <fstream>
#include <sstream>
#include "../GraphicEngine/gamestate.h"
#include "inventory.h"

using namespace rapidjson;

class Equipment;
class SavedManager
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~SavedManager();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will load the current save
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void load(bool forceLoad=false);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the loaded map
        *    \return string
        */
        //////////////////////////////////////////////////////////////////////////
        std::string getMap();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the loaded coins
        *    \return int
        */
        //////////////////////////////////////////////////////////////////////////
        int getCoin();

        vector<Equipment *> & getInv();
        vector<vec2f> & getPosInv();

        int getCurrentExp();
        int getMaxExp();
        int getLevel();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will save the currentMap in the user save
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void save(std::string fileMap,GameState & gameState,int coin,int cExp=0,int MExp =100 ,int level=1);

        static SavedManager * getInstance(){
            if(instance == NULL)
                instance = new SavedManager();

            return instance;
        }
    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        SavedManager();

        static SavedManager* instance;  //Instance of saved manager
        std::string currentMap;         //Current Map of the user progress
        int coins;                      //Current coins of the user progress

        int currentExp;
        int maxExp;
        int level;

        vector<Equipment *> equip;
        vector<vec2f> equipPosition;

        bool wasLoaded; // Variable to know if the current information was loaded
};

#endif // SAVEDMANAGER_H
