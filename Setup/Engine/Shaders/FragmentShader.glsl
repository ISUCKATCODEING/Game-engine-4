#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;


struct Light{
vec3 lightPosition;
float ambientValue;
float diffuseValue;
float specularValue;
vec3 lightColour;

};



uniform sampler2D inputTexture;
uniform vec3 cameraPosition;
uniform Light light;

out vec4 fColour;

void main(){
fColour = texture(inputTexture, TexCoords);

//Ambient
vec3 ambient = light.ambientValue* texture(inputTexture, TexCoords).rgb* light.lightColour;

//Diffuse
vec3 norm = normalize(Normal);
vec3 lightDir= normalize(light.lightPosition-FragPosition);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuse = (diff * light.diffuseValue) * texture(inputTexture, TexCoords).rgb* light.lightColour;

//Specular
vec3 viewDir= normalize(cameraPosition-FragPosition);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specular = (spec * light.specularValue)* light.lightColour;

vec3 result= ambient + diffuse + specular;
fColour= vec4(result, 1.0f);
}