// *********************************************************************
// **
// ** Copyright (C) 2016-2018 Antonio David L�pez Machado
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

#ifndef GEOMETRYLOADER_H
#define GEOMETRYLOADER_H

#include "matrix/matrix4f.h"
#include <string>
#include "ColladaData.h"
#include "rapidxml/rapidxml.hpp"

#include "XmlParserUtils.h"

using namespace rapidxml;
using namespace std;

class GeometryLoader
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        GeometryLoader(xml_node<> & geometry_node,const vector<VertexSkinData> & vertex_weights);

    protected:

    private:
        xml_node<> *  meshData;

        Matrix4f current_matrix; // Matrix 4x4
        XmlParserUtils xml_parser;

        vector<VertexSkinData> vertexWeights;
        
        vector<float> verticesArray;
        vector<float> normalsArray;
        vector<float> texturesArray;
        vector<int> indicesArray;
        vector<int> jointIdsArray;
        vector<float> weightsArray;

        vector<Vertex> vertices;
        vector<vec2f> textures;
        vector<vec3f> normals;
        vector<int> indices;
        
};

#endif // GEOMETRYLOADER_H