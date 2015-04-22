#include "Model_Factory.h"


Model_Factory::Model_Factory()
{
}


Model_Factory::~Model_Factory()
{
}

Model_Factory::Model_Factory(int mv_location, int rendering_program)
{
	this->mv_location = mv_location;
	this->rendering_program = rendering_program;
}

void Model_Factory::Load_Models()
{
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals;

	objloader::LoadObj("Torus.obj", vertices, uvs, normals); 
	Torus_Model = TabVertex(vertices,uvs);
	objloader::LoadObj("Ball.obj", vertices, uvs, normals);  
	Ball_Model = TabVertex(vertices,uvs);
	objloader::LoadObj("Saw.obj",vertices,uvs,normals); 	
	Saw_Model = TabVertex(vertices,uvs);
	objloader::LoadObj("Half_Ball.obj",vertices,uvs,normals); 	
	Half_Ball_Model = TabVertex(vertices,uvs);
	objloader::LoadObj("Cube.obj",vertices,uvs,normals); 	
	Cube_Model = TabVertex(vertices,uvs);

	Models[Torus] = Torus_Model;
	Models[Ball] = Ball_Model;
	Models[Saw] = Saw_Model;
	Models[HalfBall] = Half_Ball_Model;
 	Models[Cube] = Cube_Model;
	NbModels = 5;
}

void Model_Factory::Draw_Models(ModelType Type, mat4 mv_matrix, int Texture)
{
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
	glUniform1i(glGetUniformLocation(rendering_program, "textureSelect"), Texture);
	
	if((int)Type != 0)
		glDrawArrays( GL_TRIANGLES, Models[Type - 1].NbVertex, Models[Type].NbVertex - Models[Type - 1].NbVertex);	
	else
		glDrawArrays( GL_TRIANGLES, 0, Models[0].NbVertex);	
}

void Model_Factory::Draw_Models(ModelType Type, mat4 mv_matrix, int Texture, float Percent)
{
	glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
	glUniform1i(glGetUniformLocation(rendering_program, "textureSelect"), Texture);

	if((int)Type != 0)
		glDrawArrays( GL_TRIANGLES, Models[Type - 1].NbVertex, (Models[Type].NbVertex - Models[Type - 1].NbVertex) * Percent);	
	else
		glDrawArrays( GL_TRIANGLES, 0, Models[0].NbVertex);	
}
