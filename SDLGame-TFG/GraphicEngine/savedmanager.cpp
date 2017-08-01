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

#include "savedmanager.h"

SavedManager* SavedManager::instance = NULL;

SavedManager::SavedManager()
{
    coins=0;
    currentMap="";
}

//**********************************************************************//

SavedManager::~SavedManager()
{
}

//**********************************************************************//

void SavedManager::load(){
    //Open file
    FILE * fp = fopen("./save/save.json", "rb"); // non-Windows use "r"
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(is);

    currentMap=document["currentMap"].GetString();
    coins=document["coin"].GetFloat();

    fclose(fp);
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

void SavedManager::save(std::string fileMap, int coin){
    currentMap=fileMap;
    coins=coin;
    std::ostringstream stringCoin ;
    stringCoin << coin;

    std::ofstream savedFile;
    savedFile.open ("./save/save.json");
    savedFile << "{ \"currentMap\":\""+fileMap+"\" ,"+
                 +"  \"coin\":"+stringCoin.str()+"}\n";
    savedFile.close();
}
