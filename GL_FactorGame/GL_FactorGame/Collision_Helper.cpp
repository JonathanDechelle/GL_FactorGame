#include "Collision_Helper.h"

bool Collision_Helper::IsCollide(vec3 PositionObject, Player &player, vec3 DimensionObject, bool OnTopOfCheck = false)
{
	float DistanceX = abs(PositionObject[0] - player.Futur_Position[0]); 
	float DistanceY = abs(PositionObject[1] - player.Futur_Position[1]); 
	float DistanceZ = abs(PositionObject[2] - player.Futur_Position[2]); 
	vec3 Result_Vector = vec3(DistanceX,DistanceY,DistanceZ);
	if(OnTopOfCheck) player.OnTopOf = false;

	if(DistanceX < DimensionObject[0] && DistanceY < DimensionObject[1] && DistanceZ < DimensionObject[2])
	{
		//cout << DistanceX << " " << DistanceY << " " << DistanceZ << " " << endl;
		
		if(OnTopOfCheck) player.OnTopOf = (player.Futur_Position[1] > PositionObject[1] && DistanceY >  DimensionObject[2] * 0.90f && DistanceY < DimensionObject[2]);
		player.AngleCollision = atan2(DistanceY, DistanceX);
	
		return true;
	}
	return false;
}

bool Collision_Helper::CollideWithBlock(Map_Creator map,Player &player,Drawing_Manager drawing_manager)
{
	int Index = 0;
	int i = 0, j = 0;
	vec3 Final_TilePosition;
	vec3 Initial_TilePosition;
	vec3 Final_PlayerPosition;
	bool resultOfCollide;
	vec3 OldPlayerPosition;

	while(i < 20)
	{
		while(j < 20)
		{
			Index += 3;
			if(map.Content[Index] != map.TypeContent::T_Nothing && map.Content[Index]!= map.TypeContent::T_Saw && map.Content[Index] != map.TypeContent::T_Trampoline)
			{
				OldPlayerPosition = player.Position;
				player.Position = StaticHandle::Get_projected_Position(player.Position);
				//drawing_manager.RenderCollision(player.Position);
				
				Initial_TilePosition = map.Get_Initial_TilePosition(i,j);
				Final_TilePosition = map.Set_Tile_Position(Initial_TilePosition);
				
				resultOfCollide = IsCollide(Final_TilePosition,player,map.DimensionObject,true);
				player.Position = OldPlayerPosition;

				if(resultOfCollide)
				{
					//cout << "Collide with " << i << " " << j <<endl;
					return true;
				}

				//drawing_manager.RenderCollision(Final_TilePosition); 
				
			}
			j++;
		}
		i++;
		j = 0;
	}

	return false;
}

void Collision_Helper::Update(Map_Creator map, Player &player,Drawing_Manager drawing_manager)
{
	player.IsCollide = CollideWithBlock(map,player,drawing_manager);

	for(int i = 0; i < 5; i++)
	{
		if(IsCollide(map.TabSaw[i].Position,player,vec3(3,3,4)))
		{
			player.IsHurt = true;
		}	
	}

	for(int i = 0; i < 3; i++)
	{
		if(IsCollide(map.TabTrampo[i].Position,player,vec3(3,3,4)))
		{
			player.Rebound = true;
		}
	}
}