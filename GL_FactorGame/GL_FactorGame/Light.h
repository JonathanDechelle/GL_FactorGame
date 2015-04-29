#pragma once
#include "vmath.h"
#include "..\Include\glew.h"
#include "..\Include\glut.h"

class Light
{
public:
	Light(void);
	~Light(void);
	vec4 Light_Direction;
	float Light_Brightness;
	float Light_Radius;
	GLint lightDir_location;
	GLint lightBrightness_location;
	GLint lightRadius_location;

	void Initialize(int renderingProgram);
	void Update(float CurrentTime);
};

