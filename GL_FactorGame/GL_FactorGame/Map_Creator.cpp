#include "Map_Creator.h"


Map_Creator::Map_Creator(void)
{
}


Map_Creator::~Map_Creator(void)
{
}

Map_Creator::Map_Creator(int mv_location, int rendering_program)
{
	this->rendering_program = rendering_program;
	this->mv_location = mv_location;
}

void Map_Creator::SetTexture(int i, int j, int Index)
{
	mv_matrix = translate((float)j * 4.50f,(float)-i * 4.50f, -20.0f) *
		scale(2.0f,2.0f,2.0f);

	if(Content[Index] != 0)
		glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);

	switch(Content[Index])
	{
	case 0:
		/* Nothing In map*/ 
		break;
	case 1:
		glUniform1i(glGetUniformLocation(rendering_program, "textureSelect"), 1);
		break;
	case 2:
		glUniform1i(glGetUniformLocation(rendering_program, "textureSelect"), 2);
		break;
	case 3:
		glUniform1i(glGetUniformLocation(rendering_program, "textureSelect"), 0);
		break;
	}
}

void Map_Creator::Load(string FileName)
{
	Load_Image::generate_Map(FileName,Content);
}

void Map_Creator::UpdateAndDraw(Model_Factory Models_factory,float GameSpeed)
{
	int Index = 0;
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			Index+= 3;
			SetTexture(i,j,Index);
			if(Content[Index] != 0) Models_factory.Draw_Models(Models_factory.ModelType::Cube,mv_matrix,mv_location,Load_Image::Type_Image::Leaf,rendering_program); 
		}
	}
}