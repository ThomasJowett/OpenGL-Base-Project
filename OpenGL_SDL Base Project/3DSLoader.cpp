#include <stdio.h>
#include <stdlib.h>
#include "Commons.h"
#include "3DSLoader.h"
#include <sys\stat.h>

long FileLength(int f)
{
	struct stat buf;
	fstat(f, &buf);
	return(buf.st_size);
}

size_t getFilesize(const char* filename) {
	struct stat st;
	if (stat(filename, &st) != 0) {
		return 0;
	}
	return st.st_size;
}

MeshData Load3DS(char *p_filename)
{
	MeshData mesh;

	Vector3D vertex;
	TexCoord UV;
	Vector3D normal;

	int i; //Index variable
	FILE *infile; //File pointer

	unsigned short chunkId, s_tempA, s_tempB, s_tempC; //Chunk identifier unsigned
	unsigned int chunkLength; //Chunk length
	unsigned char name; // Char variable
	unsigned short size; //Number of elements in each chunk

	unsigned short faceFlag; //Flag that stores some face information

	if ((infile = fopen(p_filename, "rb")) == NULL)
	{
		printf("Impossible to open the file \n", p_filename);
		return mesh; //Open file
	}

	while (ftell(infile) < getFilesize(p_filename)) //Loop to scan the whole file
	{
		//std::cout << "File Size: " << getFilesize(p_filename) << std::endl;
		fread(&chunkId, 2, 1, infile); //Read the chunk header
		fread(&chunkLength, 4, 1, infile); //Read the length of the chunk
		//system("pause");//uncomment this line if you want to go through each chunk

		switch (chunkId)
		{
			//-----------------MAIN3DS ---------------
			// Description: Main chunk, contains all the other chunks 
			// Chunk ID: 4d4d // Chunk Length: 0 + sub chunks 
			//-------------------------------------
		case 0x4d4d:
			break;
			//-----------------EDIT3DS ----------- 
			// Description: 3D Editor chunk, objects layout info 
			// Chunk ID: 3d3d (hex) // Chunk Length: 0 + sub chunks 
			//-------------------------------------
		case 0x3d3d:
			break;
			//---------------EDIT_OBJECT ---------------
			// Description: Object block, info for each object 
			// Chunk ID: 4000 (hex) 
			// Chunk Length: len(object name) + sub chunks 
			//-------------------------------------
		case 0x4000:
			i = 0;
			do
			{
				fread(&name, 1, 1, infile);
				mesh.name[i] = name;
				std::cout << name;
				i++;
			} while (name != '\0' && i < 20);
			std::cout<< std::endl;
			break;
			//---------------OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info 
			// Chunk ID: 4100 (hex) // Chunk Length: 0 + sub chunks 
			//-------------------------------------
		case 0x4100:
			break;
			//---------------TRI_VERTEXL ---------------
			// Description: Vertices list 
			// Chunk ID: 4110 (hex) 
			// Chunk Length: 1 x unsigned short (number of vertices) 
			// + 3 x float (vertex coordinates) x (number of vertices) 
			// + sub chunks 
			//-------------------------------------
		case 0x4110:
			fread(&size, sizeof(unsigned short), 1, infile);
			mesh.vertices_qty = size;
			std::cout << "Number of vertices: " << mesh.vertices_qty << std::endl;

			for (i = 0; i < size; i++)
			{
				fread(&vertex.x, sizeof(float), 1, infile);
				fread(&vertex.y, sizeof(float), 1, infile);
				fread(&vertex.z, sizeof(float), 1, infile);

				mesh.vertices.push_back(vertex);
			}
			break;
			//---------------TRI_FACEL1 ----------------
			// Description: triangles (faces) list 
			// Chunk ID: 4120 (hex) 
			// Chunk LengtH: 1 x unsigned short (number of triangles) 
			// + 3 x unsigned short (triangle points) x (number of triangles) 
			// + sub chunks 
			//-------------------------------------
		case 0x4120:
			fread(&size, sizeof(unsigned short), 1, infile);
			mesh.triangles_qty = size;

			for (i = 0; i < size; i++)
			{
				Triangle vertexIndex;
				fread(&s_tempA, sizeof(unsigned short), 1, infile);
				
				fread(&s_tempB, sizeof(unsigned short), 1, infile);
				
				fread(&s_tempC, sizeof(unsigned short), 1, infile);
				
				vertexIndex = { s_tempA, s_tempB, s_tempC };

				mesh.texCoordIndices.push_back(vertexIndex);
				mesh.triangles.push_back(vertexIndex);
				fread(&faceFlag, sizeof(unsigned short), 1, infile);
			}
			break;
			//-------------TRI_MAPPINGCOORDS ------------
			// Description: Vertices list 
			// Chunk ID: 4140 (hex) 
			// Chunk Length: 1 x unsigned short (number of mapping points) 
			// + 2 x float (mapping coordinates) x (number of mapping points) 
			// + sub chunks //-------------------------------------
		case 0x4140:
			fread(&size, sizeof(unsigned short), 1, infile);
			for (i = 0; i < size; i++)
			{
				fread(&UV.u, sizeof(float), 1, infile);
				fread(&UV.v, sizeof(float), 1, infile);
				mesh.texCoords.push_back(UV);
			}
			break;
			//-----------Skip unknown chunks ------------
			//We need to skip all the chunks that currently we don't use 
			//We use the chunk lenght information to set the file pointer 
			//to the same level next chunk 
			//-------------------------------------
		default:
			fseek(infile, chunkLength - 6, SEEK_CUR);
		}
	}
	fclose(infile);//Close the file

	for (int i = 0; i<mesh.triangles_qty; ++i)
	{
		Triangle& face = mesh.triangles[i];
		Triangle normalIndex;
		normalIndex.a = i;
		normalIndex.b = i;
		normalIndex.c = i;

		// compute face normal
		Vector3D p0 = mesh.vertices[int(face.a)];
		Vector3D p1 = mesh.vertices[int(face.b)];
		Vector3D p2 = mesh.vertices[int(face.c)];
		Vector3D normal = normal.Cross((p0 - p1), (p0 - p2));

		mesh.normals.push_back(normal.GetNormalized());
		mesh.normalsIndices.push_back(normalIndex);
	}
	return(mesh);
}