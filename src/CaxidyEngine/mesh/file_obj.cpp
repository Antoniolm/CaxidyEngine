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

#include "file_obj.h"

namespace CaxidyEngine {
    
FileObj* FileObj::instance = NULL;

//**********************************************************************//

FileObj::FileObj(){
    delete instance;
}

//**********************************************************************//

void FileObj::readMesh(const char * fileName,std::vector<vec3f> & vertex,std::vector<GLushort> & triangles){
    int value;
    float x,y,z;
    std::string aux;
    std::istringstream * stream;
    std::ifstream in(fileName, std::ios::in);
    if (!in)
    {
        std::cout<< "Cannot open " << fileName << std::endl;
    }

    std::string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v ") { //Extract vertex
            stream=new std::istringstream(line.substr(2));
            (*stream) >> x;
            (*stream) >> y;
            (*stream) >> z;
            vertex.push_back(vec3f(x,y,z));
        }
        else if (line.substr(0,2) == "f "){ //Extract face
            stream=new std::istringstream(line.substr(2));
            for(int i=0;i<3;i++){
                (*stream) >> value;
                triangles.push_back((GLushort)--value);
                (*stream) >> aux;
            }
        }
    }

}

//**********************************************************************//

void FileObj::readEverything(const char * fileName,std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,std::vector<vec3f> & normals
                             ,std::vector<vec2f> & textureCord,std::vector<vec3f> & tangent,std::vector<vec3f> & biTangent,bool flagNormal,bool flagOrigin){
    int value;
    char charValue;
    float x,y,z;
    std::istringstream * stream;
    std::vector<vec3f> vertexAux;
    std::vector<vec3f> normalsVertex;
    std::vector<vec2f> textureVertex;
    std::vector<GLushort> trianglesIndex;
    std::vector<int> normalFaces;
    std::vector<int> textureFaces;
    std::ifstream in(fileName, std::ios::in);
    if (!in)
    {
        std::cout<< "Cannot open " << fileName << std::endl;
    }
    else{
        std::cout<< "Geometry ->"<< fileName<< std::endl;
    }

    std::string line;
    while (getline(in, line))
    {
        if (line.substr(0,2) == "v "){ //Extract vertex
            stream=new std::istringstream(line.substr(2));
            (*stream) >> x;
            (*stream) >> y;
            (*stream) >> z;
            vertexAux.push_back(vec3f(x,y,z));
        }
        else if (line.substr(0,3) == "vn "){ //Extract normal face
            stream=new std::istringstream(line.substr(3));
            (*stream) >> x;
            (*stream) >> y;
            (*stream) >> z;
            normalsVertex.push_back(vec3f(x,y,z));

        }
        else if (line.substr(0,3) == "vt "){ //Extract texture Coord
            stream=new std::istringstream(line.substr(3));
            (*stream) >> x;
            (*stream) >> y;
            textureVertex.push_back(vec2f(x,y));

        }
        else if (line.substr(0,2) == "f "){
            stream=new std::istringstream(line.substr(2));
            for(int i=0;i<3;i++){
                //Extract the triangle face
                (*stream) >> value;
                trianglesIndex.push_back(--value);

                //Extract the texture face
                (*stream) >> charValue; //Extract the char between element
                (*stream) >> value;
                textureFaces.push_back(--value);

                //Extract the normals face
                (*stream) >> charValue; //Extract the char between element
                (*stream) >> value;
                normalFaces.push_back(--value);
            }
        }

    }
    if(flagOrigin){
        vec3f origin=calculate_origin(vertexAux);
        for(unsigned i=0;i< vertexAux.size();i++){
            vertexAux[i]=vertexAux[i]-origin;

        }

    }
    std::vector<vec3f> normalAux;
    if(flagNormal)
        calculate_normals(vertexAux,trianglesIndex,normalAux);

    for(unsigned i=0;i<trianglesIndex.size();i++){
        vertex.push_back(vertexAux[trianglesIndex[i]]);

        if(flagNormal)
            normals.push_back(normalAux[trianglesIndex[i]]);
        else
            normals.push_back(normalsVertex[normalFaces[i]]);

        textureCord.push_back(textureVertex[textureFaces[i]]);
        triangles.push_back(i);
    }
    calculate_bump(vertex,triangles,textureCord,tangent,biTangent);
}

//**********************************************************************//

void FileObj::calculate_normals(std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,std::vector<vec3f> & normals){
    //Calculate face normals
    vec3f v1,v2,normalFace;

	for(unsigned i=0;i<vertex.size();i++){
		normals.push_back(vec3f(0.0,0.0,0.0));
	}

	for(unsigned i=0;i<triangles.size();i=i+3){
        int i0 = triangles[i];
        int i1 = triangles[i + 1];
        int i2 = triangles[i + 2];

		v1=vertex[i1]-vertex[i0];
		v2=vertex[i2]-vertex[i0];

		normalFace=v1.cross(v2);

		normalFace.normalize();

        normals[i0]=normals[i0] + normalFace;
        normals[i1]=normals[i1] + normalFace;
        normals[i2]=normals[i2] + normalFace;
	}

    for(unsigned k=0;k<vertex.size();k++){
        normals[k].normalize();
	}

}

//**********************************************************************//

vec3f FileObj::calculate_origin(std::vector<vec3f> & vertex){
    float maxX,maxY,maxZ,minX,minY,minZ;
    maxX=vertex[0].x;  maxY=vertex[0].y;  maxZ=vertex[0].z;
    minX=vertex[0].x;  minY=vertex[0].y;  minZ=vertex[0].z;

    for(unsigned i=1;i<vertex.size();i++){
        if(vertex[i].x >maxX) maxX=vertex[i].x;
        if(vertex[i].y >maxY) maxY=vertex[i].y;
        if(vertex[i].z >maxZ) maxZ=vertex[i].z;

        if(vertex[i].x < minX) minX=vertex[i].x;
        if(vertex[i].y < minY) minY=vertex[i].y;
        if(vertex[i].z < minZ) minZ=vertex[i].z;
	}

    vec3f result;
    result.x = minX+((maxX-minX)/2.0);
    result.y = minY+((maxY-minY)/2.0);
    result.z = minZ+((maxZ-minZ)/2.0);

    return result;
}

//**********************************************************************//

void FileObj::calculate_bump(std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,
                             std::vector<vec2f> & textCoord,std::vector<vec3f> & tangent,std::vector<vec3f> & bitTangent){
    //Calculate edges and UV
    vec3f edge1,edge2;
    vec2f deltaUV1,deltaUV2;
    vec3f tangentEle,bitTangentEle;
    vec3f triangle;

    for(unsigned i=0;i<triangles.size();i=i+3){
        triangle.x = triangles[i];
        triangle.y = triangles[i + 1];
        triangle.z = triangles[i + 2];

        edge1=vertex[triangle.y]-vertex[triangle.x];
        edge2=vertex[triangle.z]-vertex[triangle.x];

        deltaUV1=textCoord[triangle.y]-textCoord[triangle.x];
        deltaUV2=textCoord[triangle.z]-textCoord[triangle.x];


        GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

        tangentEle.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
        tangentEle.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
        tangentEle.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
        tangentEle.normalize();
        tangent.push_back(tangentEle);
        tangent.push_back(tangentEle);
        tangent.push_back(tangentEle);

        bitTangentEle.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
        bitTangentEle.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
        bitTangentEle.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
        bitTangentEle.normalize();
        bitTangent.push_back(bitTangentEle);
        bitTangent.push_back(bitTangentEle);
        bitTangent.push_back(bitTangentEle);
	}
}

} // CaxidyEngine
