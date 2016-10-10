#version 330 core 
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normal;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 mvp_Matrix;
uniform mat4 model;

void main()
{
    vec4 worldPos = model * vec4(position, 1.0f);
    FragPos = worldPos.xyz; 
    gl_Position = mvp_Matrix * vec4(position,1.0f);
    TexCoords = texCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalMatrix * normal;
}