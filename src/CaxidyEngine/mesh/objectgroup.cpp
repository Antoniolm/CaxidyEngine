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


#include "objectgroup.h"

namespace CaxidyEngine {
    
ObjectGroup::ObjectGroup(MaterialIndex materialIndex){
    MaterialCollection *materialCollect=MaterialCollection::getInstance();
    root=new NodeSceneGraph();
    root->add(materialCollect->getMaterial(materialIndex));

}

//**********************************************************************//

ObjectGroup::~ObjectGroup()
{
    delete root;
}

//**********************************************************************//

void ObjectGroup::addObject(vec3f position,MeshIndex meshIndex){
    std::vector<vec3f> currentVertex;
    std::vector<GLushort> currentTriangles;
    std::vector<vec3f> currentNormals;
    std::vector<vec2f> currentTextureCord;
    std::vector<vec3f> currentTangent;
    std::vector<vec3f> currentBitTangent;
    MeshCollection * meshCollect =MeshCollection::getInstance();
    Mesh * mesh=meshCollect->getMesh(meshIndex);

    currentVertex=mesh->getVertex();
    currentTriangles=mesh->getTriangles();
    currentNormals=mesh->getNormals();
    currentTextureCord=mesh->getTextCoord();
    currentTangent=mesh->getTangent();
    currentBitTangent=mesh->getBitTangent();

    int shift=triangles.size();
    for(unsigned i=0;i<currentTriangles.size();i++){
        vertex.push_back(vec3f(currentVertex[i].x+position.x,currentVertex[i].y+position.y,currentVertex[i].z+position.z));
        normals.push_back(currentNormals[i]);
        textureCord.push_back(currentTextureCord[i]);
        triangles.push_back(currentTriangles[i]+shift);
        tangent.push_back(currentTangent[i]);
        biTangent.push_back(currentBitTangent[i]);
    }
}

//**********************************************************************//

void ObjectGroup::init(){
    if(!vertex.empty()){
        mesh=new Mesh(vertex,triangles,normals,textureCord,tangent,biTangent);
        root->add(mesh);

        vertex.clear();
        normals.clear();
        textureCord.clear();
        triangles.clear();
        tangent.clear();
        biTangent.clear();
    }
}

//**********************************************************************//

void ObjectGroup::visualization(Context & vis){
    //Draw our objects
    if(!vis.celShading_mode)
        root->visualization(vis);    
}

//**********************************************************************//

void ObjectGroup::updateState(GameState & gameState){
}

//**********************************************************************//

Mesh * ObjectGroup::getMesh(){
    return mesh;
}

} // CaxidyEngine
