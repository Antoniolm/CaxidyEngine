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

#include "voxelgroup.h"

namespace CaxidyEngine {

VoxelGroup::VoxelGroup()
{
    //ctor
}

//**********************************************************************//

VoxelGroup::VoxelGroup(const rapidjson::Value & voxelGFeature, std::vector<ObjectScene *> & objs){
    //For each group
    int tamX=voxelGFeature["XNumber"].GetInt();
    int tamY=voxelGFeature["YNumber"].GetInt();
    int tamZ=voxelGFeature["ZNumber"].GetInt();
    int initialX=voxelGFeature["position"][0].GetFloat();
    float initialY=voxelGFeature["position"][1].GetFloat();
    int initialZ=-voxelGFeature["position"][2].GetFloat();
    std::string material;

    for(int x=0;x<tamX;x++){
        for(int z=0;z<tamZ;z++){
            for(int y=0;y<tamY;y++){

                if(y==0) material=voxelGFeature["materialTop"].GetString();
                else material=voxelGFeature["materialMiddle"].GetString();

                objs.push_back(new Voxel(voxelGFeature,vec3f(initialX+x+0.5f,initialY-y,initialZ-z-0.5f),material));

            }
        }
    }
}

//**********************************************************************//

VoxelGroup::~VoxelGroup()
{
    //dtor
}

} // CaxidyEngine 
