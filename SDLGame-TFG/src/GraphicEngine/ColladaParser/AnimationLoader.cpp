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

#include "AnimationLoader.h"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

AnimationLoader::AnimationLoader(xml_node<> & animation_node, xml_node<> & joint_node)
{
    xml_node<> * skeleton = xml_parser.getChildWithAttribute(joint_node.first_node("visual_scene"), "node", "id", "Armature");
    std::string root_id= skeleton->first_node("node")->first_attribute("id")->value();

    xml_node<> * timeData = animation_node.first_node("animation")->first_node("source")->first_node("float_array");
    vector<string> raw_times = xml_parser.extract(timeData->value());
    vector<float> times;

    for(int i=0;i<raw_times.size();i++){
        times.push_back(stof(raw_times[i]));
    }

    float duration = times[times.size()-1];

    vector<KeyFrameData> frames;
    for(int i=0;i<times.size();i++){
        frames.push_back(KeyFrameData(times[i]));
    }
}