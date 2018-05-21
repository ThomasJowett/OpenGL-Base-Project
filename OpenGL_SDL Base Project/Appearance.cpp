#include "Appearance.h"

Appearance::Appearance()
{
	mMaterial = {
		{ 0.4f, 0.2f, 0.2f, 1.0f },
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		20.0f
	};

	mDiffuseTexID = 0;
	mSpecularTexID = 0;
}

void Appearance::SetMaterial(float diffuse[4], float ambient[4], float specular[4], float specularPower)
{
	mMaterial.diffuse[1] = diffuse[1];
	mMaterial.diffuse[2] = diffuse[2];
	mMaterial.diffuse[3] = diffuse[3];
	mMaterial.diffuse[4] = diffuse[4];

	mMaterial.ambient[1] = ambient[1];
	mMaterial.ambient[2] = ambient[2];
	mMaterial.ambient[3] = ambient[3];
	mMaterial.ambient[4] = ambient[4];

	mMaterial.specular[1] = specular[1];
	mMaterial.specular[2] = specular[2];
	mMaterial.specular[3] = specular[3];
	mMaterial.specular[4] = specular[4];

	mMaterial.specularPower = specularPower;
}

void Appearance::Render(Shader* shader)
{
	//set the current material
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mMaterial.ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mMaterial.diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, mMaterial.specular);
	//glMaterialf(GL_FRONT, GL_SHININESS, mMaterial.specularPower);

	shader->UpdateMaterial(mMaterial);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mDiffuseTexID); //Set the active diffuse texture

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, mSpecularTexID); //Set the active specular texture

	mMesh->Draw();
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0); //reset bound textures to zero

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
}
