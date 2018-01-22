#include "OBJLoader.h"
#include "Commons.h"
#include <sys\stat.h>
#include <string>

long FileLenghth(int f)
{
	struct stat buf;
	fstat(f, &buf);
	return(buf.st_size);
}

char LoadOBJ(obj_type_ptr p_object, char * p_filename)
{
	FILE * infile = fopen(p_filename, "rb");
	if (infile == NULL) {
		printf("Impossible to open the file %s\n", p_filename);
		return false;
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
			Vector3D vertex;
			fscanf(infile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			p_object->vertex[vertexIndices] = vertex;
			vertexIndices++;
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			TexCoord UV;
			fscanf(infile, "%f %f\n", &UV.u, &UV.v);
			//printf("%f %f \n", UV.u, UV.v);
			//system("pause");
			p_object->texCoord[uvIndices] = UV;
			uvIndices++;
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			Vector3D normal;
			fscanf(infile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			//printf("%f %f %f\n", normal.x, normal.y, normal.z);
			//system("pause");
			p_object->normals[normalsIndices] = normal.GetNormalized();
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
				return false;
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

			p_object->triangle[facesIndices] = vertexIndex;
			
			p_object->texCoordIndices[facesIndices] = uvIndex;

			p_object->normalsIndices[facesIndices] = normalIndex;

			facesIndices ++;
		}
		else if (strcmp(lineHeader, "g") == 0) {
			fscanf(infile, "%s", &p_object->name);
		}
	}
	p_object->vertices_qty = vertexIndices;
	p_object->triangles_qty = facesIndices;
	fclose(infile);
	return true;
}
