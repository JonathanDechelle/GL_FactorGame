#pragma once
#include "Keyboard.h"
#include "vmath.h"
#include "Model_Factory.h"
#include "Load_Image.h"

class Player
{
public:
	Player(void);
	~Player(void);
	Player(int mv_location, int rendering_program);
	void Udpate(Keyboard keyboard);
	void Draw(Model_Factory Models_factory,float CurrentTime);
	
	mat4 mv_matrix;
	int mv_location;
	int rendering_program;
	vec3 Position;
};

