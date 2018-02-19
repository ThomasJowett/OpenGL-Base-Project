#ifndef _Appearance_H
#define _Appearance_H

#include "Commons.h"
#include <gl\GLU.h>

class Appearance
{
public:
	Appearance();
	Appearance(MeshData* geometry, Material material, GLuint textureID) /*: mGeometry(geometry), mMaterial(material), mTextureID(textureID)*/ {
		mGeometry = geometry; mMaterial = material; mTextureID = textureID;
	}
	~Appearance() {}

	Material GetMaterial() const { return mMaterial; }
	void SetMaterial(Material material) { mMaterial = material; }
	void SetMaterial(float diffuse[4], float ambient[4], float specular[4], float specularPower);

	MeshData* GetGeometry() const { return mGeometry; }
	void SetGeometry(MeshData* geometry) { mGeometry = geometry; }

	GLuint GetTextureID() const { return mTextureID; }

	void Render();

private:
	MeshData* mGeometry;
	Material mMaterial;
	GLuint mTextureID;
};
#endif // !_Appearance_H
