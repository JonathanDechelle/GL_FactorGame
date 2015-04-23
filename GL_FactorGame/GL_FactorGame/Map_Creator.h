#pragma once
#include "Load_Image.h"
#include "Model_Factory.h"
#include "Saw.h"
#include "StaticHandle.h"
#include "Collision_Helper.h"

class Map_Creator
{
public:
	Map_Creator(void);
	~Map_Creator(void);
	Map_Creator(int mv_location, int rendering_program);
	void Load(string FileName);
	void SetTexture(int i, int j, int Index);
	void SetBase_Position(vec3 Position);
	void UpdateAndDraw(Drawing_Manager drawing_manager,Model_Factory Models_factory,float GameSpeed);
	bool IsCollide(vec3 PositionObject, vec3 PosPlayer, vec3 DimensionObject);
	bool CollideWithBlock(vec3 Position,Model_Factory Models_factory);
	vec3 Set_Tile_Position(vec3 Initial_TilePosition);
	vec3 Get_Initial_TilePosition(int i, int j);

	unsigned int* Content;
	mat4 Base_mv_matrix;
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

