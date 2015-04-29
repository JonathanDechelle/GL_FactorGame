#pragma once
#include "Light.h"

class StaticHandle
{
public:
	static GLuint rendering_program;
	static GLuint mv_location;
	static GLuint proj_location;
	static GLuint lookAtMatrix_Location;
	static float CurrentTime;
	static float Speed;
	static float GameSpeed;
	static mat4 mv_matrix;
	static mat4 proj_matrix;
	static mat4 MapBase_matrix;
	static vec3 PlayerPosition;
	static vec3 PlayerStartPosition;
	static bool PlayerRebound;
	static bool PlayerIsHurt;
	static float PlayerLife;
	static float PlayerMaxLife;
	vec3 PlayerDirectionDamage;
	static Light light;
};

