#version 400

	layout(location=0) in vec3 position;
	layout(location=1) in vec3 normal;
	layout(location=2) in vec2 textCoord;
	layout(location=3) in vec3 tangent;
	layout(location=4) in vec3 bitangent;

	out vec3 FragPos;
	out vec3 Normal;
	out vec2 TextCoord;
	out vec3 TangentLightPos;
	out vec3 TangentViewPos;
	out vec3 TangentFragPos;
	out vec4 FragPosLightSpace;

	out vec4 FragPosCameraSpace;

	uniform mat4 transform;
	uniform mat4 view;
	uniform mat4 projection;
	uniform vec3 lightPosVertex;
	uniform vec3 viewPosVertex;
	uniform mat4 lightSpaceMatrix;
	uniform mat4 spaceMatrix;

	void main(void)
	{
		gl_Position = projection * view * transform * vec4(position,1.0f);

		FragPos = vec3(transform * vec4(position, 1.0f));
		Normal= mat3(transpose(inverse(transform))) * normal;
		TextCoord=textCoord;

		mat3 NormalShadow=transpose(inverse(mat3(transform)));
    	vec3 T = normalize(mat3(transform) * tangent);
    	vec3 B = normalize(mat3(transform) * bitangent);
    	vec3 N = normalize(mat3(transform) * normal);
    	mat3 TBN = transpose(mat3(T, B, N));

    	TangentLightPos = TBN * lightPosVertex;
    	TangentViewPos  = TBN * viewPosVertex;
    	TangentFragPos  = TBN * FragPos;
    	
		FragPosLightSpace= lightSpaceMatrix * vec4(FragPos,1.0);
		FragPosCameraSpace= spaceMatrix * vec4(FragPos,1.0);
	}