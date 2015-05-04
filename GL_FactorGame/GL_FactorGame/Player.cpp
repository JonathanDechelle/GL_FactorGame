#include "Player.h"

Player::~Player(void)
{
}

void Player::Reset()
{
	Speed = 0.000005f;
	Friction = 0.0000005f;
	
	for(int i = 0; i < 3; i++)
	{
		Next_Position[i] = 0;
		Distance[i] = 0;
		BasePosition[i] = 0;
	}

	BaseFactor = 10000;
	Fake_Floor = -20;
	Falling = 0;
	gravity = 0.000015f;
	BaseJump = 0.65f; //off sector
	//BaseJump = 0.65f; //on sector

	StartPosition = vec3(0.0f,-22.0f,-19.0f);
	Position = StartPosition;
	Last_Position = Position;
	Futur_Position = Position;
	IsHurt = false;
	Rebound = false;
	OnTopOf = false;
	IsCollide = false;
	Life = 100;
	MaxLife = 100;
}

Player::Player()
{
	Reset();
}

void Player::SetBase_Position(vec3 Position)
{
	this->Position = Position;
}

void ApplyFriction(float &Distance, float Friction)
{
	if(Distance > 0)	Distance -= Friction;
	else				Distance = 0;
}

void Check_Limit(float &Next_Position, float Distance)
{
	if(Next_Position < 0) 	Next_Position = Distance * -1;
	else					Next_Position = Distance;
}

void Player::Jump()
{
	Next_Position[1] += 0.01f;
	Falling -= BaseJump;
	keyboard.SetActive(' ',false);
}

void Player::ApplyGravity(float gravity)
{
	Falling += gravity;
	Position[1] -= Falling;
}

vec3 Player::GetNextPosition()
{
	for (int Axe = 0; Axe < Z + 1; Axe++) 
	{
		Distance[Axe] = abs(Next_Position[Axe]);

		if(Axe != Y)	ApplyFriction(Distance[Axe],Friction * StaticHandle::GameSpeed);
		else			ApplyFriction(Distance[1],Friction * 3 *  StaticHandle::GameSpeed);

		Check_Limit(Next_Position[Axe],Distance[Axe]);
	}

	return Next_Position;
}

void Player::Manage_Keyboard(Keyboard keyboard)
{
	this->keyboard = keyboard;
	if(keyboard.IsHold('W')) Next_Position[Z]-= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('S')) Next_Position[Z]+= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('A')) Next_Position[X]-= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('D')) Next_Position[X]+= Speed * StaticHandle::GameSpeed;
}

void Player::Udpate(Keyboard keyboard, Model_Factory Models_factory)
{
	if(IsHurt)
	{
		Jump();
		Life -= 2;
	}

	if (Rebound)
	{
		Jump();
	}

	if(Life < 0)
	{
		Reset();
		SetBase_Position(StartPosition);
		Life = MaxLife;
	}

	if(IsCollide)
	{
		Position = Last_Position;
	}

	Manage_Keyboard(keyboard);
	if(!OnTopOf)
	{
		if(IsCollide)
		{
			Falling *= -0.50f;
			Next_Position *= -0.75f;
		}
	}
	else
	{
		Next_Position[Y] = 0;
		Falling *= -0.50f;
		if(keyboard.IsPressed(' ')) Jump();
	}

	Next_Position = GetNextPosition();
	Position += Next_Position;

	Rotation = (Next_Position - Position) * (Friction * BaseFactor) + (BasePosition * Friction * BaseFactor);
	
	Futur_Position = Position  + Next_Position;
	Futur_Position[Y] -= Falling;
	Last_Position = Position;

	ApplyGravity(gravity * StaticHandle::GameSpeed);

	IsHurt = false;
	Rebound = false;
}

