#pragma once
#include "Keyboard.h"
#include "vmath.h"
#include "Model_Factory.h"

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
	void Udpate(Keyboard keyboard, Model_Factory Models_factory);
	void SetBase_Position(vec3 Position);
	void Reset();
	void Jump();
	void ApplyGravity(float gravity);
	vec3 GetNextPosition();

	vec3 Position;
	vec3 Next_Position;
	vec3 Last_Position;
	vec3 Futur_Position;
	vec3 Rotation;
	vec3 Distance;
	float Speed;
	float Friction;
	float BaseJump;
	float BaseFactor;
	Keyboard keyboard;
	float JumpHeight;
	vec3 BasePosition;
	vec3 StartPosition;
	bool IsHurt;
	bool Rebound;
	float Life;
	float MaxLife;


	//Gravity Section
	float gravity;
	float Falling;
	float Fake_Floor; //will change in futur

	bool IsCollide; //Test only
};

