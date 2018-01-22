#ifndef _OBJECT3DS_H_
#define _OBJECT3DS_H_
#include "Commons.h"
#include <string>
#include "Texture2D.h"
#include "Transformation.h"
#include "SceneNode.h"

using::std::string;
class Texture;

class Object3DS : public SceneNode
{
public:
	Object3DS(Vector3D startPosition, string modelFileName, string mFileType);
	~Object3DS() {}

	void Update(float deltaTime, float rotation, Vector3D translation, Vector3D scale);
	void Render();

	//Load the 3DS file
	void LoadModel();

	//Load texture for this model.
	void LoadTexture(char* texturepath, int width, int height);

	void SetTransform(Enum, float*, int);
	void SetTransform(Enum, float, float, float, int);
	void SetTransform(Enum, float, float, float, float, int);
	void SetTransform(Transformation *);

	Vector3D GetPosition();

private:
	void computeNormals(obj_type_ptr mesh);
	
	Vector3D mScale;
	Vector3D mPosition;
	float mRotation;

	Transformation * TransNode;

	char fileName[20];
	char fileType[3];
	char textureName[20];
	bool fileHasNormals;

	obj_type object;
};


#endif // !_OBJECT3DS_H_
