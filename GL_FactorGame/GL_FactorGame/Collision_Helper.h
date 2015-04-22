#pragma once
#include "vmath.h"
#include "Model_Factory.h"
#include "Load_Image.h"

class Collision_Helper
{
public:
	static vec3 Get_projected_Position(vec3 Position);
	static bool IsCollide(vec3 PositionObject, vec3 PosPlayer, vec3 DimensionObject);
	static void RenderCollision(Model_Factory Models_factory,vec3 Position);
	static bool OnTopOf;
};

