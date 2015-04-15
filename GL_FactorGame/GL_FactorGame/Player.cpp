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
	Fake_Floor = 0;
	Falling = 0;
	BasePosition = Position;
}

void Player::Udpate(Keyboard keyboard)
{
	if(keyboard.IsHold('W')) Next_Position[2]-= Speed;
	if(keyboard.IsHold('S')) Next_Position[2]+= Speed;
	if(keyboard.IsHold('A')) Next_Position[0]-= Speed;
	if(keyboard.IsHold('D')) Next_Position[0]+= Speed;

	Distance[0] = abs(Next_Position[0]);
	Distance[2] = abs(Next_Position[2]);
	
	if(Distance[0] > 0) Distance[0] -= Friction;
	else Distance[0] = 0;
	if(Distance[2] > 0) Distance[2] -= Friction;
	else Distance[2] = 0;

	if(Next_Position[0] < 0) 
		Next_Position[0] = Distance[0] * -1;
	else					
		Next_Position[0] = Distance[0];

	if(Next_Position[2] < 0) 
		Next_Position[2] = Distance[2] * -1;
	else					
		Next_Position[2] = Distance[2];

	Position += Next_Position;
	Rotation = -(Position - Next_Position) * (Friction * BaseFactor) + (BasePosition * Friction * BaseFactor);

	if(Position[1] > Fake_Floor) 
	{
		float gravity = 0.000015f;
		Falling += gravity;
		Position[1] -= Falling;
	}
	else
	{
		Position[1] = Fake_Floor;
		Falling = 0;
		if(keyboard.IsPressed(' ')) 
		{
			Position[1] += 2;
			Falling = -0.0125f;
			keyboard.SetActive(' ',false);
		}
	}
}

void Player::Draw(Model_Factory Models_factory, float CurrentTime)
{
	//TORUS EFFECT (5 torus same rotation only angle start is different)
	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate(Rotation[0] * BaseFactor,0.0f,0.0f,1.0f) * 
		rotate(-Rotation[2] * BaseFactor,1.0f,0.0f,0.0f) *
		rotate(CurrentTime * (BaseFactor/100), 0.0f, 1.0f, 0.0f) * 
		scale(0.85f,0.85f,0.85f);

	Models_factory.Draw_Models(Models_factory.ModelType::Torus,mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program);

	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate(45.0f, 0.0f, 0.0f, 1.0f) * 
		rotate(Rotation[0] * BaseFactor,0.0f,0.0f,1.0f) * 
		rotate(-Rotation[2] * BaseFactor,1.0f,0.0f,0.0f) *
		rotate(CurrentTime * (BaseFactor/100), 0.0f, 1.0f, 0.0f) * 
		scale(0.85f,0.85f,0.85f);

	Models_factory.Draw_Models(Models_factory.ModelType::Torus,mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program);

	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate(90.0f, 0.0f, 0.0f, 1.0f) * 
		rotate(Rotation[0] * BaseFactor,0.0f,0.0f,1.0f) * 
		rotate(Rotation[2] * BaseFactor,1.0f,0.0f,0.0f) *
		rotate(CurrentTime * (BaseFactor/100), 0.0f, 1.0f, 0.0f) * 
		scale(0.85f,0.85f,0.85f);

	Models_factory.Draw_Models(Models_factory.ModelType::Torus,mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program);


	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate(135.0f, 0.0f, 0.0f, 1.0f) * 
		rotate(Rotation[0] * BaseFactor,0.0f,0.0f,1.0f) * 
		rotate(Rotation[2] * BaseFactor,1.0f,0.0f,0.0f) *
		rotate(CurrentTime * (BaseFactor/100), 0.0f, 1.0f, 0.0f) * 
		scale(0.85f,0.85f,0.85f);

	Models_factory.Draw_Models(Models_factory.ModelType::Torus,mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program);

	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate( Rotation[0] * BaseFactor,0.0f,0.0f,1.0f) *
		rotate( 90.0f,1.0f,0.0f,0.0f) *
		rotate(-Rotation[2] * BaseFactor,1.0f,0.0f,0.0f);

	Models_factory.Draw_Models(Models_factory.ModelType::HalfBall,mv_matrix,mv_location,Load_Image::Type_Image::Or,rendering_program);

	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate( Rotation[0] * BaseFactor,0.0f,0.0f,1.0f) *
		rotate( -90.0f,1.0f,0.0f,0.0f) *
		rotate(-Rotation[2] * BaseFactor,1.0f,0.0f,0.0f);

	Models_factory.Draw_Models(Models_factory.ModelType::HalfBall,mv_matrix,mv_location,Load_Image::Type_Image::Or,rendering_program);

}