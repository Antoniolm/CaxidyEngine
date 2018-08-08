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

namespace CaxidyEngine {

GeometryLoader::GeometryLoader(rapidxml::xml_node<> & geometry_node,const std::vector<VertexSkinData> & vertex_weights)
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
    
    rapidxml::xml_node<> * positionsData = xml_parser.getChildWithAttribute(meshData, "source", "id", positions_id)->first_node("float_array");

    int count = std::stoi(positionsData->first_attribute("count")->value());

    std::vector<std::string> pos_data = xml_parser.extract(positionsData->value());
    for (int i = 0; i < count/3; i++) {
			vec4f position(
                std::stof(pos_data[i * 3]), 
                std::stof(pos_data[i * 3 + 1]), 
                std::stof(pos_data[i * 3 + 2]), 
                1.0f);
            position.transform(current_matrix_.getMatrix());
			vertices.push_back(Vertex(vertices.size(), vec3f(position.x, position.y, position.z), vertex_weights_[vertices.size()]));
	}

    // Read normals
    std::string normals_id = xml_parser.getChildWithAttribute(meshData->first_node("polylist"), "input", "semantic", "NORMAL")->first_attribute("source")->value();
    normals_id = normals_id.substr(normals_id.find("#")+1);

    rapidxml::xml_node<> * normalsData = xml_parser.getChildWithAttribute(meshData,"source", "id", normals_id)->first_node("float_array");
	count = std::stoi(normalsData->first_attribute("count")->value());

    std::vector<std::string> norm_data = xml_parser.extract(normalsData->value());
		for (int i = 0; i < count/3; i++) {
            vec4f normal(
                    std::stof(norm_data[i * 3]), 
                    std::stof(norm_data[i * 3 + 1]), 
                    std::stof(norm_data[i * 3 + 2]), 
                    0.0f);

            normal.transform(current_matrix_.getMatrix());    
			normals.push_back(vec3f(normal.x, normal.y, normal.z));
		}

    // Read texture coords
    std::string text_id = xml_parser.getChildWithAttribute(meshData->first_node("polylist"), "input", "semantic", "TEXCOORD")->first_attribute("source")->value();
    text_id = text_id.substr(text_id.find("#")+1);

    rapidxml::xml_node<> * texCoordsData = xml_parser.getChildWithAttribute(meshData,"source", "id", text_id)->first_node("float_array");
    count = std::stoi(texCoordsData->first_attribute("count")->value());

    std::vector<std::string> tex_data = xml_parser.extract(texCoordsData->value());
    for (int i = 0; i < count/2; i++) {
    	textures.push_back(vec2f(
            std::stof(tex_data[i * 2]),
            std::stof(tex_data[i * 2 + 1])));
    }
}

void GeometryLoader::process_data(){ 
    rapidxml::xml_node<> * poly = meshData->first_node("polylist");

    std::vector<std::string> index_data = xml_parser.extract(poly->first_node("p")->value());

    for(int i=0;i<index_data.size()/4;i++){
        int positionIndex = std::stoi(index_data[i * 4]);
        int normalIndex = std::stoi(index_data[i * 4 + 1]);
        int texCoordIndex = std::stoi(index_data[i * 4 + 2]);

        Vertex current_vertex = vertices[positionIndex];
        if(!current_vertex.is_set()){
            current_vertex.texture_index_=texCoordIndex;
            current_vertex.normal_index_=normalIndex;
            indices_array_.push_back(positionIndex);
        }
    }
   
    for (int i = 0; i < vertices.size(); i++) {
        vertices_array_.push_back(vertices[i].position_.x);
        vertices_array_.push_back(vertices[i].position_.y);
        vertices_array_.push_back(vertices[i].position_.z);

        textures_array_.push_back(textures[vertices[i].texture_index_].x);
        textures_array_.push_back( 1 - textures[vertices[i].texture_index_].y);
        
        normals_array_.push_back(normals[vertices[i].normal_index_].x);
        normals_array_.push_back(normals[vertices[i].normal_index_].y);
        normals_array_.push_back(normals[vertices[i].normal_index_].z);

        VertexSkinData weights = vertices[i].weights_data_;

        jointIds_array_.push_back(weights.joint_ids[0]);
        jointIds_array_.push_back(weights.joint_ids[1]);
        jointIds_array_.push_back(weights.joint_ids[2]);

        weights_array_.push_back(weights.weights[0]);
        weights_array_.push_back(weights.weights[1]);
        weights_array_.push_back(weights.weights[2]);
    }

}

MeshData GeometryLoader::getMesh()
{
    return MeshData(vertices_array_, textures_array_, normals_array_, indices_array_, jointIds_array_, weights_array_);
}

} // CaxidyEngine