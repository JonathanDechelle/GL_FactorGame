#include "Trampoline.h"


Trampoline::Trampoline(void)
{
}


Trampoline::~Trampoline(void)
{
}

Trampoline::Trampoline(vec3 Position)
{
	this->Position = Position;
}

void Trampoline::Update()
{
	if(Collision_Helper::IsCollide(Position,StaticHandle::PlayerPosition,vec3(3)))
	{
		StaticHandle::PlayerRebound = true;
	}
}

void Trampoline::Draw(Drawing_Manager drawing_Manager)
{
	drawing_Manager.DrawTrampoline(Position,0.5f);
}


