#pragma once
#include "Drawing_Manager.h"

class Saw
{
public:
	Saw(void);
	Saw(vec3 Position);
	Saw(vec3 Position, vec2 Direction);
	~Saw(void);
	void Update();
	void Draw(Drawing_Manager drawing_Manager);
	vec3 Position;
	vec3 StartPosition;
	vec2 Direction;
	int Sens;
	float Radius;
	float Speed;
};

