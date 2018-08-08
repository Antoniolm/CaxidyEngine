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

#include "optionmanager.h"

OptionManager* OptionManager::instance = NULL;

OptionManager::OptionManager()
{
    //ctor
}

//**********************************************************************//

OptionManager::~OptionManager()
{
    //dtor
}

//**********************************************************************//

void OptionManager::load(){

    //Open file
    FILE * fp = fopen("resources/option/options.json", "rb");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    rapidjson::Document document;
    document.ParseStream(is);

    //Obtain information
    resolution.first=document["resolWidth"].GetFloat();
    resolution.second=document["resolHeight"].GetFloat();
    window=document["window"].GetBool();
    volume=document["volume"].GetFloat();

    fclose(fp);
}

//**********************************************************************//

std::pair<int,int> OptionManager::getResolution(){
    return resolution;
}
//**********************************************************************//

bool OptionManager::getWindow(){
    return window;
}

//**********************************************************************//

int OptionManager::getVolume(){
    return volume;
}

//**********************************************************************//

void OptionManager::save(std::pair<int,int>aResolution,bool wind,int aVolume){

    //Resolution transformation
    std::ostringstream stringWidth ;
    stringWidth << aResolution.first;

    std::ostringstream stringHeight ;
    stringHeight << aResolution.second;

    //Window transformation
    std::string stringWindow="false";
    if(wind)
        stringWindow="true";

    //Volume Transformation
    std::ostringstream stringVolume;
    stringVolume << aVolume;

    //Save information in the file
    std::ofstream savedFile;
    savedFile.open ("resources/option/options.json");
    savedFile << "{ \"resolWidth\":"+stringWidth.str()+","+
                 +" \"resolHeight\":"+stringHeight.str()+","+
                 +" \"window\":"+stringWindow+","+
                 +" \"volume\":"+stringVolume.str()+"}\n";
    savedFile.close();
}

