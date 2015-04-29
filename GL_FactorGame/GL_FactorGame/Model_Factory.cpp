#include "Model_Factory.h"


Model_Factory::Model_Factory()
{
}


Model_Factory::~Model_Factory()
{
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
	objloader::LoadObj("LifeBarContent.obj",vertices,uvs,normals); 	
	LifeBar_Content_Model = TabVertex(vertices,uvs);
	objloader::LoadObj("LifeBarFrame.obj",vertices,uvs,normals); 	
	LifeBar_Frame_Model = TabVertex(vertices,uvs);
	objloader::LoadObj("Trampoline.obj",vertices,uvs,normals); 	
	Trampoline_Model = TabVertex(vertices,uvs);

	Models[Torus] = Torus_Model;
	Models[Ball] = Ball_Model;
	Models[Saw] = Saw_Model;
	Models[HalfBall] = Half_Ball_Model;
 	Models[Cube] = Cube_Model;
	Models[LifeBar_Frame] = LifeBar_Frame_Model;
	Models[LifeBar_Content] = LifeBar_Content_Model;
	Models[Trampoline] = Trampoline_Model;
	NbModels = 8;
}

void Model_Factory::Draw_Models(ModelType Type, int Texture)
{
	glUniformMatrix4fv(StaticHandle::mv_location, 1, GL_FALSE, StaticHandle::mv_matrix);
	glUniform1i(glGetUniformLocation(StaticHandle::rendering_program, "textureSelect"), Texture);
	
	if((int)Type != 0)
		glDrawArrays( GL_TRIANGLES, Models[Type - 1].NbVertex, Models[Type].NbVertex - Models[Type - 1].NbVertex);	
	else
		glDrawArrays( GL_TRIANGLES, 0, Models[0].NbVertex);	
}

void Model_Factory::Draw_Models(ModelType Type, int Texture, float Percent)
{
	glUniformMatrix4fv(StaticHandle::mv_location, 1, GL_FALSE, StaticHandle::mv_matrix);
	glUniform1i(glGetUniformLocation(StaticHandle::rendering_program, "textureSelect"), Texture);

	if((int)Type != 0)
		glDrawArrays( GL_TRIANGLES, Models[Type - 1].NbVertex, (Models[Type].NbVertex - Models[Type - 1].NbVertex) * Percent);	
	else
		glDrawArrays( GL_TRIANGLES, 0, Models[0].NbVertex * Percent);	
}
