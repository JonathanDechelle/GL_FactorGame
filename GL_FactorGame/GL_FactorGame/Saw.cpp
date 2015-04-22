#include "Saw.h"


Saw::Saw(void)
{
	Position = vec3(0,-22,-19);
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
