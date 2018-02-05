#include "GameObject.h"
#include "../gl/glut.h"
#include "3DSLoader.h"
#include "OBJLoader.h"
#include "SDL.h"

GameObject::GameObject(Vector3D startPosition, string modelFileName, string mFileType)
{
	//Start Position.
	mPosition = startPosition;
	mScale = { 1.0f, 1.0f, 1.0f };

	//3DS file to load.
	std::strcpy(fileName, modelFileName.c_str());
	std::strcpy(fileType, mFileType.c_str());
	LoadModel();

	mRotation = 0.0f;

	TransNode = NULL;
}

void GameObject::LoadModel()
{
	if (fileName != NULL)
	{
		if (strcmp(fileType, "OBJ") == 0)
		{
			LoadOBJ(&object, fileName);
			//computeNormals(&object);
			fileHasNormals = true;
		}
		else if (strcmp(fileType, "3DS") == 0) 
		{
			Load3DS(&object, fileName);
			computeNormals(&object);
			fileHasNormals = false;
		}
		else
		{
			printf("File type not recognised\n");
		}
	}
}

void GameObject::LoadTexture(char* texturepath, int width, int height)
{
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	Texture2D * texture = new Texture2D();
	texture->Load(texturepath, width, height);
	object.id_texture = texture->GetID();
}

void GameObject::SetTransform(Enum pName, float * v, int Order)
{
	if (TransNode == NULL)
		TransNode = new Transformation;

	TransNode->SetValuev(pName, v, Order);
}

void GameObject::SetTransform(Enum pName, float x, float y, float z, int Order)
{
	if (TransNode == NULL)
		TransNode = new Transformation;

	TransNode->SetValue(pName, x, y, z, Order);
}

void GameObject::SetTransform(Enum pName, float a, float x, float y, float z, int Order)
{
	if (TransNode == NULL)
		TransNode = new Transformation;

	TransNode->SetValue(pName, a, x, y, z, Order);
}

void GameObject::SetTransform(Transformation * T)
{
	if (TransNode != NULL)
		delete TransNode;

	TransNode = T;
}

Vector3D GameObject::GetPosition()
{
	return mPosition;
}

void GameObject::Update(float deltaTime, float rotation, Vector3D translation, Vector3D scale)
{
	mScale = scale;

	mPosition = mPosition + translation;

	mRotation = mRotation + rotation;
}

void GameObject::Render()
{
	//glScalef(mScale.x, mScale.y, mScale.z);
	//glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	//glRotatef(mRotation, 1, 1, 1);
	if (TransNode)
		TransNode->Render();

	glBindTexture(GL_TEXTURE_2D, object.id_texture); //We set the active texture


	glBegin(GL_TRIANGLES); //glBegin and glEnd delimit the vertices that feine a primitive (triangles)
	for (int l_index = 0; l_index < object.triangles_qty; l_index++)
	{
		//-----------------FIRST VERTEX ----------------//
		// Texture coordinates of the first vertex 
		
		// Coordinates of the first vertex
		
		if (fileHasNormals)
		{
			glTexCoord2f(object.texCoord[object.texCoordIndices[l_index].a].u, object.texCoord[object.texCoordIndices[l_index].a].v);
			glNormal3f(object.normals[object.normalsIndices[l_index].a].x, object.normals[object.normalsIndices[l_index].a].y, object.normals[object.normalsIndices[l_index].a].z);
		}
		else
		{
			glTexCoord2f(object.texCoord[object.triangle[l_index].a].u, object.texCoord[object.triangle[l_index].a].v);
			glNormal3f(object.normals[l_index].x, object.normals[l_index].y, object.normals[l_index].z);
		}
		glVertex3f(object.vertex[object.triangle[l_index].a].x,
			object.vertex[object.triangle[l_index].a].y,
			object.vertex[object.triangle[l_index].a].z);
		//std::cout << "Vertex.a read";//Uncomment to see if the vertexs are being read
		//Vertex definition 
		//-----------------SECOND VERTEX -----------------
		// Texture coordinates of the second vertex 
		
		//

		// Coordinates of the second vertex
		
		if (fileHasNormals)
		{
			glTexCoord2f(object.texCoord[object.texCoordIndices[l_index].b].u, object.texCoord[object.texCoordIndices[l_index].b].v);
			glNormal3f(object.normals[object.normalsIndices[l_index].b].x, object.normals[object.normalsIndices[l_index].b].y, object.normals[object.normalsIndices[l_index].b].z);
		}
		else
		{
			glTexCoord2f(object.texCoord[object.triangle[l_index].b].u, object.texCoord[object.triangle[l_index].b].v);
			glNormal3f(object.normals[l_index].x, object.normals[l_index].y, object.normals[l_index].z);
		}
		glVertex3f(object.vertex[object.triangle[l_index].b].x,
			object.vertex[object.triangle[l_index].b].y,
			object.vertex[object.triangle[l_index].b].z);
		//-----------------THIRD VERTEX -----------------
		// Texture coordinates of the third vertex 
		
		//

		// Coordinates of the Third vertex
		
		if (fileHasNormals)
		{
			glTexCoord2f(object.texCoord[object.texCoordIndices[l_index].c].u, object.texCoord[object.texCoordIndices[l_index].c].v);
			glNormal3f(object.normals[object.normalsIndices[l_index].c].x, object.normals[object.normalsIndices[l_index].c].y, object.normals[object.normalsIndices[l_index].c].z);
		}
		else
		{
			glTexCoord2f(object.texCoord[object.triangle[l_index].c].u, object.texCoord[object.triangle[l_index].c].v);
			glNormal3f(object.normals[l_index].x, object.normals[l_index].y, object.normals[l_index].z);
		}
		glVertex3f(object.vertex[object.triangle[l_index].c].x,
			object.vertex[object.triangle[l_index].c].y,
			object.vertex[object.triangle[l_index].c].z);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void GameObject::computeNormals(obj_type_ptr mesh)
{
	// face normals
	const int normalCount = mesh->triangles_qty;

	// first pass: compute face normals, solve vertex sharing between faces
	for (int i = 0; i<mesh->triangles_qty; ++i)
	{
		Triangle& face = mesh->triangle[i];

		// compute face normal
		Vector3D p0 = mesh->vertex[int(face.a)];
		Vector3D p1 = mesh->vertex[int(face.b)];
		Vector3D p2 = mesh->vertex[int(face.c)];
		Vector3D normal = normal.Cross((p0 - p1), (p0 - p2));
		mesh->normals[i] = normal.GetNormalized();
	}
}