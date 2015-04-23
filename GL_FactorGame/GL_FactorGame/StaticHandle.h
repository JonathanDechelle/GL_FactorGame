#pragma once
#include "..\Include\glew.h"
#include "..\Include\glut.h"

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
};

