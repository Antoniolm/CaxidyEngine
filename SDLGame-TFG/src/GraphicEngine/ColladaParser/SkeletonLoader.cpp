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
    GLfloat * manual_matrix = new GLfloat[16];
    joint_orders_ = joint_orders;

    manual_matrix[0]=0.99999994;  manual_matrix[1]=0.0;          manual_matrix[2]=0.0;           manual_matrix[3]=0.0;   
    manual_matrix[4]=0.0;         manual_matrix[5]=-4.371139e-8; manual_matrix[6]=1.0;           manual_matrix[7]=0.0;
    manual_matrix[8]=0.0;         manual_matrix[9]=-1.0;         manual_matrix[10]=-4.371139e-8; manual_matrix[11]=0.0;
    manual_matrix[12]=0.0;        manual_matrix[13]=0.0;         manual_matrix[14]=0.0;          manual_matrix[15]=1.0;

    current_matrix.setMatrix(manual_matrix);

    xml_node<> * armature_data = xml_parser.getChildWithAttribute(&visual_scene_node, "node", "id", "Armature");
    current_matrix.setMatrix(manual_matrix);
    
    xml_node<> * head_node = armature_data->first_node("node");

    load_joint_data(head_node,true);
}

JointData SkeletonLoader::load_joint_data(xml_node<> * node, bool root)
{
    JointData joint;

    int id = xml_parser.indexOf(joint_orders_, node->first_attribute("id")->value());
    Matrix4f matrix(xml_parser.extract(node->first_node("matrix")->value()));

    if(root){
		current_matrix.product(matrix.getMatrix());
	}
    else {
        current_matrix.setMatrix(matrix.getMatrix());
    }

    std::cout<< id << "->"<< node->first_attribute("id")->value() <<std::endl;
    GLfloat * test = current_matrix.getMatrix();
    cout<< test[0]<< " "<< test[1]<< " "<< test[2]<< " "<< test[3]<< " "<< endl; 
    cout<< test[4]<< " "<< test[5]<< " "<< test[6]<< " "<< test[7]<< " "<< endl;
    cout<< test[8]<< " "<< test[9]<< " "<< test[10]<< " "<< test[11]<< " "<< endl;
    cout<< test[12]<< " "<< test[13]<< " "<< test[14]<< " "<< test[15]<< " "<< endl;

    for(xml_node<> * loop_node = node->first_node("node"); loop_node; loop_node = loop_node->next_sibling("node")){
        joint.addChild(load_joint_data(loop_node,false));
    }
    return joint;
}