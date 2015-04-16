#pragma once
#include "Load_Image.h"
#include "..\Include\glew.h"
#include "..\Include\glut.h"
#include "vmath.h"
#include "Model_Factory.h"

class Map_Creator
{
public:
	Map_Creator(void);
	~Map_Creator(void);
	Map_Creator(int mv_location, int rendering_program);
	void Load(string FileName);
	void SetTexture(int i, int j, int Index);
	void UpdateAndDraw(Model_Factory Models_factory,float GameSpeed);
	unsigned int* Content;
	int rendering_program;
	mat4 mv_matrix;
	int mv_location;
};

