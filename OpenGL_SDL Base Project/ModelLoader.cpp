#include "ModelLoader.h"
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

IndexedModel ModelLoader::LoadStaticMesh(const char * filename)
{
	IndexedModel result;

	const aiScene* model = aiImportFile(filename, aiProcess_Triangulate);

	Vector3D position;

	for (int i = 0; i < model->mMeshes[0]->mNumVertices; i++)
	{
		position.x = model->mMeshes[0]->mVertices[i].x;
		position.y = model->mMeshes[0]->mVertices[i].y;
		position.y = model->mMeshes[0]->mVertices[i].z;

		result.positions.push_back(position);
	}

	return result;
}
