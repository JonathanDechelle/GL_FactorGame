#include "Drawing_Manager.h"


Drawing_Manager::Drawing_Manager(void)
{
}


Drawing_Manager::~Drawing_Manager(void)
{
}

Drawing_Manager::Drawing_Manager(Model_Factory Models_factory)
{
	this->Models_factory = Models_factory;
	BaseFactor = 10000;
	ColorEyes[0] = Green;
	ColorEyes[1] = Red;
}

void Drawing_Manager::Draw_Torus(float AngleStart)
{
	StaticHandle::mv_matrix = translate(PlayerPosition[0],PlayerPosition[1],PlayerPosition[2]) *
		rotate(AngleStart, 0.0f, 0.0f, 1.0f) *
		rotate(PlayerRotation[0] * BaseFactor,0.0f,0.0f,1.0f) * 
		rotate(-PlayerRotation[2] * BaseFactor,1.0f,0.0f,0.0f) *
		rotate(CurrentTime * GameSpeed/25 * (BaseFactor/100), 0.0f, 1.0f, 0.0f) * 
		scale(0.85f,0.85f,0.85f);

	Models_factory.Draw_Models(Models_factory.ModelType::Torus,Load_Image::Type_Image::BlueCircuit);
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

	StaticHandle::mv_matrix = translate(PlayerPosition[0],PlayerPosition[1],PlayerPosition[2]) *
		rotate( PlayerRotation[0] * BaseFactor,0.0f,0.0f,1.0f) *
		rotate( AngleStart,1.0f,0.0f,0.0f) *
		rotate(-PlayerRotation[2] * BaseFactor,1.0f,0.0f,0.0f);

	if(EyeColor == 0) 	EyeTexture = Load_Image::Type_Image::GreenEye;
	else				EyeTexture = Load_Image::Type_Image::RedEye;

	Models_factory.Draw_Models(Models_factory.ModelType::HalfBall,EyeTexture);
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

void Drawing_Manager::DrawSaw(vec3 Position)
{
	StaticHandle::mv_matrix = translate(Position) * 
		rotate(CurrentTime * GameSpeed/5 * (BaseFactor/100), 0.0f, 0.0f, 1.0f)  *
		rotate(90.0f, 1.0f, 0.0f, 0.0f);

	Models_factory.Draw_Models(Models_factory.ModelType::Saw,Load_Image::Metal);
}

void Drawing_Manager::DrawTrampoline(vec3 Position,float size)
{
	StaticHandle::mv_matrix = translate(Position) * scale(size,size,size);

	Models_factory.Draw_Models(Models_factory.ModelType::Trampoline,Load_Image::RedCircuit);
}

void Drawing_Manager::DrawLifeBar(vec3 PlayerPosition, float PlayerLife, float PlayerMaxLife)
{
	StaticHandle::mv_matrix = translate(vec3(PlayerPosition[0],PlayerPosition[1],-19.0f) + vec3(0.0f,14.0f,5.0f)) * 
		//rotate(90.0f, 1.0f, 0.0f, 0.0f) * content
		rotate(0.0f,1.0f,0.0f,0.0f) * 
		scale(14.0f,7.0f,10.0f);

	float LifeRatio = PlayerLife / PlayerMaxLife;

	Models_factory.Draw_Models(Models_factory.ModelType::LifeBar_Frame,Load_Image::WoodBox);
	Models_factory.Draw_Models(Models_factory.ModelType::LifeBar_Content,Load_Image::LifeBarContent,LifeRatio);
}

void Drawing_Manager::RenderCollision(vec3 Position)
{
	StaticHandle::mv_matrix = translate(Position) * scale(2.0f);
	Models_factory.Draw_Models(Models_factory.ModelType::Cube,Load_Image::Type_Image::Leaf); 
}

void Drawing_Manager::Update(Player player)
{
	PlayerPosition = player.Position;
	PlayerRotation = player.Rotation;
	PlayerLife = player.Life;
	PlayerMaxLife = player.MaxLife;
}

void Drawing_Manager::Draw(float CurrentTime,float GameSpeed)
{
	this->CurrentTime = CurrentTime;
	this->GameSpeed = GameSpeed;

	DrawPlayer();
	DrawLifeBar(PlayerPosition,PlayerLife,PlayerMaxLife);
}

