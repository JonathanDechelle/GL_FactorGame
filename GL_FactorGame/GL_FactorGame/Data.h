#pragma once
#include "vertex.h"
#include "..\Include\Windows.h"
#include <vector>
#include "vmath.h"
#include <stdio.h>
using namespace  std;

class TabVertex
{
public:
	vertex* ArrayPoints;
	int NbVertex;
	int GetArraySize();
	TabVertex(void);
	TabVertex(vertex * ArrayPoints, int NbVertex);
	TabVertex(vector<vec3> vertices, vector<vec2> uvs);
private:
	int ArraySize;
};

class DATA
{
public:
	DATA(void);
	~DATA(void);
};
