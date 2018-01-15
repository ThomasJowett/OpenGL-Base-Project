#include "Texture2D.h"
#include <iostream>
#include <fstream>

using namespace::std;

Texture2D::Texture2D()
{
	//_ID++;
}


Texture2D::~Texture2D()
{
	glDeleteTextures(1, &_ID);
}

bool Texture2D::Load(char* path, int width, int height)
{
	char* tempTextureData;
	int fileSize;
	ifstream inFile;
	_width = width;
	_height = height;
	inFile.open(path, ios::binary);

	if (!inFile.good())
	{
		cerr << "Can't open texture file " << path << endl;
		return false;
	}

	inFile.seekg(0, ios::end); // Seek to end of file
	fileSize = (int)inFile.tellg(); //	Get current position in file - The End, this givesus the total file size
	tempTextureData = new char[fileSize]; // Create a new array to store the data (of the correct size)
	inFile.seekg(0, ios::beg); // Seek back to beginning of the file.
	inFile.read(tempTextureData, fileSize); // Read in all the data.
	inFile.close(); //Close the file.

	cout << path << " : loaded.\n";

	//glGenTextures(1, &textureID);

	glGenTextures(1, &_ID); //Get the next texture ID
	glBindTexture(GL_TEXTURE_2D, _ID); //Bind the texture to the ID.
	//glBindTexture(GL_TEXTURE_2D, textures[_ID]);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, tempTextureData);

	delete[] tempTextureData; // Clear up the data - we don't need it anymore
	return true;
}
