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

#include "mesh.h"

Mesh::Mesh()
{
    //ctor
}

//**********************************************************************//

Mesh::Mesh(const string & aFile,bool save){
    objFile=aFile;
    numIndex=0;
    saveInfo=save;
    init();
}

//**********************************************************************//

Mesh::Mesh(const vector<vec3f> & vertex, const vector<GLushort> & triangles,const vector<vec3f> & normals,const vector<vec2f> & textureCord,
           const vector<vec3f> & tangent,const vector<vec3f> & biTangent,bool save){
    init(vertex,triangles,normals,textureCord,tangent,biTangent);
}

//**********************************************************************//

Mesh::~Mesh()
{
    glDeleteBuffers(1,&vertexArrayObject);
    glDeleteBuffers(1,&vertexArrayBuffers[POSITION_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[NORMAL_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[TEXCOORD_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[INDEX_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[TANGENT_VB]);
    glDeleteBuffers(1,&vertexArrayBuffers[BITANGENT_VB]);
}

//**********************************************************************//

void Mesh::init(){
    vector<GLushort> aTriangles;
    vector<vec3f> aVertex;
    vector<vec3f> aNormals;
    vector<vec2f> aTextureCord;
    vector<vec3f> aTangent;
    vector<vec3f> aBiTangent;

    FileObj * obj=FileObj::getInstance();
    obj->readEverything(objFile.c_str(),aVertex,aTriangles,aNormals,aTextureCord,aTangent,aBiTangent,true,true);
    generateBoundingBox(aVertex);

    numIndex=aTriangles.size();

    loadMesh(aVertex,aTriangles,aNormals,aTextureCord,aTangent,aBiTangent);

    if(saveInfo){
        vertex=aVertex;
        triangles=aTriangles;
        normals=aNormals;
        textureCord=aTextureCord;
        tangent=aTangent;
        bitTangent=aBiTangent;
    }
}

//**********************************************************************//

void Mesh::init(const vector<vec3f> & aVertex, const vector<GLushort> & aTriangles,const vector<vec3f> & aNormals,const vector<vec2f> & aTextureCord
                ,const vector<vec3f> & aTangent,const vector<vec3f> & aBiTangent){
    generateBoundingBox(aVertex);
    numIndex=aTriangles.size();

    loadMesh(aVertex,aTriangles,aNormals,aTextureCord,aTangent,aBiTangent);

    if(saveInfo){
        vertex=aVertex;
        triangles=aTriangles;
        normals=aNormals;
        textureCord=aTextureCord;
        tangent=aTangent;
        bitTangent=aBiTangent;
    }
}

//**********************************************************************//

void Mesh::visualization(Context & vis){
    //Draw our object
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES,numIndex,GL_UNSIGNED_SHORT,0);
    glBindVertexArray(0);
}

//**********************************************************************//

void Mesh::updateState(GameState & gameState){
}

//**********************************************************************//

BoundingBox Mesh::getBoundingBox(){
    return boundingBox;
}

//**********************************************************************//

vector<vec3f> & Mesh::getVertex(){
    return vertex;
}

//**********************************************************************//

vector<GLushort> & Mesh::getTriangles(){
    return triangles;
}

//**********************************************************************//

vector<vec3f> & Mesh::getNormals(){
    return normals;
}

//**********************************************************************//

vector<vec2f> & Mesh::getTextCoord(){
    return textureCord;
}

//**********************************************************************//

vector<vec3f> & Mesh::getTangent(){
    return tangent;
}

//**********************************************************************//

vector<vec3f> & Mesh::getBitTangent(){
    return bitTangent;
}

//**********************************************************************//

void Mesh::generateBoundingBox(const vector<vec3f> & vertex){
    float maxX,maxY,maxZ,minX,minY,minZ;
    maxX=vertex[0].x;  maxY=vertex[0].y;  maxZ=vertex[0].z;
    minX=vertex[0].x;  minY=vertex[0].y;  minZ=vertex[0].z;
    int tam=vertex.size();

    for(int i=1;i<tam;i++){
        if(vertex[i].x >maxX) maxX=vertex[i].x;
        if(vertex[i].y >maxY) maxY=vertex[i].y;
        if(vertex[i].z >maxZ) maxZ=vertex[i].z;

        if(vertex[i].x < minX) minX=vertex[i].x;
        if(vertex[i].y < minY) minY=vertex[i].y;
        if(vertex[i].z < minZ) minZ=vertex[i].z;
	}

	boundingBox.maxValue=vec3f(maxX,maxY,maxZ);
	boundingBox.minValue=vec3f(minX,minY,minZ);
}

//**********************************************************************//

void Mesh::loadMesh(const vector<vec3f> & vertex, const vector<GLushort> & triangles,const vector<vec3f> & normals,const vector<vec2f> & textureCord
                    ,const vector<vec3f> & tangent,const vector<vec3f> & bitTangent){
    glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	//Vertex buffer
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER,vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vec3f)*vertex.size(),&vertex[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0 , 0);

    //Normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec3f)* normals.size(), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //Texture Coord buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vec2f) * textureCord.size(), &textureCord[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    //Tangent buffer
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER,vertexArrayBuffers[TANGENT_VB]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vec3f)*tangent.size(),&tangent[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0 , 0);

    //Bitangent buffer
    glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER,vertexArrayBuffers[BITANGENT_VB]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vec3f)*bitTangent.size(),&bitTangent[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0 , 0);

    //Triangles buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(GLushort)*triangles.size(),&triangles[0],GL_STATIC_DRAW);

    glBindVertexArray(0);
}

