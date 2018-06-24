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


#ifndef OBJECTGROUP_H
#define OBJECTGROUP_H

#include "../collection/materialcollection.h"
#include "../nodescenegraph.h"
#include "../collection/meshcollection.h"

class ObjectGroup : public Object3D
{
    public:
        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        ObjectGroup(MaterialIndex materialIndex);

        //////////////////////////////////////////////////////////////////////////
        /** Destructor */
        //////////////////////////////////////////////////////////////////////////
        virtual ~ObjectGroup();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will add another object to our group of object
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void addObject(vec3f position,MeshIndex meshIndex);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    It will init our group of object( init his mesh)
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void init();

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will show the object in our interface
        *    @param cv -> the context of our visualization
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void visualization(Context & vis);

        //////////////////////////////////////////////////////////////////////////
        /**
        *    The method will update the state of the object. That change need the
        *    current time in our application
        *    @param gameState -> the current state of our game
        *    \return void
        */
        //////////////////////////////////////////////////////////////////////////
        void updateState(GameState & gameState);

         //////////////////////////////////////////////////////////////////////////
        /**
        *    It will return the mesh of our group
        *    \return mesh *
        */
        //////////////////////////////////////////////////////////////////////////
        Mesh * getMesh();
    protected:

    private:
        vector<vec3f> vertex;       // Vector of vertex
        vector<GLushort> triangles; // Vector of triangles
        vector<vec3f> normals;      // Vector of normals
        vector<vec2f> textureCord;  // Vector of coordinate texture
        vector<vec3f> tangent;      // Vector of tangents
        vector<vec3f> biTangent;    // Vector of bitangents
        NodeSceneGraph * root;      // Root of the group of objects
        Mesh * mesh;                // Mesh of the group of objects
};

#endif // OBJECTGROUP_H
