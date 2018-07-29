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

#include "savedmanager.h"

SavedManager* SavedManager::instance = NULL;

SavedManager::SavedManager()
{
    coins=0;
    currentMap="";
    wasLoaded=false;
}

//**********************************************************************//

SavedManager::~SavedManager()
{
}

//**********************************************************************//

void SavedManager::load(bool forceLoad){
    if(!wasLoaded || forceLoad){
        wasLoaded=true;

        //Open file
        FILE * fp = fopen("resources/save/save.json", "rb"); // non-Windows use "r"
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        rapidjson::Document document;
        document.ParseStream(is);

        currentMap=document["currentMap"].GetString();
        coins=document["coin"].GetFloat();

        currentExp=document["currentExp"].GetInt();
        maxExp=document["maxExp"].GetInt();
        level=document["level"].GetInt();

        fclose(fp);
    }
}

//**********************************************************************//

std::string SavedManager::getMap(){
    return currentMap;
}

//**********************************************************************//

int SavedManager::getCoin(){
    return coins;
}

//**********************************************************************//

int SavedManager::getCurrentExp(){
    return currentExp;
}

//**********************************************************************//
int SavedManager::getMaxExp(){
    return maxExp;
}

//**********************************************************************//

int SavedManager::getLevel(){
    return level;
}

//**********************************************************************//

void SavedManager::save(std::string fileMap,GameState & gameState, int coin,int cExp,int MExp,int level){

    wasLoaded=false;
    currentMap=fileMap;

    coins=coin;
    std::ostringstream stringCoin ;
    stringCoin << coin;

    std::ofstream savedFile;
    savedFile.open ("resources/save/save.json");
    savedFile << "{ \"currentMap\":\""+ fileMap +"\" ,"+
                 "  \"coin\":"+ stringCoin.str() +" ,\n";
    savedFile << " \"currentExp\":"<< cExp <<", \n";
    savedFile << " \"maxExp\":"<< MExp <<", \n";
    savedFile << " \"level\":"<< level <<", \n";

    savedFile << "\"equip\": [\n";

    savedFile << "] \n }\n";

    savedFile.close();
}
