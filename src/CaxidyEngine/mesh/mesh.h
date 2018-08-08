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

#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include "context/context.h"
#include "CaxidyEngine/object3d.h"
#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"
#include <GL/glu.h>
#include <GL/gl.h>
#include <fstream>
#include "matrix/matrix4f.h"
#include <iostream>
#include "matrix/structdata.h"
#include "CaxidyEngine/rootmap.h"
#include "context/shader.h"
#include "file_obj.h"

using namespace std;

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB,
	TANGENT_VB,
	BITANGENT_VB
};

class Mesh : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        Mesh();

        //////////////////////////////////////////////////////////////////////////
        /**  Constructor */
        /////////////////////////////////////////////////////////////////////////
        Mesh(const string & aFile,bool save=false);

        //////////////////////////////////////////////////////////////////////////
        /**  Constructor */
        /////////////////////////////////////////////////////////////////////////
        Mesh(const vector<vec3f> & vertex, const vector<GLushort> & triangles,const vector<vec3f> & normals
             ,const vector<vec2f> & textureCord,const vector<vec3f> & tangent,const vector<vec3f> & biTangent,bool save=false);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~Mesh();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will obtain the boundingBox of the object.
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        BoundingBox getBoundingBox();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the vertex of the object.
        *    \return vector<vec3f> &
        */
        //////////////////////////////////////////////////////////////////////////
        vector<vec3f> & getVertex();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the triangles of the object
        *    \return vector<GLushort> &
        */
        //////////////////////////////////////////////////////////////////////////
        vector<GLushort> & getTriangles();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the normals of the object
        *    \return vector<vec3f> &
        */
        //////////////////////////////////////////////////////////////////////////
        vector<vec3f> & getNormals();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the texture coordinates of the object
        *    \return vector<vec2f> &
        */
        //////////////////////////////////////////////////////////////////////////
        vector<vec2f> & getTextCoord();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the tangent of the object
        *    \return vector<vec3f> &
        */
        //////////////////////////////////////////////////////////////////////////
        vector<vec3f> & getTangent();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will obtain the biTangent of the object
        *    \return vector<vec3f> &
        */
        //////////////////////////////////////////////////////////////////////////
        vector<vec3f> & getBitTangent();


    protected:

    private:
        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will initialize the information for the visualization
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void init();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will initialize the information for the visualization
        *    \return void
        */
        /////////////////////////////////////////////////////////////////////////
        void init(const vector<vec3f> & vertex, const vector<GLushort> & triangles,const vector<vec3f> & normals,const vector<vec2f> & textureCord
                ,const vector<vec3f> & tangent,const vector<vec3f> & biTangent);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will load our current mesh
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void loadMesh(const vector<vec3f> & vertex, const vector<GLushort> & triangles,const vector<vec3f> & normals,const vector<vec2f> & textureCord,
                      const vector<vec3f> & tangent=vector<vec3f>(),const vector<vec3f> & bitTangent=vector<vec3f>());

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will generate the boundingbox of our mesh
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void generateBoundingBox(const vector<vec3f> & vertex);

        static const unsigned int NUM_BUFFERS = 6; // Number of buffers
        GLuint vertexArrayBuffers[NUM_BUFFERS];    // Vertex Array buffer
        GLuint vertexArrayObject;                  // Vertex Array Object
        string objFile;                            // File with the model 3D
        int numIndex;                              // number of index
        bool saveInfo;                             // Flag to save or not the info of its model
        vector<vec3f> vertex;                      // Vector of vertex
        vector<GLushort> triangles;                // Vector of triangles
        vector<vec3f> normals;                     // Vector of normals
        vector<vec2f> textureCord;                 // Vector of coordinate of texture
        vector<vec3f> bitTangent;                  // Vector of bitangent
        vector<vec3f> tangent;                     // Vector of tangent
};

#endif // MESH_H
