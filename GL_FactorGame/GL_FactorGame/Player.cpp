#include "Player.h"

Player::~Player(void)
{
}

Player::Player()
{
	Speed = 0.000005f;
	Friction = 0.0000005f;
	OnTopOf = false;

	for(int i = 0; i < 3; i++)
	{
		Position[i] = 0;
		Next_Position[i] = 0;
		Distance[i] = 0;
	}
	
	BaseFactor = 10000;
	Fake_Floor = -20;
	Falling = 0;
	BasePosition = Position;
	gravity = 0.000015f;
	//BaseJump = 1.05f; //off sector
	BaseJump = 0.85f; //on sector
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
	Next_Position[1] += 0.15f;
	Falling = -BaseJump;
	keyboard.SetActive(' ',false);
}

void Player::ApplyGravity(float gravity)
{
	Falling += gravity;
	Position[1] -= Falling;
}

void Player::Manage_Keyboard(Keyboard keyboard)
{
	this->keyboard = keyboard;
	if(keyboard.IsHold('W')) Next_Position[Z]-= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('S')) Next_Position[Z]+= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('A')) Next_Position[X]-= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('D')) Next_Position[X]+= Speed * StaticHandle::GameSpeed;
}

void Player::Udpate(Keyboard keyboard, Map_Creator Map, Model_Factory Models_factory)
{
	IsCollide = false;
	Manage_Keyboard(keyboard);
	

	for (int Axe = 0; Axe < Z + 1; Axe++) 
	{
		Distance[Axe] = abs(Next_Position[Axe]);

		if(Axe != Y)	ApplyFriction(Distance[Axe],Friction * StaticHandle::GameSpeed);
		else			ApplyFriction(Distance[1],Friction * 3 *  StaticHandle::GameSpeed);

		Check_Limit(Next_Position[Axe],Distance[Axe]);
	}
	
	Futur_Position = Position  + Next_Position;
	
	StaticHandle::PlayerPosition = Futur_Position;

	IsCollide = Map.CollideWithBlock(Models_factory);
	OnTopOf = Collision_Helper::OnTopOf;

	if(!OnTopOf)
	{
		if(IsCollide)
		{
			Falling *= -0.50f;
			Next_Position *= -0.75f;
			//if(keyboard.IsPressed(' ')) Jump();
		}
	}
	else
	{
		Next_Position[Y] = 0;
		Falling *= -0.50f;
		//Falling = 0;
		Position[Y] = Last_Position[1];
		if(keyboard.IsPressed(' ')) Jump();
	}

	
	Position += Next_Position;

	Last_Position = Position;
	Rotation = (Next_Position - Position) * (Friction * BaseFactor) + (BasePosition * Friction * BaseFactor);
	
	ApplyGravity(gravity * StaticHandle::GameSpeed);
	StaticHandle::PlayerIsHurt = false;
}

