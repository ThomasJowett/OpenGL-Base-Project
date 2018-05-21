#ifndef _Appearance_H
#define _Appearance_H

#include "iRenderable.h"
#include "Commons.h"
#include "Mesh.h"

#include <gl\GLU.h>

class Appearance : public IRenderable
{
public:
	Appearance();
	Appearance(Mesh* mesh, Material material, GLuint diffuseTexID, GLuint specularTexID) 
		: mMesh(mesh), mMaterial(material), mDiffuseTexID(diffuseTexID), mSpecularTexID(specularTexID) {}
	~Appearance() = default;

	Material GetMaterial() const { return mMaterial; }
	void SetMaterial(Material material) { mMaterial = material; }
	void SetMaterial(float diffuse[4], float ambient[4], float specular[4], float specularPower);

	Mesh* GetMesh() const { return mMesh; }
	void SetMesh(Mesh* mesh) { mMesh = mesh; }

	GLuint GetDiffuseTextureID() const { return mDiffuseTexID; }

	void Render(Shader* shader) override;

private:
	Mesh* mMesh;
	Material mMaterial;

	GLuint mDiffuseTexID;
	GLuint mSpecularTexID;
};
#endif // !_Appearance_H
