#include "Saw.h"


Saw::Saw(void)
{
	
}

Saw::Saw(vec3 Position)
{
	this->Position = Position;
}

Saw::~Saw(void)
{

}

void Saw::Update()
{

}

void Saw::Draw(Drawing_Manager drawing_Manager)
{
	drawing_Manager.DrawSaw(Position);
}
