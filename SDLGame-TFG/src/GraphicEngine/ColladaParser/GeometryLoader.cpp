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

#include "GeometryLoader.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

GeometryLoader::GeometryLoader(xml_node<> & geometry_node,const vector<VertexSkinData> & vertex_weights)
{
    meshData = geometry_node.first_node("geometry")->first_node("mesh");
    vertex_weights_ = vertex_weights;

    current_matrix_.change_axis();
}

void GeometryLoader::read_data()
{
    XmlParserUtils xml_parser;

    // Read positions
    std::string aux_pos_id = meshData->first_node("vertices")->first_node("input")->first_attribute("source")->value();
    std::string positions_id = aux_pos_id.substr(aux_pos_id.find("#")+1);
    std::cout<< positions_id <<std::endl;
    xml_node<> * positionsData = xml_parser.getChildWithAttribute(meshData, "source", "id", positions_id)->first_node("float_array");

    int count = stoi(positionsData->first_attribute("count")->value());
    std::cout<< count <<std::endl;

    vector<string> pos_data = xml_parser.extract(positionsData->value());
    for (int i = 0; i < count/3; i++) {
			vec4f position(
                stof(pos_data[i * 3]), 
                stof(pos_data[i * 3 + 1]), 
                stof(pos_data[i * 3 + 2]), 
                1.0f);
            position.transform(current_matrix_.getMatrix());
			vertices.push_back(Vertex(vertices.size(), vec3f(position.x, position.y, position.z), vertex_weights_[vertices.size()]));
	}

    // Read normals
}