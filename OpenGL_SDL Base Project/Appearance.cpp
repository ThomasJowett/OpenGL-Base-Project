#include "Appearance.h"

Appearance::Appearance()
{
	mMaterial = {
		{ 0.4f, 0.2f, 0.2f, 1.0f },
		{ 0.2f, 0.2f, 0.2f, 1.0f },
		{ 0.5f, 0.5f, 0.5f, 1.0f },
		20.0f
	};

	mTextureID = 0;
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

void Appearance::Render()
{
	//set the current material
	glMaterialfv(GL_FRONT, GL_AMBIENT, mMaterial.ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mMaterial.diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mMaterial.specular);
	glMaterialf(GL_FRONT, GL_SHININESS, mMaterial.specularPower);

	glBindTexture(GL_TEXTURE_2D, mTextureID); //We set the active texture


	glBegin(GL_TRIANGLES); //glBegin and glEnd delimit the vertices that feine a primitive (triangles)
	for (int l_index = 0; l_index < mGeometry.triangles_qty; l_index++)
	{
		//-----------------FIRST VERTEX ----------------//

		glTexCoord2f(mGeometry.texCoords[mGeometry.texCoordIndices[l_index].a].u,
			mGeometry.texCoords[mGeometry.texCoordIndices[l_index].a].v);

		glNormal3f(mGeometry.normals[mGeometry.normalsIndices[l_index].a].x,
			mGeometry.normals[mGeometry.normalsIndices[l_index].a].y,
			mGeometry.normals[mGeometry.normalsIndices[l_index].a].z);

		glVertex3f(mGeometry.vertices[mGeometry.triangles[l_index].a].x,
			mGeometry.vertices[mGeometry.triangles[l_index].a].y,
			mGeometry.vertices[mGeometry.triangles[l_index].a].z);

		//-----------------SECOND VERTEX -----------------//


		glTexCoord2f(mGeometry.texCoords[mGeometry.texCoordIndices[l_index].b].u,
			mGeometry.texCoords[mGeometry.texCoordIndices[l_index].b].v);

		glNormal3f(mGeometry.normals[mGeometry.normalsIndices[l_index].b].x,
			mGeometry.normals[mGeometry.normalsIndices[l_index].b].y,
			mGeometry.normals[mGeometry.normalsIndices[l_index].b].z);

		glVertex3f(mGeometry.vertices[mGeometry.triangles[l_index].b].x,
			mGeometry.vertices[mGeometry.triangles[l_index].b].y,
			mGeometry.vertices[mGeometry.triangles[l_index].b].z);

		//-----------------THIRD VERTEX -----------------//

		glTexCoord2f(mGeometry.texCoords[mGeometry.texCoordIndices[l_index].c].u, 
			mGeometry.texCoords[mGeometry.texCoordIndices[l_index].c].v);

		glNormal3f(mGeometry.normals[mGeometry.normalsIndices[l_index].c].x,
			mGeometry.normals[mGeometry.normalsIndices[l_index].c].y,
			mGeometry.normals[mGeometry.normalsIndices[l_index].c].z);

		glVertex3f(mGeometry.vertices[mGeometry.triangles[l_index].c].x,
			mGeometry.vertices[mGeometry.triangles[l_index].c].y,
			mGeometry.vertices[mGeometry.triangles[l_index].c].z);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}
