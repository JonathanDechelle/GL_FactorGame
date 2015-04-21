#pragma once
#include "Keyboard.h"
#include "vmath.h"
#include "Model_Factory.h"
#include "Load_Image.h"
#include "Map_Creator.h"

class Player
{
public:
	enum EyeColor
	{
		Green,Red
	};
	Player(void);
	~Player(void);
	Player(int mv_location, int rendering_program);
	void Udpate(Keyboard keyboard,float GameSpeed,Map_Creator Map, Model_Factory Models_factory);
	void SetBase_Position(vec3 Position);
	void Draw(Model_Factory Models_factory,float CurrentTime, float GameSpeed);
	void Draw_Torus(Model_Factory Models_factory,float CurrentTime, float GameSpeed,float AngleStart);
	void Draw_AllTorus(int nb,Model_Factory Models_factory, float CurrentTime, float GameSpeed);
	void Draw_Eye(Model_Factory Models_factory,float CurrentTime, float GameSpeed,float AngleStart,int NoEye);
	void Draw_AllEyes(int nb,Model_Factory Models_factory, float CurrentTime, float GameSpeed);
	void Jump();
	void ApplyGravity(float gravity);

	mat4 mv_matrix;
	int mv_location;
	int rendering_program;
	vec3 Position;
	vec3 Next_Position;
	vec3 Last_Position;
	vec3 Rotation;
	vec3 Distance;
	vec3 BasePosition;
	float Speed;
	float Friction;
	float BaseJump;
	float BaseFactor;
	int ColorEyes[2];
	Keyboard keyboard;
	float JumpHeight;

	//Gravity Section
	float gravity;
	float Falling;
	float Fake_Floor; //will change in futur

	bool Collision_Test; //Test only
};

