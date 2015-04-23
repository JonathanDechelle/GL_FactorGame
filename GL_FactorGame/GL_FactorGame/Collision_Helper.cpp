#include "Collision_Helper.h"


vec3 Collision_Helper::Get_projected_Position(vec3 Position)
{
	Position[0] += StaticHandle::proj_matrix[3][0] * StaticHandle::proj_matrix[0][0];
	Position[1] += StaticHandle::proj_matrix[3][1] * StaticHandle::proj_matrix[1][1];
	Position[2] += StaticHandle::proj_matrix[3][2] * StaticHandle::proj_matrix[2][2];

	return Position;
}
