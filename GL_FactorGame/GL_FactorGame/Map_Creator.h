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
	void SetBase_Position(vec3 Position);
	void UpdateAndDraw(Model_Factory Models_factory,float GameSpeed);
	bool CollideWithBlock(vec3 Position);
	unsigned int* Content;
	int rendering_program;
	mat4 mv_matrix;
	mat4 mapBase_mv_matrix;
	int mv_location;
	vec3 BaseOffset;
	float Base_FactorDistance_BetweenTile;
	float BaseScale;
	vec3 DimensionObject;
};

