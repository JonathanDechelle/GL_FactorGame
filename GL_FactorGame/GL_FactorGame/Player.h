#pragma once
#include "Keyboard.h"
#include "vmath.h"
#include "Model_Factory.h"
#include "Load_Image.h"
#include "Map_Creator.h"
#include "Collision_Helper.h"

#define X 0
#define Y 1
#define Z 2

class Player
{
public:
	~Player(void);
	Player();
	Player(vec3 Position);
	void Manage_Keyboard(Keyboard keyboard);
	void Udpate(Keyboard keyboard,Map_Creator Map, Model_Factory Models_factory);
	void SetBase_Position(vec3 Position);
	void Jump();
	void ApplyGravity(float gravity);

	vec3 Position;
	vec3 Next_Position;
	vec3 Last_Position;
	vec3 Futur_Position;
	vec3 Rotation;
	vec3 Distance;
	vec3 BasePosition;
	float Speed;
	float Friction;
	float BaseJump;
	float BaseFactor;
	Keyboard keyboard;
	float JumpHeight;
	bool OnTopOf;

	//Gravity Section
	float gravity;
	float Falling;
	float Fake_Floor; //will change in futur

	bool IsCollide; //Test only
};

