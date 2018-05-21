#version 460

in VertexData {
	vec3 posW;
	vec2 texCoord;
	vec3 normal;
} FragmentIn;

out vec4 FragColour;

layout (std140, binding = 5 ) uniform Material{
	vec4 ambientMat;
	vec4 diffuseMat;
	vec4 specularMat;
	float specularPower;
};

layout (std140, binding = 2) uniform Light{
	vec4 ambientLight;
	vec4 diffuseLight;
	vec4 specularLight;
	vec3 lightPosition;
};

uniform vec3 eyePosW;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

void main()
{
	vec3 normalW = normalize(FragmentIn.normal);
	vec3 toEye = normalize(eyePosW - FragmentIn.posW);

	vec4 textureColour = texture2D(diffuseTexture, FragmentIn.texCoord);
	vec4 textureSpecular = texture2D(specularTexture, FragmentIn.texCoord);

	vec3 lightVecNorm = vec3(normalize(lightPosition - FragmentIn.posW));

	vec3 r = reflect(-lightVecNorm, FragmentIn.normal);

	float specularAmount = pow(max(dot(r, toEye), 0.0f), specularPower);

	float diffuseAmount = max(dot(lightVecNorm, FragmentIn.normal), 0.0f);

	vec3 specular = specularAmount * (specularLight.rgb * specularMat.rgb).rgb * textureSpecular.r;
	vec3 diffuse = diffuseAmount * (diffuseLight.rgb * diffuseMat.rgb).rgb;
	vec3 ambient = (ambientLight.rgb * ambientMat.rgb).rgb;
	
	FragColour = vec4(((textureColour.rgb * (ambient + diffuse)) + specular), textureColour.a);
}