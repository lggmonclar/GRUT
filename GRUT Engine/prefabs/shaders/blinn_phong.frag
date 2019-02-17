#version 430 core
out vec4 FragColor;

layout (std140, binding = 1) uniform ViewPosition { //UBO
    vec3 ViewPos; // 12 (4 padding)
};

struct PointLight {
    vec3 Position;
    vec3 Color;
};

layout (std430, binding = 2) buffer PointLights { //SSBO
    PointLight pointLights[]; //( (12 + (4 padding)) + (12 + (4 padding)) ) * pointLightsSize
};

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform vec3 color;
uniform sampler2D tex;

vec3 calcPointLights() {
    vec3 result;
    for(int i = 0; i < pointLights.length(); i++) {
        // ambient
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * pointLights[i].Color;
        
        // diffuse 
        vec3 norm = normalize(fs_in.Normal);
        vec3 lightDir = normalize(pointLights[i].Position - fs_in.FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * pointLights[i].Color;
        
        // specular
        float specularStrength = 0.5;
        vec3 viewDir = normalize(ViewPos - fs_in.FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specular = specularStrength * spec * pointLights[i].Color;  
            
        result += (ambient + diffuse + specular) * color;
    }

    return result;
}

void main() {
    FragColor = vec4(calcPointLights(), 1.0);
}