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

#ifndef FILE_OBJ_H
#define FILE_OBJ_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <istream>
#include "GL/glew.h"
#include <cstdlib>
#include <math.h>
#include "matrix/structdata.h"

namespace CaxidyEngine {

class FileObj{
    public :
        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will read a obj file and obtain all the vertex
        *    and triangle of them
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void readMesh(const char * fileName, std::vector<vec3f> & vertex,std::vector<GLushort> & triangles);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will read a obj file and obtain all the vertex,triangles
        *    normals,textureCoord of them
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void readEverything(const char * fileName,std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,
                            std::vector<vec3f> & normals,std::vector<vec2f> & textureCord,std::vector<vec3f> & tangent,std::vector<vec3f> & biTangent,
                            bool flagNormal,bool flagOrigin);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will calculate the normals of an object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void calculate_normals(std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,std::vector<vec3f> & normals);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will calculate the origin of an object
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        vec3f calculate_origin(std::vector<vec3f> & vertex);


        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will calculate the bump map of an object
        *    \return vec3f
        */
        //////////////////////////////////////////////////////////////////////////
        void calculate_bump(std::vector<vec3f> & vertex,std::vector<GLushort> & triangles,std::vector<vec2f> & textCoord,std::vector<vec3f> & tangent,std::vector<vec3f> & bitTangent);

        static FileObj * getInstance(){
            if(instance == NULL)
                instance = new FileObj();

            return instance;
        }
    private:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor  */
        //////////////////////////////////////////////////////////////////////////
        FileObj();

        static FileObj* instance;   //Instance of the fileObj

};

} // CaxidyEngine

#endif // FILE_OBJ_H
