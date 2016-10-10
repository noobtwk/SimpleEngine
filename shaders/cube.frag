#version 330 core
in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

struct DirLight{
	vec3 color;
	vec3 direction;
};

struct PointLight {
	vec3 position;
	vec3 color;
	
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 direction;
	vec3 color;
	vec3 position;
	
	float cutOff;
	float outCutOff;
	
	float constant;
	float linear;
	float quadratic;
};


out vec4 color;

uniform vec3 ambientL;

uniform int isDirLighting;
uniform DirLight dirLight;

uniform int isPointLighting;
uniform int pointSize;

uniform PointLight pointLight[20];


uniform int isSpotLighting;
uniform int spotSize;

uniform SpotLight spotLight[10];

uniform vec3 viewPos;

uniform sampler2D texture1;

vec3 calDirLight(DirLight light,vec3 nor,vec3 viewDir,vec3 tex)
{
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(nor,lightDir),0.0);
	
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(nor,halfwayDir),0.0),16.0);
	
	//vec3 ambient = ambientL * tex;
	vec3 diffuse = diff * light.color* tex;
	vec3 specular = spec * light.color;
	return (diffuse + specular);
}

vec3 calPointLight(PointLight light,vec3 norm,vec3 viewDir,vec3 fragPos,vec3 col)
{
	vec3 lightDir = normalize(light.position-fragPos);
	float diff = max(dot(norm,lightDir),0.0);
	
	vec3 halfwayDir = normalize(lightDir+viewDir);
	float spec = pow(max(dot(norm,halfwayDir),0.0f),8.0);
	
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear*distance + light.quadratic*distance*distance);
	
	//vec3 ambient = ambientL * col * attenuation;
	vec3 diffuse = diff * col* light.color * attenuation;
	vec3 specular = spec * light.color * attenuation;
	return (diffuse+specular);
}

vec3 calSpotLight(SpotLight light,vec3 norm,vec3 viewDir,vec3 fragPos,vec3 col)
{
	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon = (light.cutOff - light.outCutOff);
	float intensity = clamp((theta-light.outCutOff)/epsilon,0.0,1.0);
	
	float diff = max(dot(norm,lightDir),0.0);
	
	vec3 halfwayDir = normalize( lightDir + viewDir);
	float spec = pow(max(dot(norm,halfwayDir),0.0),32.0);
	
	vec3 diffuse = diff * col * intensity;
	vec3 specular = spec * light.color * intensity;
	
	float distance = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear*distance + light.quadratic*distance*distance);
	
	diffuse *= attenuation;
	specular *= attenuation;
	
	return (diffuse + specular);
	
	
}

void main()
{
	vec3 color1 = texture(texture1,TexCoords).rgb;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 normal = normalize(Normal);
	vec3 result = color1 * ambientL;
	if(isDirLighting==1)
		result += calDirLight(dirLight,normal,viewDir,color1);
	if(isPointLighting==1)
	{
		for(int i=0;i<pointSize;++i)
		{
			result+=calPointLight(pointLight[i],normal,viewDir,FragPos,color1);
		}
	}
	if(isSpotLighting==1)
	{
		for(int i=0;i<spotSize;++i)
		{
			result +=calSpotLight(spotLight[i],normal,viewDir,FragPos,color1);
		}
	}
	color = vec4(result,1.0f);
}