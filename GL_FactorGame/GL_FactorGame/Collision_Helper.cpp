#include "Collision_Helper.h"



bool Collision_Helper::IsCollide(vec3 PositionObject, Player player, vec3 DimensionObject)
{
	float DistanceX = abs(PositionObject[0] - player.Position[0]); 
	float DistanceY = abs(PositionObject[1] - player.Position[1]); 
	float DistanceZ = abs(PositionObject[2] - player.Position[2]); 
	player.OnTopOf = false;

	if(DistanceX < DimensionObject[0] && DistanceY < DimensionObject[1] && DistanceZ < DimensionObject[2])
	{
		//cout << DistanceX << " " << DistanceY << " " << DistanceZ << " " << endl;
		player.OnTopOf = (player.Position[1] > PositionObject[1] && DistanceY > 2.5);
		
		return true;
	}
	return false;
}

bool Collision_Helper::CollideWithBlock(Map_Creator map,Player player)
{
	
	int Index = 0;
	int i = 0, j = 0;
	vec3 Final_TilePosition;
	vec3 Initial_TilePosition;
	vec3 OldPlayerPosition;
	bool resultOfCollide;
	
	while(i < 20)
	{
		while(j < 20)
		{
			Index += 3;
			if(map.Content[Index] != map.TypeContent::T_Nothing && map.Content[Index]!= map.TypeContent::T_Saw && map.Content[Index] != map.TypeContent::T_Trampoline)
			{
				OldPlayerPosition = player.Position;
				player.Position = StaticHandle::Get_projected_Position(player.Position);
				//Collision_Helper::RenderCollision(Models_factory,Final_PlayerPosition);
				
				Initial_TilePosition = map.Get_Initial_TilePosition(i,j);
				Final_TilePosition = map.Set_Tile_Position(Initial_TilePosition);
				
				
				resultOfCollide = IsCollide(Final_TilePosition,player,map.DimensionObject);
				player.Position = OldPlayerPosition;

				if(resultOfCollide)
				{
					//cout << "Collide with " << i << " " << j <<endl;
					return true;
				}

				//Collision_Helper::RenderCollision(Models_factory,Final_TilePosition); 
				
			}
			j++;
		}
		i++;
		j = 0;
	}

	return false;
}

void Collision_Helper::Update(Map_Creator map, Player player)
{
	player.IsCollide = CollideWithBlock(map,player);
}

/*
void Collision_Helper::RenderCollision(Model_Factory Models_factory,vec3 Position)
{
	StaticHandle::mv_matrix = translate(Position) * scale(2.0f);
	Models_factory.Draw_Models(Models_factory.ModelType::Cube,Load_Image::Type_Image::Leaf); 
}
*/