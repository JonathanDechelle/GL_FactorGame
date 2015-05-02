#include "StaticHandle.h"

GLuint StaticHandle::rendering_program = 0;
GLuint StaticHandle::mv_location = 0;
GLuint StaticHandle::proj_location = 0;
GLuint StaticHandle::lookAtMatrix_Location = 0;
float StaticHandle::CurrentTime = 0;
float StaticHandle::Speed = 0.0005f;
//float StaticHandle::GameSpeed = 3500; //off sector
float StaticHandle::GameSpeed = 1500; //on sector

mat4 StaticHandle::mv_matrix = 0;
mat4 StaticHandle::proj_matrix = 0;
mat4 StaticHandle::MapBase_matrix = 0;
Light StaticHandle::light;

vec3 StaticHandle::Get_projected_Position(vec3 Position)
{
	Position[0] += StaticHandle::proj_matrix[3][0] * StaticHandle::proj_matrix[0][0];
	Position[1] += StaticHandle::proj_matrix[3][1] * StaticHandle::proj_matrix[1][1];
	Position[2] += StaticHandle::proj_matrix[3][2] * StaticHandle::proj_matrix[2][2];

	return Position;
}