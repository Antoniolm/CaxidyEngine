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

#include "SkeletonLoader.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

SkeletonLoader::SkeletonLoader(xml_node<> & visual_scene_node, const vector<string> & joint_orders)
{
    joint_orders_ = joint_orders;

    current_matrix.change_axis();

    xml_node<> * armature_data = xml_parser.getChildWithAttribute(&visual_scene_node, "node", "id", "Armature");
    
    xml_node<> * head_node = armature_data->first_node("node");

    joint_ = *load_joint_data(head_node,true);
    skeleton_data_ = new SkeletonData(2,joint_);
}

JointData * SkeletonLoader::load_joint_data(xml_node<> * node, bool root)
{
    string name =node->first_attribute("id")->value();
    int id = xml_parser.indexOf(joint_orders_, name);
    Matrix4f matrix(xml_parser.extract(node->first_node("matrix")->value()));

    if(root){
		current_matrix.product(matrix.getMatrix());
	}
    else {
        current_matrix.setMatrix(matrix.getMatrix());
    }

    JointData * joint = new JointData(id,name,current_matrix);
    for(xml_node<> * loop_node = node->first_node("node"); loop_node; loop_node = loop_node->next_sibling("node")){
        joint->addChild(*load_joint_data(loop_node,false));
    }
    return joint;
}

SkeletonData & SkeletonLoader::get_skeleton()
{
    return *skeleton_data_;
}