#version 330 core
out vec4 color;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
    

};
  
#define numLight 5

// in vec3f variable
in vec3 Normal;
in vec2 TextCoord;
in vec3 FragPos;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;
in vec4 FragPosLightSpace;

// Uniform variable
uniform DirLight dirLight;
uniform Material material;
uniform vec3 viewPos;
uniform int invertNormal;
uniform int noLight;
uniform int numActivateLight;
uniform PointLight pointLights[numLight];
uniform bool normalMapping;

uniform sampler2D ourTexture;
uniform sampler2D normalMap; 
uniform sampler2D shadowMap; 

//Definition of our functions
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,vec3 lightDir);
float calculateShadow(vec4 fragPosLightSpace,vec3 normal, vec3 lightDir);

void main()
{ 
 vec3 result;
 vec3 norm = normalize(Normal);

//Calculate color of our texture
 vec4 texColor = texture(ourTexture,TextCoord);
 if(texColor.a < 0.1)
    discard;

if(normalMapping){  
    norm = texture(normalMap, TextCoord).rgb;
    norm = normalize(norm * 2.0 - 1.0);

    // Calculate ambient component
    vec3 ambient = texColor.rgb;
    
    // Calculate diffuse component
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = diff * texColor.rgb;

    // Calculate specular component
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32.0);
    vec3 specular = vec3(0.2) * spec;
    
    // Calculate shadow
    float shadow = calculateShadow(FragPosLightSpace,norm,lightDir);       
    vec3 lighting = (ambient + (0.8 - shadow) * (diffuse + specular)) * texColor.rgb;

    //Calculate the point light
    result=vec3(0.0);
    for(int i = 0; i < numActivateLight; i++)
            result += calculatePointLight(pointLights[i], norm, FragPos, viewDir,lightDir); 

    color = vec4(lighting* (result+(dirLight.ambient * material.ambient + diffuse * dirLight.diffuse * material.diffuse + specular * dirLight.specular * material.specular)), 1.0f);   
}
else {
    //If is a object in the scene
     if(noLight==0){   
        vec3 lightColor = vec3(1.0);
        
        // Calculate ambient component
        vec3 ambient = texColor.rgb;
        
        // Calculate diffuse component
        vec3 lightDir = normalize(dirLight.direction - FragPos);
        float diff = max(dot(lightDir, norm), 0.0);
        vec3 diffuse = diff * lightColor;
        
        // Calculate specular component
        vec3 viewDir = normalize(viewPos - FragPos);
        float spec = 0.0;
        vec3 halfwayDir = normalize(lightDir + viewDir);  
        spec = pow(max(dot(norm, halfwayDir), 0.0), 64.0);
        vec3 specular = spec * lightColor;

        // Calculate shadow
        float shadow = calculateShadow(FragPosLightSpace,norm,lightDir);       
        vec3 lighting = (ambient * material.ambient  + (1.0 - shadow) * (diffuse* material.diffuse  + specular  * material.specular)) * texColor.rgb; 
    
        //Added point Light
        result=vec3(0.0);
        for(int i = 0; i < numActivateLight; i++)
            result += calculatePointLight(pointLights[i], norm, FragPos, viewDir,lightDir); 

        color=texColor * (vec4(lighting, 1.0f) + vec4(result,1.0));
     }

     //If is a menu or text in the scene
     if(noLight==1)
        color=texColor* vec4(material.ambient,1.0f);
 }

}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir,vec3 lightDir)
{
    // Calculate diffuse component
    float diff = max(dot(lightDir,normal), 0.0);

    // Calculate specular component
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

    // Calculate the attenuation of our point light
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    // Calculate the result component of our point Light
    vec3 ambient = light.ambient *2.0 * material.ambient;
    vec3 diffuse = light.diffuse * diff *2.0 * material.diffuse;
    vec3 specular = light.specular *spec*2.0 * material.specular;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

float calculateShadow(vec4 fragPosLightSpace,vec3 normal, vec3 lightDir)
{
    // Calculate fragment light space in range [-1,1]
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    
    // transform fragment light space in range[-1,1] to [0,1]
    projCoords = projCoords * 0.5 + 0.5;

    // Obtain the close depth value
    float closestDepth = texture(shadowMap, projCoords.xy).r; 

    // Obtain the depth of our current fragment
    float currentDepth = projCoords.z;

    // Comprobe if the current fragment is in shadow or not
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);   
    
    //Soft the shadow using PCF ( using four samples )
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = 0; x <= 1; ++x){
        for(int y = 0; y <= 1; ++y)    {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 4.0;

    if(projCoords.z>1.0)
        shadow=0.0;

    return shadow;
}