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

namespace CaxidyEngine {

class GeometryLoader
{
    public:

        //////////////////////////////////////////////////////////////////////////
        /** Constructor */
        //////////////////////////////////////////////////////////////////////////
        GeometryLoader(rapidxml::xml_node<> & geometry_node,const std::vector<VertexSkinData> & vertex_weights);

        void read_data();

        void process_data();

        MeshData getMesh();

    protected:

    private:
        rapidxml::xml_node<> *  meshData;

        Matrix4f current_matrix_; // Matrix 4x4
        XmlParserUtils xml_parser;

        std::vector<VertexSkinData> vertex_weights_;
        
        std::vector<float> vertices_array_;
        std::vector<float> normals_array_;
        std::vector<float> textures_array_;
        std::vector<int> indices_array_;
        std::vector<int> jointIds_array_;
        std::vector<float> weights_array_;

        std::vector<Vertex> vertices;
        std::vector<vec2f> textures;
        std::vector<vec3f> normals;
};

} // CaxidyEngine

#endif // GEOMETRYLOADER_H