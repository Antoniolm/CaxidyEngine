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

#include "voxel.h"

namespace CaxidyEngine {

Voxel::Voxel()
{
    //ctor
}

Voxel::Voxel(const rapidjson::Value & voxelFeature,vec3f posVoxel, std::string material){
    MeshCollection * meshCollect= MeshCollection::getInstance();
    MaterialCollection * materialCollect= MaterialCollection::getInstance();

    Matrix4f * transObj=new Matrix4f();
    transObj->translation(posVoxel.x,posVoxel.y,posVoxel.z);

    NodeSceneGraph *objNode=new NodeSceneGraph();
    objNode->add(transObj);
    objNode->add(materialCollect->getMaterial(material));

    objNode->add(meshCollect->getMesh(voxelFeature["mesh"].GetString()));
    object=objNode;
    damage=voxelFeature["damage"].GetFloat();
}

//**********************************************************************//

Voxel::~Voxel()
{
    //dtor
}

} // CaxidyEngine
