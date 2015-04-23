#pragma once
#include "DATA.h"
#include "objloader.h"
#include "..\Include\glew.h"
#include "..\Include\glut.h"
#include "StaticHandle.h"

class Model_Factory
{
public:
	Model_Factory();
	~Model_Factory(void);
	enum ModelType
	{
		Torus,
		Ball,
		Saw,
		HalfBall,
		Cube
	};
	TabVertex Torus_Model;
	TabVertex Ball_Model;
	TabVertex Saw_Model;
	TabVertex Half_Ball_Model;
	TabVertex Cube_Model;
	TabVertex Models[5];
	int NbModels;

	void Load_Models();
	void Draw_Models(ModelType Type, mat4 mv_matrix, int Texture);
	void Draw_Models(ModelType Type, mat4 mv_matrix, int Texture, float Percent);
};

