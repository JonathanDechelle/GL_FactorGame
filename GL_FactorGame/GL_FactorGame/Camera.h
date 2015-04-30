#pragma once
#include "vmath.h"
#include "..\Include\glut.h"
#include "Keyboard.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);
	vec3 Position;
	vec3 center;
	vec3 Up;
	mat4 lookAt(vec3 eye, vec3 center, vec3 up);
	void Update(vec3 PlayerPosition);
	void Keyboard_Update(Keyboard keyboard);
	void MouseMove(int x, int y);
	void SetBasePosition(vec3 Position);
	mat4 lookAtMatrix_matrix;
	float LastX,LastY;
	float Yaw,Pitch;
	bool firstMouse;
	float CameraSpeed;
	vec3 BaseOffset;
};

