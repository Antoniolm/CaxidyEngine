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

GeometryLoader::GeometryLoader(xml_node<> & geometry_node,const vector<VertexSkinData> & vertex_weights)
{
    meshData = geometry_node.first_node("geometry")->first_node("mesh");
    vertex_weights_ = vertex_weights;

    GLfloat * manual_matrix = new GLfloat[16];

    manual_matrix[0]=0.99999994;  manual_matrix[1]=0.0;          manual_matrix[2]=0.0;           manual_matrix[3]=0.0;   
    manual_matrix[4]=0.0;         manual_matrix[5]=-4.371139e-8; manual_matrix[6]=1.0;           manual_matrix[7]=0.0;
    manual_matrix[8]=0.0;         manual_matrix[9]=-1.0;         manual_matrix[10]=-4.371139e-8; manual_matrix[11]=0.0;
    manual_matrix[12]=0.0;        manual_matrix[13]=0.0;         manual_matrix[14]=0.0;          manual_matrix[15]=1.0;

    current_matrix_.setMatrix(manual_matrix);
}

void GeometryLoader::read_data()
{
    XmlParserUtils xml_parser;

    std::string aux_pos_id = meshData->first_node("vertices")->first_node("input")->first_attribute("source")->value();
    std::string positions_id = aux_pos_id.substr(aux_pos_id.find("#")+1);
    std::cout<< positions_id <<std::endl;
    xml_node<> * positionsData = xml_parser.getChildWithAttribute(meshData, "source", "id", positions_id)->first_node("float_array");

    int count = stoi(positionsData->first_attribute("count")->value());
    std::cout<< count <<std::endl;

    vector<string> pos_data = xml_parser.extract(positionsData->value());
}