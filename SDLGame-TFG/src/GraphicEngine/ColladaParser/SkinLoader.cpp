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

SkinLoader::SkinLoader(xml_node<> &library_controllers_node):
	skinning_data_()
{
    xml_node<> * skin_node = library_controllers_node.first_node("controller")->first_node("skin");

	///////////////
	// JoinList
	//////////////
    xml_node<> * input_node = skin_node->first_node("vertex_weights");
	string jointId= utils::getChildWithAttribute(input_node, "input", "semantic", "JOINT")->first_attribute("source")->value();
	jointId = jointId.substr(jointId.find("#")+1);
    std::cout<< "Joint:" << jointId << std::endl;

	xml_node<> * joints_node = utils::getChildWithAttribute(skin_node, "source", "id", jointId)->first_node("Name_array");

	cout << joints_node->value() << endl;

	vector<string> jointsList = utils::extract(joints_node->value());

	///////////////
	// Weights
	//////////////
	string weightsDataId= utils::getChildWithAttribute(input_node, "input", "semantic", "WEIGHT")->first_attribute("source")->value();
	weightsDataId = weightsDataId.substr(weightsDataId.find("#")+1);
    std::cout<< "Joint:" << weightsDataId << std::endl;

	xml_node<> * weights_node = utils::getChildWithAttribute(skin_node, "source", "id", weightsDataId)->first_node("float_array");

	cout << weights_node->value() << endl;

	vector<string> weights = utils::extract(weights_node->value());
	vector<float> weights_list;

	for(int i=0;i < weights.size();i++)
		weights_list.push_back(stof(weights[i]));
	
	///////////////
	// Effective joints
	//////////////
	vector<string> vcountList = utils::extract(input_node->first_node("vcount")->value());
	vector<int> vcounts;

	for (int i = 0; i < vcountList.size(); i++) {
		vcounts.push_back(stoi(vcountList[i]));
	}

	///////////////
	// Create skin_data
	//////////////
	vector<string> vList = utils::extract(input_node->first_node("v")->value());
	vector<VertexSkinData> skinningData;

	int pointer = 0;
	VertexSkinData skinData;
	int joint_id, weight_id;
	for(int i=0; i < vcounts.size(); i++){
		skinData = VertexSkinData();
		for (int j = 0; j < vcounts[i]; j++) {
				joint_id = stoi(vList[pointer++]);
				weight_id = stoi(vList[pointer++]);
				skinData.addJoint(joint_id, weights_list[weight_id]);
		}
		skinningData.push_back(skinData);
	}

	skinning_data_.joint_order_ = jointsList;
	skinning_data_.vertices_skin_data_ = skinningData;
}

//**********************************************************************//

SkinningData & SkinLoader::extractSkinData()
{
	return skinning_data_;
}
