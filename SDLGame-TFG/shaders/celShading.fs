#version 330 core

layout(location = 0) out vec4 color;

// in vec3f variable
in vec3 Normal;
in vec2 TextCoord;
in vec4 posFigure;

uniform bool normalMapping;
uniform sampler2D normalMap; 

void main(void){
	vec3 norm = normalize(Normal); 

	if(normalMapping){  	
	    norm = texture(normalMap, TextCoord).rgb;
	    norm = normalize(norm * 2.0 - 1.0);
	}

	color = vec4(norm.x,norm.y,norm.z,posFigure.z);
}