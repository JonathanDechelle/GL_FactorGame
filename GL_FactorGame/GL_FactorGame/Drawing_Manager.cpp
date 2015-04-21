#include "Drawing_Manager.h"


Drawing_Manager::Drawing_Manager(void)
{
}


Drawing_Manager::~Drawing_Manager(void)
{
}

Drawing_Manager::Drawing_Manager(Model_Factory Models_factory,int mv_location, int rendering_program)
{
	this->Models_factory = Models_factory;
	BaseFactor = 10000;
	ColorEyes[0] = Green;
	ColorEyes[1] = Red;
	this->mv_location = mv_location;
	this->rendering_program = rendering_program;
}

void Drawing_Manager::Draw_Torus(float AngleStart)
{
	mv_matrix = translate(PlayerPosition[0],PlayerPosition[1],PlayerPosition[2]) *
		rotate(AngleStart, 0.0f, 0.0f, 1.0f) *
		rotate(PlayerRotation[0] * BaseFactor,0.0f,0.0f,1.0f) * 
		rotate(-PlayerRotation[2] * BaseFactor,1.0f,0.0f,0.0f) *
		rotate(CurrentTime * GameSpeed/25 * (BaseFactor/100), 0.0f, 1.0f, 0.0f) * 
		scale(0.85f,0.85f,0.85f);

	Models_factory.Draw_Models(Models_factory.ModelType::Torus,mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program);
}

void Drawing_Manager::Draw_AllTorus(int nb)
{
	float Ecart = 45.0f;
	float Angle;

	for (int i = 0; i < nb; i++)
	{
		Angle = i * Ecart;
		Draw_Torus(Angle);
	}
};

void Drawing_Manager::Draw_Eye(float AngleStart,int NoEye)
{
	int EyeColor = ColorEyes[NoEye];
	int EyeTexture;

	mv_matrix = translate(PlayerPosition[0],PlayerPosition[1],PlayerPosition[2]) *
		rotate( PlayerRotation[0] * BaseFactor,0.0f,0.0f,1.0f) *
		rotate( AngleStart,1.0f,0.0f,0.0f) *
		rotate(-PlayerRotation[2] * BaseFactor,1.0f,0.0f,0.0f);

	if(EyeColor == 0) 	EyeTexture = Load_Image::Type_Image::GreenEye;
	else				EyeTexture = Load_Image::Type_Image::RedEye;

	Models_factory.Draw_Models(Models_factory.ModelType::HalfBall,mv_matrix,mv_location,EyeTexture,rendering_program);
}

void Drawing_Manager::Draw_AllEyes(int nb)
{
	float Ecart = 90.0f;
	float Angle;

	for (int i = 1; i < nb + 1; i++)
	{
		if(i % 2 == 1)
			Angle = Ecart * i;
		else
			Angle = -(Ecart * (i-1));
		Draw_Eye(Angle, (i - 1));
	}
}

void Drawing_Manager::DrawPlayer()
{
	Draw_AllTorus(4);
	Draw_AllEyes(2);
}

void Drawing_Manager::Draw(float CurrentTime,float GameSpeed)
{
	this->CurrentTime = CurrentTime;
	this->GameSpeed = GameSpeed;

	DrawPlayer();
}
