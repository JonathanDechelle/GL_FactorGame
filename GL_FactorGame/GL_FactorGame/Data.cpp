#include "DATA.h"

TabVertex::TabVertex()
{

}

TabVertex::TabVertex(vertex * ArrayPoints, int NbVertex)
{
	this->ArrayPoints = new vertex[NbVertex];
	this->NbVertex = NbVertex;
	this->ArraySize = sizeof(vertex) * NbVertex;

	 memcpy ( this->ArrayPoints, ArrayPoints, ArraySize);
}

TabVertex::TabVertex(vector<vec3> vertices, vector<vec2> uvs)
{
	this->ArrayPoints = new vertex[vertices.size()];
	this->NbVertex = vertices.size();
	this->ArraySize = sizeof(vertex) * NbVertex;

	for (int i =0; i < NbVertex; i++)
	{
		ArrayPoints[i].x = vertices[i][0];
		ArrayPoints[i].y = vertices[i][1];
		ArrayPoints[i].z = vertices[i][2];
		ArrayPoints[i].u = uvs[i][0];
		ArrayPoints[i].v = uvs[i][1];
	}
}

int TabVertex::GetArraySize()
{
	return ArraySize;
}

DATA::DATA(void)
{
	
	vertex CubePositions[]=
	{
		// FRONT
		vertex(-0.25f,  0.25f, -0.25f, 0.0f   , 0.0f),
		vertex(-0.25f, -0.25f, -0.25f, 0.0f   , 1.0f),
		vertex( 0.25f, -0.25f, -0.25f, 1.0f   , 1.0f),

		vertex( 0.25f, -0.25f, -0.25f, 1.0f   , 1.0f),
		vertex( 0.25f,  0.25f, -0.25f, 1.0f   , 0.0f),
		vertex(-0.25f,  0.25f, -0.25f, 0.0f   , 0.0f),
		/////


		//BACK
		vertex(-0.25f,  0.25f, 0.25f, 0.0f   , 0.0f),
		vertex(-0.25f, -0.25f, 0.25f, 0.0f   , 1.0f),
		vertex( 0.25f, -0.25f, 0.25f, 1.0f   , 1.0f),

		vertex( 0.25f, -0.25f, 0.25f, 1.0f   , 1.0f),
		vertex( 0.25f,  0.25f, 0.25f, 1.0f   , 0.0f),
		vertex(-0.25f,  0.25f, 0.25f, 0.0f   , 0.0f),
		////

		//TOP
		vertex(-0.25f,  0.25f, -0.25f, 0.0f   , 0.0f),
		vertex( 0.25f,  0.25f, -0.25f, 0.0f   , 1.0f),
		vertex( 0.25f,  0.25f,  0.25f, 1.0f   , 1.0f),

		vertex( 0.25f,  0.25f,  0.25f, 1.0f   , 1.0f),
		vertex(-0.25f,  0.25f,  0.25f, 1.0f   , 0.0f),
		vertex(-0.25f,  0.25f, -0.25f, 0.0f   , 0.0f),
		//

		//BOTTOM
		vertex(-0.25f, -0.25f, -0.25f, 0.0f   , 0.0f),
		vertex( 0.25f, -0.25f, -0.25f, 0.0f   , 1.0f),
		vertex( 0.25f, -0.25f,  0.25f, 1.0f   , 1.0f),

		vertex( 0.25f, -0.25f,  0.25f, 1.0f   , 1.0f),
		vertex(-0.25f, -0.25f,  0.25f, 1.0f   , 0.0f),
		vertex(-0.25f, -0.25f, -0.25f, 0.0f   , 0.0f),
		//

		//LEFT SIDE
		vertex( 0.25f, -0.25f, -0.25f, 0.0f   , 1.0f),
		vertex( 0.25f,  0.25f, -0.25f, 0.0f   , 0.0f),
		vertex( 0.25f, -0.25f,  0.25f, 1.0f   , 1.0f),

		vertex( 0.25f,  0.25f,  0.25f, 1.0f   , 0.0f),
		vertex( 0.25f,  0.25f, -0.25f, 0.0f   , 0.0f),
		vertex( 0.25f, -0.25f,  0.25f, 1.0f   , 1.0f),
		////

		//RIGHT SIDE
		vertex(-0.25f, -0.25f, -0.25f, 0.0f   , 1.0f),
		vertex(-0.25f,  0.25f, -0.25f, 0.0f   , 0.0f),
		vertex(-0.25f, -0.25f,  0.25f, 1.0f   , 1.0f),

		vertex(-0.25f,  0.25f,  0.25f, 1.0f   , 0.0f),
		vertex(-0.25f,  0.25f, -0.25f, 0.0f   , 0.0f),
		vertex(-0.25f, -0.25f,  0.25f, 1.0f   , 1.0f),

	};

	 SimpleCube = TabVertex(CubePositions, 36);
}


DATA::~DATA(void)
{
}
