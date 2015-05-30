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
	void Apply_KeyboardAction(Keyboard keyboard);
	void Udpate(Keyboard keyboard, Model_Factory Models_factory);
	void Set_NextBehaviour();
	void Remove_Life(float value);
	void Set_BasePosition(vec3 Position);
	void Set_Constants();
	void Reset_DefaultAll();
	void Reset_DefaultPosition();
	void Reset_CurrentState();
	void Reset_DefaultHealth(float value);
	void Jump();
	void Apply_Gravity(float gravity);
	vec3 Get_NextMove();
	vec3 Get_FuturPosition();
	vec3 Get_PastPosition();
	vec3 Get_NormalPosition();
	vec3 Get_ReflectionPosition();

	vec3 Position;
	vec3 Last_Position;
	vec3 Futur_Position;
	vec3 Start_Position;
	vec3 Next_Move;
	vec3 Rotation;
	vec3 Distance;
	float Speed;
	float Friction;
	float BaseJump;
	float BaseFactor;
	Keyboard keyboard;
	float JumpHeight;
	
	bool IsHurt;
	bool Rebound;
	float Life;
	float MaxLife;

	//Gravity Section
	float gravity;
	float Falling;
	
	bool IsCollide; 
	bool OnTopOf;
	float AngleCollision;
};

