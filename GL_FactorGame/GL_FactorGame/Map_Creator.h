#pragma once
#include "Saw.h"
#include "Trampoline.h"

class Map_Creator
{
public:
	Map_Creator(void);
	~Map_Creator(void);
	void Load(string FileName);
	void SetTexture(int i, int j, int Index);
	void SetBase_Position(vec3 Position);
	void UpdateAndDraw(Drawing_Manager drawing_manager,Model_Factory Models_factory);
	//bool CollideWithBlock(Model_Factory Models_factory,vec3 PlayerPosition);
	vec3 Set_Tile_Position(vec3 Initial_TilePosition);
	vec3 Get_Initial_TilePosition(int i, int j);

	unsigned int* Content;
	vec3 BaseOffset;
	vec3 DimensionObject;
	float Base_FactorDistance_BetweenTile;
	float BaseScale;
	Saw TabSaw[10];
	Trampoline TabTrampo[10];

	enum TypeContent
	{
		T_Nothing,
		T_Leaf,
		T_Sand,
		T_WoodBox,
		T_Saw,
		T_Trampoline
	};
};

