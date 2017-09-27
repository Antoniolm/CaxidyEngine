#version 330

layout(location = 0) in vec3 position;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 textCoord;
layout(location=3) in vec3 tangent;
layout(location=4) in vec3 bitangent;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 viewPosVertex;

uniform float offSet; 

void main(void){
   gl_Position = projection * view * transform * vec4(position * offSet,1.0f);//u_offset1,1.0f);
}