#version 330 core

layout(location = 0) out vec4 color;

uniform sampler2D normalMap; 

void main(void){
	vec3 norm = normalize(Normal); 

	if(normalMapping){  	
	    norm = texture(normalMap, TextCoord).rgb;
	    norm = normalize(norm * 2.0 - 1.0);
	}
	
	color = vec4(0.0,0.0,0.0,1.0);
	
}