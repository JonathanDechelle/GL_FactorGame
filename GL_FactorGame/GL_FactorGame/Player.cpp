#include "Player.h"

Player::~Player(void)
{
}

void Player::Reset_DefaultPosition()
{
	Start_Position = vec3(0.0f,-22.0f,-19.0f);
	Position = Start_Position;
	Last_Position = Start_Position;
	Futur_Position = Start_Position;
}

void Player::Reset_CurrentState()
{
	IsHurt = false;
	Rebound = false;
	OnTopOf = false;
	IsCollide = false;
}

void Player::Reset_DefaultHealth(float value)
{
	MaxLife = value;
	Life = MaxLife;
}

void Player::Reset_DefaultAll()
{
	Falling = 0;
	for(int i = 0; i < 3; i++)
	{
		Next_Move[i] = 0;
		Distance[i] = 0;
	}

	Reset_DefaultPosition();
	Reset_CurrentState();
	Reset_DefaultHealth(100);
}

void Player::Set_Constants()
{
	Speed = 0.000005f;
	Friction = 0.0000005f;
	BaseFactor = 10000;
	gravity = 0.000015f;
	BaseJump = 0.65f;
}

Player::Player()
{
	Set_Constants();
	Reset_DefaultAll();
}

void Player::Set_BasePosition(vec3 Position)
{
	this->Position = Position;
}

void Apply_Friction(float &Distance, float Friction)
{
	if(Distance > 0)	Distance -= Friction;
	else				Distance = 0;
}

void Apply_Sign(float &Next_MoveAxe, float Distance)
{
	if(Next_MoveAxe < 0) 	Next_MoveAxe = -Distance;
	else					Next_MoveAxe =	Distance;
}

void Player::Jump()
{
	Falling -= BaseJump;
	keyboard.SetActive(' ',false);
}

void Player::Apply_Gravity(float gravity)
{
	Falling += gravity;
	Position[Y] -= Falling;
}

vec3 Player::Get_NextMove()
{
	for (int Axe = 0; Axe < Z + 1; Axe++) 
	{
		Distance[Axe] = abs(Next_Move[Axe]);
		Apply_Friction(Distance[Axe],Friction * StaticHandle::GameSpeed);
		Apply_Sign(Next_Move[Axe],Distance[Axe]);
	}

	return Next_Move;
}

void Player::Manage_Keyboard(Keyboard keyboard)
{
	this->keyboard = keyboard;
	if(keyboard.IsHold('W')) Next_Move[Z]-= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('S')) Next_Move[Z]+= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('A')) Next_Move[X]-= Speed * StaticHandle::GameSpeed;
	if(keyboard.IsHold('D')) Next_Move[X]+= Speed * StaticHandle::GameSpeed;
}

void Player::Apply_KeyboardAction(Keyboard keyboard)
{
	Manage_Keyboard(keyboard);
	Next_Move = Get_NextMove();
	Position += Next_Move;
}

vec3 Player::Get_FuturPosition()
{
	Futur_Position = Position  + Next_Move;
	Futur_Position[Y] -= Falling;
	return Futur_Position;
}

vec3 Player::Get_PastPosition()
{
	return Position;
}

vec3 Player::Get_NormalPosition()
{
	//Cross product
	vec3 Normal;
	vec3 Floor = vec3(1,0,0);
	vec3 NextMove_Normalized = normalize(Next_Move);

	Normal[0] = (Floor[1] * NextMove_Normalized[2]) - (Floor[2] * NextMove_Normalized[1]);
	Normal[1] = (Floor[2] * NextMove_Normalized[0]) - (Floor[0] * NextMove_Normalized[2]);
	Normal[2] = (Floor[0] * NextMove_Normalized[1]) - (Floor[1] * NextMove_Normalized[0]);

	return Normal;
}

vec3 Player::Get_ReflectionPosition()
{
	vec3 Rin = Position;
	vec3 Rreflect;
	vec3 N = Get_NormalPosition();

	Rreflect = Rin - ((2.0f * N) * Rin)* N;

	return Rreflect;
}

void Player::Remove_Life(float value)
{
	Life -= value;
}

void Player::Set_NextBehaviour()
{
	if(IsHurt || Rebound)
	{
		Jump();
		if(IsHurt)	Remove_Life(2);
	}
	else
	{
		if(IsCollide)
		{
			Position = Last_Position;
			Falling *= -0.50f;

			if(!OnTopOf)
			{
				/* Reflexion here prochain code*/
				Next_Move *= -0.75f;
				Position += Next_Move;

				//Position += Get_ReflectionPosition();
			}
		}

		if(OnTopOf)
			if(keyboard.IsPressed(' ')) Jump();
	}
}

void Player::Udpate(Keyboard keyboard, Model_Factory Models_factory)
{
	Set_NextBehaviour();
	Apply_KeyboardAction(keyboard);

	Rotation = (Next_Move - Position) * (Friction * BaseFactor);

	Futur_Position = Get_FuturPosition();
	Last_Position = Get_PastPosition();
	
	Apply_Gravity(gravity * StaticHandle::GameSpeed);

	Life < 0 ? Reset_DefaultAll() : Reset_CurrentState(); 
}

