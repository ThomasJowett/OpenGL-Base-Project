#include "OBJLoader.h"
#include <sys\stat.h>
/*
long FileLenghth(int f)
{
	
	struct stat buf;
	fstat(f, &buf);
	return(buf.st_size);
	
	long t = 1;
		return t;
	
}
*/
MeshData OBJLoader :: LoadOBJ(char * p_filename)
{
	MeshData mesh; 

	Vector3D vertex;
	TexCoord UV;
	Vector3D normal;
	
	FILE * infile = fopen(p_filename, "rb");
	if (infile == NULL) {
		printf("Impossible to open the file %s\n", p_filename);
		return mesh;
	}
	
	unsigned int vertexIndices = 0, normalsIndices = 0, uvIndices = 0, facesIndices = 0;

	while (true) {
		char lineHeader[128];
		//read the first word of the line
		int res = fscanf(infile, "%s", lineHeader);
		if (res == EOF)
			break;
		//else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			fscanf(infile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			mesh.vertices.push_back(vertex);
			vertexIndices++;
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			fscanf(infile, "%f %f\n", &UV.u, &UV.v);
			mesh.texCoords.push_back(UV);
			//mesh.texCoord[uvIndices] = UV;
			uvIndices++;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			fscanf(infile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			mesh.normals.push_back(normal.GetNormalized());
			normalsIndices++;
		}
		else if (strcmp(lineHeader, "f") == 0) {
			Triangle vertexIndex, uvIndex, normalIndex;
			char backslash;
			int matches = fscanf(infile, "%d %c %d %c %d %d %c %d %c %d %d %c %d %c %d\n", &vertexIndex.a, &backslash, &uvIndex.a, &backslash, &normalIndex.a, &vertexIndex.b, &backslash, &uvIndex.b, &backslash, &normalIndex.b, &vertexIndex.c, &backslash, &uvIndex.c, &backslash, &normalIndex.c);
			//printf("%d %d %d %d %d %d %d %d %d\n",vertexIndex.a, uvIndex.a, normalIndex.a, vertexIndex.b, uvIndex.b, normalIndex.b, vertexIndex.c, uvIndex.c, normalIndex.c);
			if (matches != 15) {
				printf("%i\n",matches);
				printf("File can't be read by this parser\n");
				system("pause");
				return mesh;
			}
			vertexIndex.a--;
			vertexIndex.b--;
			vertexIndex.c--;

			uvIndex.a--;
			uvIndex.b--;
			uvIndex.c--;

			normalIndex.a--;
			normalIndex.b--;
			normalIndex.c--;

			mesh.triangles.push_back(vertexIndex);
			
			mesh.texCoordIndices.push_back(uvIndex);

			mesh.normalsIndices.push_back(normalIndex);

			facesIndices ++;
		}
		else if (strcmp(lineHeader, "g") == 0) {
			fscanf(infile, "%s", &mesh.name);
		}
	}
	mesh.vertices_qty = vertexIndices;
	mesh.triangles_qty = facesIndices;
	fclose(infile);
	
	return mesh;
}
