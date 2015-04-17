#pragma once
#include "Keyboard.h"
#include "vmath.h"
#include "Model_Factory.h"
#include "Load_Image.h"
#include "Map_Creator.h"

class Player
{
public:
	Player(void);
	~Player(void);
	Player(int mv_location, int rendering_program);
	void Udpate(Keyboard keyboard,float GameSpeed,Map_Creator Map);
	void Draw(Model_Factory Models_factory,float CurrentTime, float GameSpeed);
	void Jump();
	void ApplyGravity(float LimiteY, float gravity);

	mat4 mv_matrix;
	int mv_location;
	int rendering_program;
	vec3 Position;
	vec3 Next_Position;
	vec3 Rotation;
	vec3 Distance;
	vec3 BasePosition;
	float Speed;
	float Friction;
	float BaseFactor;

	Keyboard keyboard;

	//Gravity Section
	float gravity;
	float Falling;
	float Fake_Floor; //will change in futur

	bool Collision_Test; //Test only
};

