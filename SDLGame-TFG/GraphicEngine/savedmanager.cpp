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

    currentExp=document["currentExp"].GetInt();
    maxExp=document["maxExp"].GetInt();
    level=document["level"].GetInt();


    const rapidjson::Value & equipFeature=document["equip"];
    for(unsigned currentEquip=0;currentEquip<equipFeature.Size();currentEquip++){
        equip.push_back(new Equipment(equipFeature[currentEquip]));
        equipPosition.push_back(vec2f(equipFeature[currentEquip]["posInv"][0].GetInt(),equipFeature[currentEquip]["posInv"][1].GetInt()));
    }

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

vector<Equipment *> & SavedManager::getInv(){
    return equip;
}

//**********************************************************************//

vector<vec2f> & SavedManager::getPosInv(){
    return equipPosition;
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
    currentMap=fileMap;
    coins=coin;
    std::ostringstream stringCoin ;
    stringCoin << coin;

    std::ofstream savedFile;
    savedFile.open ("./save/save.json");
    savedFile << "{ \"currentMap\":\""+ fileMap +"\" ,"+
                 "  \"coin\":"+ stringCoin.str() +" ,\n";
    savedFile << " \"currentExp\":"<< cExp <<", \n";
    savedFile << " \"maxExp\":"<< MExp <<", \n";
    savedFile << " \"level\":"<< level <<", \n";

    savedFile << "\"equip\": [\n";

    Inventory * inv=gameState.inventoryMenu->getInventory();
    int countItems=0;
    int totalItem=inv->getNumItems();
    Equipment * equip;

    for(int i=0;i<inv->getSizeY() && countItems!=totalItem;i++){
        for(int j=0;j<inv->getSizeX() && countItems!=totalItem;j++){
            equip=inv->getItem(j,i);
            if(equip!=0){
                vec3f position=vec3f(equip->getPosition());

                savedFile << " { \"position\":["<< position.x<<","<<position.y<<","<< position.z<<"],\n" <<
                    "  \"posInv\": ["<< j <<","<< i <<"],\n" <<
                    "  \"type\":"<< equip->getEquipType() <<",\n" <<
                    "  \"name\":\""<< equip->getName() << "\",\n"<<
                    "  \"material\":\""<< equip->getMaterial() <<"\",\n" <<
                    "  \"geometry\":\""<< equip->getMesh() << "\",\n" <<
                    "  \"imgProfile\":\""<< equip->getImageProfile() << "\",\n"<<

                    "  \"damage\":"<< equip->getDamage() << ",\n"<<
                    "  \"life\":"<< equip->getLife() << ",\n"<<
                    "  \"armour\": "<< equip->getArmour() <<" \n }";

                countItems++;
                if(countItems!=totalItem)
                    savedFile<< ",\n";
                else{
                    savedFile<< " \n";
                }
            }
        }
    }

    savedFile << "] \n }\n";

    savedFile.close();
}
