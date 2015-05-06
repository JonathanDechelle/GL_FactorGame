#pragma once
#include <iostream>
#include "..\Include\SOIL.h"
#include "..\Include\glew.h"
#include "..\Include\glut.h"
using namespace std;

class Load_Image
{
public:
	static int rendering_program;
	static void Initialize(int new_rendering_program);
	static void generate_texture(string FileName);
	static void generate_Map(string FileName,  unsigned int* &Map_TileType);
	static void generate_texture(string FileName,GLuint* textures, int Index);
	static void set_UniformTexture(string FileName, int Index);
	static enum Type_Image{
		BlueCircuit,
		Or,
		Metal,
		GreenEye,
		RedEye,
		Leaf,
		Sand,
		WoodBox,
		LifeBarContent,
		RedCircuit,
	};
};

