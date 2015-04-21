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
	void Get_proj_Matrix(mat4 proj_matrix);
	void UpdateAndDraw(Model_Factory Models_factory,float GameSpeed);
	bool IsCollide(vec3 PositionObject, vec3 PosPlayer, vec3 DimensionObject);
	bool CollideWithBlock(vec3 Position,Model_Factory Models_factory);
	vec3 Set_Tile_Position(vec3 Initial_TilePosition);
	vec3 Set_Player_Position(vec3 Initial_PlayerPosition);
	vec3 Get_Initial_TilePosition(int i, int j);
	vec3 Get_projected_Position(vec3 Position);

	unsigned int* Content;
	int rendering_program;
	mat4 mv_matrix;
	mat4 Base_mv_matrix;
	mat4 proj_matrix;
	int mv_location;
	vec3 BaseOffset;
	float Base_FactorDistance_BetweenTile;
	float BaseScale;
	vec3 DimensionObject;
	bool OnTopOf;
};

