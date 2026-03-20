#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
    vec3 ambient;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 emission;
    float opacity;
    float refraction;
    int illuminationModel;
}; 
uniform Material material;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform vec3 viewPos;

void main()
{    
    // Normalize the normal vector
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Prevent negative lighting when light is behind the object
    float diff = max(dot(norm, lightDir), 0.0);

    // Compute reflection for specular highlight
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), max(material.shininess, 1.0));

    // Compute ambient, diffuse, and specular components
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    // Final color output
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
