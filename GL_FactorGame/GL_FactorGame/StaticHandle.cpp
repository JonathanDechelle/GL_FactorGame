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