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

#include "SkinLoader.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "XmlParserUtils.cxx"

SkinLoader::SkinLoader()
{
    xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream file ("resources/geometries/model.dae");
	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("COLLADA");
    cout<< "test"<<endl;

    xml_node<> * skin_node = root_node->first_node("library_controllers")->first_node("controller")->first_node("skin");

    xml_node<> * input_node = skin_node->first_node("vertex_weights");
    std::cout<< "Joint:" << utils::getChildWithAttribute(input_node, "input", "semantic", "JOINT")->first_attribute("source")->value() << std::endl;

    cout<< "testEnd"<<endl;
}

//**********************************************************************//

SkinningData SkinLoader::extractSkinData()
{

}
