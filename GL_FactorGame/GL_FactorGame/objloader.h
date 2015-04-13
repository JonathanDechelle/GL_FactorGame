#pragma once
#include <vector>
#include "vmath.h"
#include <stdio.h>

using namespace  std;
class objloader
{
public:
	static bool LoadObj(const char *path, 
				 vector<vec3> &out_vertices,
				 vector<vec2> &out_uvs,
				 vector<vec3> &out_normals);
};

