#include "stdafx.h"
#include "Material.h"
#include <stdlib.h>
#include <stdio.h>


namespace QEngine
{
	MaterialInfo Material::woodMaterial {
		{ 0.20, 0.20, 0.20, 1.00 },
		{ 0.50, 0.50, 0.50, 1.00 },
		{ 0.00, 0.00, 0.00, 1.00 },
		10.00 
	};

	MaterialInfo Material::whiteShineyMaterial = {
		{ 1.00, 1.00, 1.00, 1.00 },
		{ 1.00, 1.00, 1.00, 1.00 },
		{ 1.00, 1.00, 1.00, 1.00 },
		100.00
	};

	MaterialInfo Material::whiteMattMaterial = {
		{ 1.00, 1.00, 1.00, 1.00 },
		{ 1.00, 1.00, 1.00, 1.00 },
		{ 1.00, 1.00, 1.00, 1.00 },
		10.00
	};

	MaterialInfo Material::brassMaterial = {
		{ 0.33, 0.22, 0.03, 1.00 },
		{ 0.78, 0.57, 0.11, 1.00 },
		{ 0.99, 0.91, 0.81, 1.00 },
		27.80
	};

	MaterialInfo Material::redPlasticMaterial = {
		{ 0.30, 0.00, 0.00, 1.00 },
		{ 1.00, 0.00, 0.00, 1.00 },
		{ 0.80, 0.60, 0.60, 1.00 },
		20.00
	};

	Material::~Material() { }

	Material::Material(Shader* shader, const char* textureFileName, MaterialInfo properties)
	{
		this->shader	 = shader;
		this->properties = properties;

		if (textureFileName != NULL)
		{
			BITMAPINFOHEADER bitmapInfoHeader;

			// Array to hold bitmap data
			unsigned char* bitmapData;

			// Load the bitmap data from the file
			bitmapData = LoadBitmapFile(textureFileName, &bitmapInfoHeader);

			if (bitmapData != NULL)
			{
				// Create a unique ID for a texture and assign it to txtEarth
				glGenTextures(1, &textureId);

				// Creates the texture object and sets it as the current OpenGL texture
				glBindTexture(GL_TEXTURE_2D, textureId);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

				// Move texture from system memory to OpenGL texture memory
				glTexImage2D(GL_TEXTURE_2D,	0, GL_RGB, bitmapInfoHeader.biWidth, bitmapInfoHeader.biHeight,	0, GL_RGB, GL_UNSIGNED_BYTE, bitmapData);
				free(bitmapData);

				textureEnabled = true;
			}
			else
				textureEnabled = false; // Invalid bitmap data from file
		}
		else
			textureEnabled = false; // Invalid texture path/filename
	}

	// Returns a pointer to the bitmap image of the bitmap specified
	//  by filename. Also returns the bitmap header information.
	//  No support for 8-bit bitmaps.
	unsigned char * Material::LoadBitmapFile(const char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
	{
		FILE* filePtr;
		BITMAPFILEHEADER bitmapFileHeader;

		unsigned char* bitmapImage;
		unsigned char tempRGB;

		int imageIdx = 0;

		// open filename in "read binary" mode
		errno_t err = fopen_s(&filePtr, filename, "rb");

		if (err != NULL)
			return NULL;

		// read the bitmap file header
		fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);

		// read the bitmap information header
		fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);

		// move file pointer to beginning of bitmap data
		fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

		// allocate enough memory for the bitmap image data
		bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

		// read in the bitmap image data
		fread(bitmapImage, 1, bitmapInfoHeader->biSizeImage, filePtr);

		// swap the R and B values to get RGB since the bitmap color format is in BGR
		// Added -3 to stop Heap Error being generated when freeing bitmap  in VS2012
		for (imageIdx = 0; imageIdx < (bitmapInfoHeader->biSizeImage - 3); imageIdx += 3)
		{
			tempRGB = bitmapImage[imageIdx];
			bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
			bitmapImage[imageIdx + 2] = tempRGB;
		}

		// close the file and return the bitmap image data
		fclose(filePtr);

		return bitmapImage;
	}

	void Material::Apply()
	{
		// Select shader to apply to meshes
		glUseProgram(shader->GetProgram());

		if (textureEnabled)
		{
			// Get a handle for the uniform var within the shader
			GLint texture0 = glGetUniformLocation(shader->GetProgram(), "texture0");

			// Pass texture unit zero to shader. Note:increment this to 1,2 etc for additional textures
			glUniform1i(texture0, 0);

			// Activate the texture unit
			glActiveTexture(GL_TEXTURE0);

			// Bind the texture to the texture unit
			glBindTexture(GL_TEXTURE_2D, textureId);
		}
		else
			glDisable(GL_TEXTURE_2D);
	}

	Shader * Material::GetShader()
	{
		return shader;
	}

	MaterialInfo Material::GetProperties()
	{
		return properties;
	}
}