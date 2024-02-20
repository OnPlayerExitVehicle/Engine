#version 330 core

struct Material
{
    vec3 color;
    float ambient;
    float diffuse;
    float specular;
    int shininess;
};
uniform Material material;

struct LightMaterial
{
    vec3 color;
    vec3 position;
    float ambient;
    float diffuse;
    float specular;
};
uniform LightMaterial light;

uniform vec3 VEC_ViewPosition;
uniform bool B_IsTextured;
uniform sampler2D myTexture;

in vec2 outTexture;
in vec3 outNormal;
in vec3 outFragPos;

out vec4 fragColor;

void main()
{
    if(B_IsTextured)
    {
        fragColor = texture(myTexture, outTexture);
    }
    else
    {
        fragColor = vec4(material.color, 1.0f);
    }
    
    vec3 ambient = light.color * (material.ambient * light.ambient);

    vec3 norm = normalize(outNormal);
    vec3 lightDir = normalize(light.position - outFragPos);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = (diff * material.diffuse * light.diffuse) * light.color;

    vec3 viewDir = normalize(VEC_ViewPosition - outFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specular = (material.specular * spec * light.specular) * light.color;

    fragColor = vec4(ambient + diffuse + specular, 1.0f) * fragColor;
}