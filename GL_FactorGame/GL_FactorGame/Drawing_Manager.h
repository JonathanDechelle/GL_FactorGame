#pragma once
#include "Model_Factory.h"
#include "Load_Image.h"

class Drawing_Manager
{
public:
	Drawing_Manager(void);
	~Drawing_Manager(void);
	Drawing_Manager(Model_Factory Models_factory);
	void DrawPlayer();
	void DrawLifeBar();
	void DrawSaw(vec3 Position);
	void Draw_Torus(float AngleStart);
	void Draw_AllTorus(int nb);
	void Draw_Eye(float AngleStart,int NoEye);
	void Draw_AllEyes(int nb);
	void Draw(float CurrentTime,float GameSpeed);
	float BaseFactor;
	float GameSpeed;
	float CurrentTime;
	int ColorEyes[2];
	vec3 PlayerPosition;
	vec3 PlayerRotation;

	Model_Factory Models_factory;
	enum EyeColor
	{
		Green,Red
	};
};

