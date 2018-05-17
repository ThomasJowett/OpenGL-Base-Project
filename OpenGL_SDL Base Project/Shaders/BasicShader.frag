#version 460

layout (std140) uniform Materials{
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	float shininess;
};

in VertexData {
	vec3 posW;
	vec2 texCoord;
	vec3 normal;
	vec3 eye;
	vec3 lightDir;
} FragmentIn;

out vec4 FragColour;

uniform sampler2D txDiffuse;
uniform sampler2D txSpecular;

void main()
{
	vec3 normalW = normalize(FragmentIn.normal);
	vec3 toEye = normalize(FragmentIn.eye - FragmentIn.posW);

	vec4 textureColour = texture2D(txDiffuse, FragmentIn.texCoord);
	//vec4 textureSpecular = texture2D(txSpecular, FragmentIn.texCoord);

	vec3 ambientLight = vec3(0.5,0.5,0.5);
	vec3 diffuseLight = vec3(1.0,1.0,1.0);
	vec3 specularLight = vec3(0.8,0.8,0.8);
	float specularPower = 20.0f;

	vec3 ambientMat = vec3(0.3,0.3,0.3);
	vec3 diffuseMat = vec3(1.0,1.0,1.0);
	vec3 specularMat = vec3(0.5,0.5,0.5);

	vec3 ambient = vec3(0.0,0.0,0.0);
	vec3 diffuse = vec3(0.0,0.0,0.0);
	vec3 specular = vec3(0.0,0.0,0.0);

	vec3 lightLecNorm = normalize(FragmentIn.lightDir);

	vec3 r = reflect(-lightLecNorm, FragmentIn.normal);

	float specularAmount = pow(max(dot(r, toEye), 0.0f), specularPower);

	float diffuseAmount = max(dot(lightLecNorm, FragmentIn.normal), 0.0f);

	specular += specularAmount * (specularLight * specularMat).rgb;
	diffuse += diffuseAmount * (diffuseLight * diffuseMat).rgb;
	ambient += (ambientMat * ambientLight).rgb;


	vec4 finalColour;
	finalColour = vec4((textureColour.rgb * (ambient + diffuse) + specular), textureColour.a);
	
	FragColour = finalColour;
}