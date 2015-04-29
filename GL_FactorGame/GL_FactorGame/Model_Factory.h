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
		Cube,
		LifeBar_Content,
		LifeBar_Frame,
		Trampoline
	};
	TabVertex Torus_Model;
	TabVertex Ball_Model;
	TabVertex Saw_Model;
	TabVertex Half_Ball_Model;
	TabVertex Cube_Model;
	TabVertex LifeBar_Content_Model;
	TabVertex LifeBar_Frame_Model;
	TabVertex Trampoline_Model;
	TabVertex Models[8];
	int NbModels;

	void Load_Models();
	void Draw_Models(ModelType Type, int Texture);
	void Draw_Models(ModelType Type, int Texture, float Percent);
};

