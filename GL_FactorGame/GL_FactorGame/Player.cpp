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
}

void Player::Udpate(Keyboard keyboard)
{

}

void Player::Draw(Model_Factory Models_factory, float CurrentTime)
{
	mv_matrix = translate(0.0f,0.0f,-15.0f) *
		rotate(0.0f,0.0f,0.0f,0.0f) *
		rotate(0.0f,0.0f,0.0f,0.0f);

	Models_factory.Draw_Models(Models_factory.ModelType::Torus,mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program);

	mv_matrix = translate(0.0f,0.0f,-15.0f) *
		rotate(0.0f,0.0f,0.0f,0.0f) *
		rotate(0.0f,0.0f,0.0f,0.0f);

	Models_factory.Draw_Models(Models_factory.ModelType::Ball,mv_matrix,mv_location,Load_Image::Type_Image::Or,rendering_program);

}
