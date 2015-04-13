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
    Position[1] = 0;
	Position[2] = -15;

	Last_Position = Position;
	Next_Position[0] = 0;
	Next_Position[1] = 0;
	Next_Position[2] = 0;
}

void Player::Udpate(Keyboard keyboard)
{
	if(keyboard.IsHold('W')) Next_Position[1]+= Speed;
	if(keyboard.IsHold('S')) Next_Position[1]-= Speed;
	if(keyboard.IsHold('A')) Next_Position[0]-= Speed;
	if(keyboard.IsHold('D')) Next_Position[0]+= Speed;

	Distance = abs(Next_Position[0]);
	Distance -= Friction;

	if(Next_Position[0] < 0) 
		Next_Position[0] = Distance * -1;
	else					
		Next_Position[0] = Distance;

	Position += Next_Position;
	Rotation = -(Position - Next_Position) * (Friction * 10000);
}

void Player::Draw(Model_Factory Models_factory, float CurrentTime)
{
	//mv_matrix = translate(Position[0],Position[1],Position[2]) *
	//	rotate(0.0f,0.0f,0.0f,0.0f) *
	//	rotate(0.0f,0.0f,0.0f,0.0f);

	//Models_factory.Draw_Models(Models_factory.ModelType::Torus,mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program);

	mv_matrix = translate(Position[0],Position[1],Position[2]) *
		rotate(Rotation[0] * 10000,0.0f,0.0f,1.0f) *
		rotate(0.0f,0.0f,0.0f,0.0f);

	Models_factory.Draw_Models(Models_factory.ModelType::Ball,mv_matrix,mv_location,Load_Image::Type_Image::Or,rendering_program);

}
