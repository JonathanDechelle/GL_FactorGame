#pragma once
#include "Drawing_Manager.h"
#include "Collision_Helper.h"

class Trampoline
{
public:
	Trampoline(void);
	~Trampoline(void);
	Trampoline(vec3 Position);
	void Update(Player player);
	void Draw(Drawing_Manager drawing_Manager);
	vec3 Position;
};

