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

#include "ColladaLoader.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

namespace CaxidyEngine {
	
ColladaLoader::ColladaLoader(std::string file_name)
{
    rapidxml::xml_document<> doc;
	rapidxml::xml_node<> * root_node;
	// Read the xml file into a vector
	std::ifstream file (file_name.c_str());
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("COLLADA");

    SkinLoader skinloader(*root_node->first_node("library_controllers"),10);
    SkinningData skinningData = skinloader.extractSkinData();
    
	SkeletonLoader skeletonloader(*root_node->first_node("library_visual_scenes")->first_node("visual_scene"), skinloader.extractSkinData().joint_order_);
    SkeletonData joints_data =  skeletonloader.get_skeleton();

	GeometryLoader geometry_loader(*root_node->first_node("library_geometries"),skinningData.vertices_skin_data_);
	geometry_loader.read_data();
	geometry_loader.process_data();
    MeshData mesh = geometry_loader.getMesh();

	model_data_= AnimatedModelData(mesh,joints_data);

	AnimationLoader animation_loader;
	animation_data_ = animation_loader.getAnimation(*root_node->first_node("library_animations"),*root_node->first_node("library_visual_scenes"));
}

} // CaxidyEngine
