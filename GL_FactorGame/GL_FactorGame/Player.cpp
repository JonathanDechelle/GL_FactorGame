#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}

Player::Player(int mv_location, int rendering_program)
{
	this->mv_location = mv_location;
	this->rendering_program = rendering_program;
	Speed = 0.000005f;
	Friction = 0.0000005f;
	Position[0] = 0;
    Position[1] = 10;
	Position[2] = -15;

	Next_Position[0] = 0;
	Next_Position[1] = 0;
	Next_Position[2] = 0;

	Distance[0] = 0;
	Distance[1] = 0;
	Distance[2] = 0;

	BaseFactor = 10000;
	Fake_Floor = -5;
	Falling = 0;
	BasePosition = Position;
	gravity = 0.000015f;

	ColorEyes[0] = Green;
	ColorEyes[1] = Red;
}

void ApplyFriction(float &Distance, float Friction)
{
	if(Distance > 0)	Distance -= Friction;
	else				Distance = 0;
}

void Player::Jump()
{
	Position[1] += 2;
	Falling = -0.35f;
	keyboard.SetActive(' ',false);
}

void Player::ApplyGravity(float LimiteY, float gravity)
{
	if(Position[1] > LimiteY) 
	{
		Falling += gravity;
		Position[1] -= Falling;
	}
	else
	{
		Position[1] = LimiteY;
		Falling = 0;
		if(keyboard.IsPressed(' ')) Jump();
	}
}

void Player::Udpate(Keyboard keyboard, float GameSpeed, Map_Creator Map)
{
	Collision_Test = false;
	this->keyboard = keyboard;
	if(keyboard.IsHold('W')) Next_Position[2]-= Speed * GameSpeed;
	if(keyboard.IsHold('S')) Next_Position[2]+= Speed * GameSpeed;
	if(keyboard.IsHold('A')) Next_Position[0]-= Speed * GameSpeed;
	if(keyboard.IsHold('D')) Next_Position[0]+= Speed * GameSpeed;

	Distance[0] = abs(Next_Position[0]);
	Distance[2] = abs(Next_Position[2]);
	
	ApplyFriction(Distance[0],Friction * GameSpeed);
	ApplyFriction(Distance[2],Friction * GameSpeed);

	if(Next_Position[0] < 0) 	Next_Position[0] = Distance[0] * -1;
	else						Next_Position[0] = Distance[0];

	if(Next_Position[2] < 0) 	Next_Position[2] = Distance[2] * -1;
	else						Next_Position[2] = Distance[2];

	Position += Next_Position;
	Rotation = (Next_Position - Position) * (Friction * BaseFactor) + (BasePosition * Friction * BaseFactor);

	ApplyGravity(Fake_Floor,gravity * GameSpeed);
	Collision_Test = Map.CollideWithBlock(Position);
}

void Player::Draw_Torus(Model_Factory Models_factory, float CurrentTime, float GameSpeed,float AngleStart)
{
	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate(AngleStart, 0.0f, 0.0f, 1.0f) *
		rotate(Rotation[0] * BaseFactor,0.0f,0.0f,1.0f) * 
		rotate(-Rotation[2] * BaseFactor,1.0f,0.0f,0.0f) *
		rotate(CurrentTime * GameSpeed/25 * (BaseFactor/100), 0.0f, 1.0f, 0.0f) * 
		scale(0.85f,0.85f,0.85f);

	Models_factory.Draw_Models(Models_factory.ModelType::Torus,mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program);
}

void Player::Draw_AllTorus(int nb,Model_Factory Models_factory, float CurrentTime, float GameSpeed)
{
	float Ecart = 45.0f;
	float Angle;

	for (int i = 0; i < nb; i++)
	{
		Angle = i * Ecart;
		Draw_Torus(Models_factory,CurrentTime,GameSpeed,Angle);
	}
};

void Player::Draw_Eye(Model_Factory Models_factory,float CurrentTime, float GameSpeed,float AngleStart,int NoEye)
{
	int EyeColor = ColorEyes[NoEye];
	int EyeTexture;

	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate( Rotation[0] * BaseFactor,0.0f,0.0f,1.0f) *
		rotate( AngleStart,1.0f,0.0f,0.0f) *
		rotate(-Rotation[2] * BaseFactor,1.0f,0.0f,0.0f);

	if(EyeColor == 0) 	EyeTexture = Load_Image::Type_Image::GreenEye;
	else				EyeTexture = Load_Image::Type_Image::RedEye;

	Models_factory.Draw_Models(Models_factory.ModelType::HalfBall,mv_matrix,mv_location,EyeTexture,rendering_program);
}

void Player::Draw_AllEyes(int nb,Model_Factory Models_factory, float CurrentTime, float GameSpeed)
{
	float Ecart = 90.0f;
	float Angle;

	for (int i = 1; i < nb + 1; i++)
	{
		if(i % 2 == 1)
			Angle = Ecart * i;
		else
			Angle = -(Ecart * (i-1));
		Draw_Eye(Models_factory,CurrentTime,GameSpeed,Angle, (i - 1));
	}
}

void Player::Draw(Model_Factory Models_factory, float CurrentTime, float GameSpeed)
{
	
	if(!Collision_Test)
	{
		Draw_AllTorus(4,Models_factory,CurrentTime,GameSpeed);
		Draw_AllEyes(2,Models_factory,CurrentTime,GameSpeed);
	}
	else
	{	
		Draw_AllTorus(1,Models_factory,CurrentTime,GameSpeed);
	}
}
