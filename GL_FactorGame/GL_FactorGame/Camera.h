#pragma once
#include "vmath.h"
#include "..\Include\glut.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);
	vec3 Position;
	vec3 center;
	vec3 Up;
	mat4 lookAt(vec3 eye, vec3 center, vec3 up);
	void Update();
	void MouseMove(int x, int y);
	mat4 lookAtMatrix_matrix;
	mat4 RotationMatrix_matrix;
	float LastX,LastY;
	float Yaw,Pitch;
	bool firstMouse;
};

