#pragma once
#include "Load_Image.h"
#include "..\Include\glew.h"
#include "..\Include\glut.h"
#include "vmath.h"
#include "Model_Factory.h"
#include "Saw.h"

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
	void UpdateAndDraw(Drawing_Manager drawing_manager,Model_Factory Models_factory,float GameSpeed);
	bool IsCollide(vec3 PositionObject, vec3 PosPlayer, vec3 DimensionObject);
	bool CollideWithBlock(vec3 Position,Model_Factory Models_factory);
	vec3 Set_Tile_Position(vec3 Initial_TilePosition);
	vec3 Set_Player_Position(vec3 Initial_PlayerPosition);
	vec3 Get_Initial_TilePosition(int i, int j);
	vec3 Get_projected_Position(vec3 Position);

	unsigned int* Content;
	int rendering_program;
	int mv_location;
	mat4 mv_matrix;
	mat4 Base_mv_matrix;
	mat4 proj_matrix;
	vec3 BaseOffset;
	vec3 DimensionObject;
	float Base_FactorDistance_BetweenTile;
	float BaseScale;
	bool OnTopOf;
	Saw TabSaw[10];

	enum TypeContent
	{
		T_Nothing,
		T_Leaf,
		T_Sand,
		T_WoodBox,
		T_Saw
	};
};

