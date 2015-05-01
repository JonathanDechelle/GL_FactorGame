#pragma once
#include "vmath.h"
#include "Player.h"
#include "Map_Creator.h"
#include "Load_Image.h"

class Collision_Helper
{
public:
	static bool IsCollide(vec3 PositionObject, Player player, vec3 DimensionObject);
	static bool CollideWithBlock(Map_Creator map,Player player);
	static void Update(Map_Creator map, Player player);
	//static void RenderCollision(Model_Factory Models_factory,vec3 Position);
};

