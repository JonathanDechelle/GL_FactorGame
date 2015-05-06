#include "Saw.h"


Saw::Saw(void)
{
	
}

Saw::Saw(vec3 Position)
{
	this->Position = Position;
	this->StartPosition = Position;
	this->Speed = 0.1;
	this->Direction = vec2(0);
	Radius = 10;
	Sens = 1;
}

Saw::Saw(vec3 Position, vec2 Direction)
{
	this->Position = Position;
	this->StartPosition = Position;
	this->Direction = Direction;
	this->Speed = 0.1;
	Radius = 10;
	Sens = 1;
}

Saw::~Saw(void)
{

}

void Saw::Update()
{
	vec3 Vector_Distance = StartPosition - Position;
	float Distance = length(Vector_Distance);

	if(Distance < Radius)
		Position += (vec3(Direction,0.0) * Speed * Sens);
	else
	{
		StartPosition = Position;
		Sens *= -1;
	}
}

void Saw::Draw(Drawing_Manager drawing_Manager)
{
	drawing_Manager.DrawSaw(Position);
}
