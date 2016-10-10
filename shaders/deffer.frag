#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture1;

//uniform vec3 Color;

void main()
{    
    
    gPosition = FragPos;
    vec3 norm = normalize(Normal);
    //gl_FragColor = vec4(norm,1.0f);

    gColor = texture(texture1,TexCoords).rgb;
	
    gNormal = normalize(Normal);

}