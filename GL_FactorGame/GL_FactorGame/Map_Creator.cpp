#include "Map_Creator.h"


Map_Creator::Map_Creator(void)
{
	DimensionObject = vec3(4.5);
	Base_FactorDistance_BetweenTile = DimensionObject[1];
	BaseScale = 2;
	BaseOffset = vec3(0.0f,0.0f,0.0f);
}


Map_Creator::~Map_Creator(void)
{
}

void Map_Creator::SetBase_Position(vec3 Position)
{
	this->BaseOffset = Position;
}

vec3 Map_Creator::Get_Initial_TilePosition(int i, int j)
{
	return vec3 ( j * Base_FactorDistance_BetweenTile,
				  -i * Base_FactorDistance_BetweenTile,
				  0.0f);
}

bool Map_Creator::IsCollide(vec3 PositionObject, vec3 PosPlayer, vec3 DimensionObject)
{
	float DistanceX = abs(PositionObject[0] - PosPlayer[0]); 
	float DistanceY = abs(PositionObject[1] - PosPlayer[1]); 
	float DistanceZ = abs(PositionObject[2] - PosPlayer[2]); 
	OnTopOf = false;

	if(DistanceX < DimensionObject[0] && DistanceY < DimensionObject[1] && DistanceZ < DimensionObject[2])
	{
		//cout << DistanceX << " " << DistanceY << " " << DistanceZ << " " << endl;
		OnTopOf = (PosPlayer[1] > PositionObject[1] && DistanceY > 2.5);

		return true;
	}
	return false;
}

vec3 Map_Creator::Set_Tile_Position(vec3 Initial_TilePosition)
{
	Initial_TilePosition[0] += Base_mv_matrix[3][0];
	Initial_TilePosition[1] += Base_mv_matrix[3][1];
	Initial_TilePosition[2] += Base_mv_matrix[3][2];
	return Collision_Helper::Get_projected_Position(Initial_TilePosition);
}

bool Map_Creator::CollideWithBlock(vec3 Position, Model_Factory Models_factory)
{
	int Index = 0;
	int i = 0, j = 0;
	vec3 Final_TilePosition;
	vec3 Initial_TilePosition;
	vec3 Final_PlayerPosition;

	while(i < 20)
	{
		while(j < 20)
		{
			Index += 3;
			if(Content[Index] != TypeContent::T_Nothing && Content[Index]!= TypeContent::T_Saw)
			{
				Final_PlayerPosition = Collision_Helper::Get_projected_Position(Position);
				StaticHandle::mv_matrix = translate(Final_PlayerPosition);
				//Models_factory.Draw_Models(Models_factory.ModelType::Cube,StaticHandle::mv_matrix,mv_location,Load_Image::Type_Image::Leaf,rendering_program); 

				Initial_TilePosition = Get_Initial_TilePosition(i,j);
				Final_TilePosition = Set_Tile_Position(Initial_TilePosition);
				
				StaticHandle::mv_matrix = translate(Final_TilePosition) * scale(BaseScale);

				if(IsCollide(Final_TilePosition,Final_PlayerPosition,DimensionObject))
				{
					//cout << "Collide with " << i << " " << j <<endl;
					return true;
				}

				//Models_factory.Draw_Models(Models_factory.ModelType::Cube,StaticHandle::mv_matrix,mv_location,Load_Image::Type_Image::Circuit,rendering_program); 
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
	vec3 Initial_TilePosition = Get_Initial_TilePosition(i,j);

	StaticHandle::mv_matrix = translate(Initial_TilePosition); 
	
	StaticHandle::mv_matrix *= Base_mv_matrix;
	
	if(Content[Index] != 0)
		glUniformMatrix4fv(StaticHandle::mv_location, 1, GL_FALSE, StaticHandle::mv_matrix);

	switch(Content[Index])
	{
	case 0:
		/* Nothing In map*/ 
		break;
	case 1:
		glUniform1i(glGetUniformLocation(StaticHandle::rendering_program, "textureSelect"), 1);
		break;
	case 2:
		glUniform1i(glGetUniformLocation(StaticHandle::rendering_program, "textureSelect"), 2);
		break;
	case 3:
		glUniform1i(glGetUniformLocation(StaticHandle::rendering_program, "textureSelect"), 0);
		break;
	}
}

void Map_Creator::Load(string FileName)
{
	Load_Image::generate_Map(FileName,Content);
	int Index = 0;
	Base_mv_matrix = translate(BaseOffset) * scale(BaseScale);

	vec3 SawPosition;
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			Index+= 3;
			if(Content[Index] == TypeContent::T_Saw)
			{
				cout << endl << "Saw at " << i << " , " << j;
				SawPosition = Set_Tile_Position(Get_Initial_TilePosition(i,j));
				//-1 -22.5 -19.80/ 17 -40.50 -19.80/ 3.50 -81 -19.80
			}
		}
	}

	TabSaw[0] = Saw(vec3(-1    , -22.5 , -19.80), vec2(1,0));
	TabSaw[1] = Saw(vec3( 17   , -40.50, -19.80), vec2(0,1));
	TabSaw[2] = Saw(vec3( 3.50 , -81   , -19.80), vec2(1,0));
}

void Map_Creator::UpdateAndDraw(Drawing_Manager drawing_manager,Model_Factory Models_factory,float GameSpeed)
{ 
	int Index = 0;
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			Index+= 3;
			SetTexture(i,j,Index);
			if(Content[Index] != TypeContent::T_Nothing && Content[Index] != TypeContent::T_Saw) 
			{
				Models_factory.Draw_Models(Models_factory.ModelType::Cube,Load_Image::Type_Image::Leaf); 
			}
		}
	}

	for(int i = 0; i < 3; i++)
	{
		TabSaw[i].Update();
		TabSaw[i].Draw(drawing_manager);
	}
}