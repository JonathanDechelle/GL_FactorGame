#include "Collision_Helper.h"


bool Collision_Helper::OnTopOf = false;
vec3 Collision_Helper::Get_projected_Position(vec3 Position)
{
	Position[0] += StaticHandle::proj_matrix[3][0] * StaticHandle::proj_matrix[0][0];
	Position[1] += StaticHandle::proj_matrix[3][1] * StaticHandle::proj_matrix[1][1];
	Position[2] += StaticHandle::proj_matrix[3][2] * StaticHandle::proj_matrix[2][2];

	return Position;
}

bool Collision_Helper::IsCollide(vec3 PositionObject, vec3 PosPlayer, vec3 DimensionObject)
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
