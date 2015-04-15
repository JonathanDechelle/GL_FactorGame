#pragma once
#include "DATA.h"
#include "objloader.h"
#include "..\Include\glew.h"
#include "..\Include\glut.h"

class Model_Factory
{
public:
	Model_Factory();
	~Model_Factory(void);
	enum ModelType
	{
		Torus,
		Ball,
		Saw
	};
	TabVertex Torus_Model;
	TabVertex Ball_Model;
	TabVertex Saw_Model;
	TabVertex Models[3];
	int NbModels;

	void Load_Models();
	void Draw_Models(ModelType Type, mat4 mv_matrix, int mv_location, int Texture,  int rendering_program);
	void Draw_Models(ModelType Type, mat4 mv_matrix, int mv_location, int Texture,  int rendering_program, float Percent);
};

