#pragma once
#include "vmath.h"
#include "Player.h"
#include "Map_Creator.h"
#include "Load_Image.h"
#include "Drawing_Manager.h"
class Collision_Helper
{
public:
	static bool IsCollide(vec3 PositionObject, Player &player, vec3 DimensionObject, bool OnTopOfCheck);
	static bool CollideWithBlock(Map_Creator map,Player &player,Drawing_Manager drawing_manager);
	static void Update(Map_Creator map, Player &player,Drawing_Manager drawing_manager);
};

