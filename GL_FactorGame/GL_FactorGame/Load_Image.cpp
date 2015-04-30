#include "Load_Image.h"
#define  RED 85
#define BLACK 0

#define LEAF_FLOOR 1
#define SAND_FLOOR 2
#define WOODBOX_FLOOR 3
#define SAW 4
#define TRAMPOLINE 5

int Load_Image::rendering_program;
void Load_Image::Initialize(int new_rendering_program)
{
	rendering_program = new_rendering_program;
}

void Load_Image::generate_texture(string FileName)
{
	int Width, Height, channel;
	unsigned char* image = SOIL_load_image(FileName.c_str(), &Width, &Height, &channel, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}

void Load_Image::generate_Map(string FileName, unsigned int* &Map_TileType)
{
	int Width, Height, channel;
	unsigned char* image = SOIL_load_image(FileName.c_str(), &Width, &Height, &channel, SOIL_LOAD_RGB);
	int Index;
	int IndexChannel = 0;
	unsigned int SommeChannel = 0;
	Map_TileType = new unsigned int[Width * Height * 3];

	for (Index = 0; Index < Width * Height * 3; Index++)
	{
		Map_TileType[Index] = image[Index];
		if(Index % Width == 0)	cout << endl;
		
		//cout << Map_TileType[Index];
	}

	//cout << endl << endl;
	for (Index = 1; Index < Width * Height * 3; Index++)
	{
		if(Index  % Width == 0)	
			cout << endl;

		if(Index % 3 == 0)
		{
			if(image[Index - 3] == 255 && 
			   image[Index - 2] == 255 &&
			   image[Index - 1] == 255)
				Map_TileType[Index] = 0;
			else
			{
				float TrueColor = image[Index - 3] + image[Index - 2] + image[Index - 1];
				TrueColor /= 3;

				if(TrueColor == RED)
				{
					if(image[Index - 3] > 0)
					{
						Map_TileType[Index] = SAW;
					}
					else if(image[Index - 2] > 0)
					{
						Map_TileType[Index] = TRAMPOLINE;
					}
				}
				else if(TrueColor == BLACK)
					Map_TileType[Index] = SAND_FLOOR;
				else
					Map_TileType[Index] = LEAF_FLOOR;
			}
			
			IndexChannel = 0;
			SommeChannel = 0;
			cout << Map_TileType[Index];
		}
		else
			cout << "-";

		
		////if(Index % Width == 0) cout << endl;
		SommeChannel += image[Index];
		IndexChannel++;
	}
}

void Load_Image::generate_texture(string FileName,GLuint* textures, int Index)
{
	int Width, Height;
	unsigned char* image = SOIL_load_image(FileName.c_str(), &Width, &Height, 0, SOIL_LOAD_RGB);

	glActiveTexture(GL_TEXTURE0 + Index);
	glBindTexture(GL_TEXTURE_2D, textures[Index]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Load_Image::set_UniformTexture(string FileName, int Index)
{
	//Take file name and substract type of file and name Uniform tex + FileName;
	FileName.erase(FileName.length() - 4,4);
	string UniformName = "tex";
	UniformName.append(FileName);
	glUniform1i(glGetUniformLocation(rendering_program, UniformName.c_str()), Index);
}
