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

#ifndef COLLADADATA_H
#define COLLADADATA_H

#include <math.h>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a Vertex skin data
*/
//////////////////////////////////////////////////////////////////////////
struct VertexSkinData{
    vector<int> joint_ids;
    vector<float> weights;

    VertexSkinData(){
    }
    void addJoint(int jointId, float weight){
		for(int i=0;i<weights.size();i++){
			if(weight > weights[i]){
				joint_ids.push_back(jointId);
				weights.push_back(weight);
				return;
			}
		}
		joint_ids.push_back(jointId);
		weights.push_back(weight);
	}
	
	void limitJointNumber(int max){
		if(joint_ids.size() > max){
            vector<float> topWeights;
            topWeights.resize(max);
            
            float total = 0;
		    for(int i=0;i<topWeights.size();i++){
    			topWeights[i] = weights[i];
			    total += topWeights[i];
		    }
            
            weights.clear();
		    for(int i=0;i<topWeights.size();i++){
			    weights.push_back(min((float)(topWeights[i]/(float)total), 1.0f));
		    }

            while(joint_ids.size() > max){
    			joint_ids.pop_back();
		    }

		}else if(joint_ids.size() < max){
            while(joint_ids.size() < max){
			    joint_ids.push_back(0);
			    weights.push_back(0);
		    }
		}
	}

	string to_string(){
		string result= "";
		for(int i=0;i<weights.size();i++){
			result += "item(" +std::to_string(i)+ ")= [ "+ std::to_string(joint_ids[i])+ "," + std::to_string(weights[i])+ "] \n";
		}
		return result;
	}
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a Vertex skin data
*/
//////////////////////////////////////////////////////////////////////////
struct SkinningData{
    vector<string> joint_order_;
    vector<VertexSkinData> vertices_skin_data_;

	SkinningData(){

	}

    SkinningData(const vector<string> & joint_order, const vector<VertexSkinData> & vertices_skin_data){
        joint_order_ = joint_order;
		vertices_skin_data_ = vertices_skin_data;
    }
};

#endif // COLLADADATA_H