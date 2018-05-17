#ifndef OBJLOADER2_H_INCLUDED
#define OBJLOADER2_H_INCLUDED

#include <vector>
#include <string>
#include "Vector.h"
#include "Mesh.h"

struct OBJIndex
{
	unsigned int vertexIndex;
	unsigned int uvIndex;
	unsigned int normalIndex;

	bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class OBJModel
{
public:
	std::vector<OBJIndex> OBJIndices;
	std::vector<Vector3D> vertices;
	std::vector<Vector2D> uvs;
	std::vector<Vector3D> normals;
	bool hasUVs;
	bool hasNormals;

	OBJModel();

	IndexedModel LoadOBJ(const std::string& fileName);

	IndexedModel ToIndexedModel();
private:
	unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
	void CreateOBJFace(const std::string& line);

	Vector2D ParseOBJVec2(const std::string& line);
	Vector3D ParseOBJVec3(const std::string& line);
	OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};


#endif // OBJLOADER2_H_INCLUDED