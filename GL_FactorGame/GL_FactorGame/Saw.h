#pragma once
#include "Drawing_Manager.h"

class Saw
{
public:
	Saw(void);
	~Saw(void);
	void Update();
	void Draw(Drawing_Manager drawing_Manager);
	vec3 Position;
};
