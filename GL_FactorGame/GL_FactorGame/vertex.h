#pragma once
class vertex
{
public:
	//Position 
	float x; 
	float y;
	float z;

	//texture
	float u; //X
	float v; //Y

	vertex(float x,float y,float z,float u,float v)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->u = u;
		this->v = v;
	}
	vertex(){}
};