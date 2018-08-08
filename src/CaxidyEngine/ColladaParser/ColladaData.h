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

#include "matrix/matrix4f.h"
#include "matrix/structdata.h"

namespace CaxidyEngine {

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a Vertex skin data
*/
//////////////////////////////////////////////////////////////////////////
struct VertexSkinData{
    std::vector<int> joint_ids;
    std::vector<float> weights;

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
            std::vector<float> topWeights;
            topWeights.resize(max);
            
            float total = 0;
		    for(int i=0;i<topWeights.size();i++){
    			topWeights[i] = weights[i];
			    total += topWeights[i];
		    }
            
            weights.clear();
		    for(int i=0;i<topWeights.size();i++){
			    weights.push_back(std::min((float)(topWeights[i]/(float)total), 1.0f));
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

	std::string to_string(){
		std::string result= "";
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
    std::vector<std::string> joint_order_;
    std::vector<VertexSkinData> vertices_skin_data_;

	SkinningData(){

	}

    SkinningData(const std::vector<std::string> & joint_order, const std::vector<VertexSkinData> & vertices_skin_data){
        joint_order_ = joint_order;
		vertices_skin_data_ = vertices_skin_data;
    }
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a Vertex skin data
*/
//////////////////////////////////////////////////////////////////////////
struct JointData {

	int index_;
	std::string name_id_;
	Matrix4f bind_local_transform_;

	std::vector<JointData> children;

	JointData(){}
	
	JointData(int index, std::string nameId, Matrix4f & bindLocalTransform) {
		index_ = index;
		name_id_ = nameId;
		bind_local_transform_.setMatrix(bindLocalTransform.getMatrix());
	}

	void addChild(JointData child) {
		children.push_back(child);
	}
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a Vertex skin data
*/
//////////////////////////////////////////////////////////////////////////
struct SkeletonData{
    int joint_count_;
	JointData head_joint_;

	SkeletonData() :
		head_joint_()
	{

	}

    SkeletonData(int joint_count, const JointData & head_joint){
        joint_count_ = joint_count;
		head_joint_ = head_joint;
    }
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a Vertex skin data
*/
//////////////////////////////////////////////////////////////////////////
struct Vertex{
    	
	int NO_INDEX;
	
	vec3f position_;
	int texture_index_;
	int normal_index_;
	struct Vertex * duplicate_vertex_;
	int index_;
	float length_;
	std::vector<vec3f> tangents_;
	vec3f averaged_tangent_;
	
	VertexSkinData weights_data_;

	Vertex(int index,const vec3f & position, const VertexSkinData & weightsData){
		NO_INDEX = -1;
		texture_index_ = NO_INDEX;
		normal_index_ = NO_INDEX;
		duplicate_vertex_ = NULL;
		index_ = index;
		weights_data_ = weightsData;
		position_ = position;
		length_ = position_.length();
	}
	
	void addTangent(vec3f tangent){
		tangents_.push_back(tangent);
	}
	
	void averageTangents(){
		if(tangents_.empty()){
			return;
		}
		for(vec3f tangent : tangents_){
			averaged_tangent_ = averaged_tangent_+ tangent;
		}
		averaged_tangent_.normalize();
	}
	
	bool is_set(){
		return texture_index_!=NO_INDEX && normal_index_!=NO_INDEX;
	}
	
	bool has_same_texture_and_normal(int textureIndexOther,int normalIndexOther){
		return textureIndexOther==texture_index_ && normalIndexOther==normal_index_;
	}
};

struct JointTransformData {

	std::string joint_name_id_;
	Matrix4f current_matrix_;

	JointTransformData(std::string joint_name_id, Matrix4f & current_matrix) {
		joint_name_id_ = joint_name_id;
		current_matrix_.setMatrix(current_matrix.getMatrix());
	}
};

struct KeyFrameData {

	float time_;
	std::vector<JointTransformData> joint_transforms;
	
	KeyFrameData(float time){
		time_ = time;
	}
	
	void addJointTransform(JointTransformData transform){
		joint_transforms.push_back(transform);
	}
	
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a animation data
*/
//////////////////////////////////////////////////////////////////////////
struct AnimationData{
	float length_seconds_;
	std::vector<KeyFrameData> key_frames_;

	AnimationData()
	{

	}

	AnimationData(float length_seconds, const std::vector<KeyFrameData> & key_frames)
	{
		length_seconds_ = length_seconds;
		key_frames_ = key_frames;
	}
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make a mesh data
*/
//////////////////////////////////////////////////////////////////////////
struct MeshData{
	std::vector<float> vertices_;
	std::vector<float> textureCoords_;
	std::vector<float> normals_;
	std::vector<int>   indices_;
	std::vector<int>   jointIds_;
	std::vector<float> vertexWeights_;
	
	MeshData()
	{
		
	}

	MeshData(const std::vector<float> & vertices,const  std::vector<float> & textureCoords, const std::vector<float> & normals, const std::vector<int> & indices,
			const std::vector<int> & jointIds, const std::vector<float> & vertexWeights)
	{
		vertices_ = vertices;
		textureCoords_ = textureCoords;
		normals_ = normals;
		indices_ = indices;
		jointIds_ = jointIds;
		vertexWeights_ = vertexWeights;
	}
};

/////////////////////////////////////////////////////////////////////////
/**
*    Struct --> This struct will let us make an animated model data
*/
//////////////////////////////////////////////////////////////////////////
struct AnimatedModelData{
	SkeletonData joints_;
	MeshData mesh_;

	AnimatedModelData()
	{
		
	}

	AnimatedModelData(const MeshData & mesh, const SkeletonData & joints)
	{
		joints_ = joints;
		mesh_ = mesh;
	}
};

} // CaxidyEngine

#endif // COLLADADATA_H