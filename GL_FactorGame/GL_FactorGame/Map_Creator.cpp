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
	Base_FactorDistance_BetweenTile = 4.50f;
	BaseScale = 2;
	BaseOffset = vec3(0.0f,0.0f,0.0f);
	DimensionObject = vec3(4,4,4);
}

void Map_Creator::SetBase_Position(vec3 Position)
{
	BaseOffset[0] = Position[0];
	BaseOffset[1] = Position[1];
	BaseOffset[2] = Position[2];
}

bool IsCollide(vec3 PositionObject, vec3 PosPlayer, vec3 DimensionObject)
{
	float DistanceX = abs(PositionObject[0] - PosPlayer[0]); 
	float DistanceY = abs(PositionObject[1] - PosPlayer[1]); 
	float DistanceZ = abs(PositionObject[2] - PosPlayer[2]); 

	//cout << DistanceX << " " << DistanceY << " " << DistanceZ << " " << endl;
	return (DistanceX < DimensionObject[0] && DistanceY < DimensionObject[1] && DistanceZ < DimensionObject[2]);
}

vec3 SetMap_Position(int i, int j, float DistanceBetweenTile, float Scale, vec3 Offset)
{
	vec3 Position;
	Position[0] =  j * DistanceBetweenTile;
	Position[1] = -i * DistanceBetweenTile;
	Position[2] =  1.0f;

	Position *= Scale;

	Position[0] += Offset[0];
	Position[1] += Offset[1];
	Position[2] += Offset[2];

	return Position;
}

bool Map_Creator::CollideWithBlock(vec3 Position)
{
	int Index = 0;
	int i = 0, j = 0;
	vec3 MapTilePosition;

	while(i < 20)
	{
		while(j < 20)
		{
			Index += 3;
			if(Content[Index] != 0)
			{
				MapTilePosition = SetMap_Position(i,j,Base_FactorDistance_BetweenTile,BaseScale,BaseOffset);

				if(IsCollide(MapTilePosition,Position,DimensionObject)) return true;
				return false;
			}
			j++;
		}
		i++;
		j = 0;
	}
	return false;
}

void Map_Creator::SetTexture(int i, int j, int Index)
{
	mv_matrix = translate( j * Base_FactorDistance_BetweenTile,
						  -i * Base_FactorDistance_BetweenTile,
						  0.0f);

	mapBase_mv_matrix = translate( BaseOffset[0],
								   BaseOffset[1],
								   BaseOffset[2]) *
						scale(BaseScale);

	mv_matrix *= mapBase_mv_matrix;

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
			if(Content[Index] != 0) 
			{
				Models_factory.Draw_Models(Models_factory.ModelType::Cube,mv_matrix,mv_location,Load_Image::Type_Image::Leaf,rendering_program); 
				return;
			}
		}
	}
}