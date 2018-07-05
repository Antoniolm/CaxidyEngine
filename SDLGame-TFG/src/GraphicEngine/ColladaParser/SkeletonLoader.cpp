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

 #include "XmlParserUtils.h"

SkeletonLoader::SkeletonLoader(xml_node<> & visual_scene_node, vector<string> joint_orders)
{
    XmlParserUtils xml_parser;
    current_matrix.identity();
    current_matrix.rotation(-90,1.0,0.0,0.0);

    GLfloat * test = current_matrix.getMatrix();
    // string weightsDataId= xml_parser.getChildWithAttribute(visual_scene_node, "input", "semantic", "WEIGHT")->first_attribute("source")->value();

    cout<< test[0]<< " "<< test[1]<< " "<< test[2]<< " "<< test[3]<< " "<< endl; 
    cout<< test[4]<< " "<< test[5]<< " "<< test[6]<< " "<< test[7]<< " "<< endl;
    cout<< test[8]<< " "<< test[9]<< " "<< test[10]<< " "<< test[11]<< " "<< endl;
    cout<< test[12]<< " "<< test[13]<< " "<< test[14]<< " "<< test[15]<< " "<< endl;
}