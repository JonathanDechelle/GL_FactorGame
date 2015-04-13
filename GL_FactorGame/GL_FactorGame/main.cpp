#include <iostream>
#include <vector>
#include "..\Include\glew.h"
#include "..\Include\glut.h"
#include "Shader_Compiler.h"
#include "vmath.h"
#include "vertex.h"
#include "DATA.h"
#include "Load_Image.h"
#include "Keyboard.h"
#include "Camera.h"
#include "objloader.h"


float CurrentTime = 0;
float Speed = 0.0005f;
float SpeedChange = 0.001f;
GLuint rendering_program;
GLuint vertex_array_object,buffer;
GLuint textures[4];
GLint mv_location, proj_location, lookAtMatrix_Location;
mat4 mv_matrix, proj_matrix;
vec2 WindowSize(800,600);
unsigned int* Map;


DATA data = DATA();
Keyboard keyboard = Keyboard();
Camera camera = Camera();



TabVertex Torus_Model;
TabVertex Ball_Model;
TabVertex Saw_Model;

void keyPressed (unsigned char key, int x, int y) {keyboard.keyPressed(key);}
void keyUp (unsigned char key, int x, int y){keyboard.keyUp(key);};
void MouseMove(int x, int y)
{ 
	//camera.MouseMove(x, y);
}

void keyUpdate()
{
	//Camera Position X
	if(keyboard.IsHold('W')) camera.Position += SpeedChange * camera.center;
	if(keyboard.IsHold('S')) camera.Position -= SpeedChange * camera.center;
	if(keyboard.IsHold('A')) camera.Position -= normalize(cross(camera.center, camera.Up)) * SpeedChange * 2;
	if(keyboard.IsHold('D')) camera.Position += normalize(cross(camera.center, camera.Up)) * SpeedChange * 2; 
	
	//Camera Position Z
	if(keyboard.IsHold('Q')) camera.Position[1] += SpeedChange;
	else if(keyboard.IsHold('E')) camera.Position[1] -= SpeedChange;

	//Camera Rotation
	if(keyboard.IsHold('J')) camera.center[0] += SpeedChange;
	else if(keyboard.IsHold('L')) camera.center[0] -= SpeedChange;

	if(keyboard.IsHold('I')) camera.center[1] += SpeedChange;
	else if(keyboard.IsHold('K')) camera.center[1] -= SpeedChange;

	if(keyboard.IsHold('U')) camera.center[2] += SpeedChange;
	else if(keyboard.IsHold('O')) camera.center[2] -= SpeedChange;

	//camera.Position[1] = 0.0f;
}

void Set_VertexArray()
{
	vector<vec3> vertices;
	vector<vec2> uvs;
	vector<vec3> normals; // Won't be used at the moment.
	objloader::LoadObj("Torus.obj", vertices, uvs, normals);
	Torus_Model = TabVertex(vertices,uvs);
	objloader::LoadObj("Ball.obj", vertices, uvs, normals);
	Ball_Model = TabVertex(vertices,uvs);
	objloader::LoadObj("Saw.obj",vertices,uvs,normals);
	/*Saw_Model = TabVertex(vertices,uvs);*/

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 
		Torus_Model.GetArraySize(),
		Torus_Model.ArrayPoints, 
		GL_STATIC_DRAW);

	glBufferData(GL_ARRAY_BUFFER, 
		Ball_Model.GetArraySize(),
		Ball_Model.ArrayPoints, 
		GL_STATIC_DRAW);

	/*glBufferData(GL_ARRAY_BUFFER, 
		Saw_Model.GetArraySize(),
		Saw_Model.ArrayPoints, 
		GL_STATIC_DRAW);*/

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  sizeof(vertex), (void *)offsetof(vertex, x));
	glEnableVertexAttribArray(1); // UV Mapping
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,  sizeof(vertex), (void *)offsetof(vertex, u));
}

void Initialize_ALL()
{
	proj_matrix = perspective(50.0f, (float)(WindowSize[0]/WindowSize[1]),	0.1f,	1000.0f);			//Initialize Matrix
	

	mv_location = glGetUniformLocation(rendering_program, "mv_matrix");
	proj_location = glGetUniformLocation(rendering_program, "proj_matrix");
	lookAtMatrix_Location = glGetUniformLocation(rendering_program, "lookAtMatrix_matrix");				//Initialize Uniform
	

	glGenTextures(4, textures);
	Load_Image::generate_texture("Circuit.jpg",textures, 0);
	Load_Image::generate_texture("Or.jpg",textures, 1);

	Set_VertexArray();																					//initialize DataVertex

	glUseProgram(rendering_program);
	Load_Image::set_UniformTexture("Circuit.jpg", 0, rendering_program);
	Load_Image::set_UniformTexture("Or.jpg",1, rendering_program);

	glutKeyboardFunc(keyPressed);																	//Set KeyboardFunc and Mouse Move
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(MouseMove);	
}

void Set_Model()
{
	mv_matrix = translate(0.0f,0.0f,-15.0f) *
		rotate(CurrentTime * 50, 0.0f, 1.0f, 0.0f) *
		rotate(CurrentTime * 50, 0.0f, 0.0f, 1.0f);

	glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
	glUniform1i(glGetUniformLocation(rendering_program, "textureSelect"), 0);
	glDrawArrays( GL_TRIANGLES, 0, Torus_Model.NbVertex);	

	mv_matrix = translate(0.0f,0.0f,-15.0f) *
		rotate(CurrentTime * 50, 1.0f, 0.0f, 0.0f) *
		rotate(CurrentTime * 50, 0.0f, 0.0f, 1.0f);

	glUniformMatrix4fv(mv_location, 1, GL_FALSE, mv_matrix);
	glUniform1i(glGetUniformLocation(rendering_program, "textureSelect"), 1);
	glDrawArrays( GL_TRIANGLES, Torus_Model.NbVertex,Ball_Model.NbVertex );	
}

void render(float CurrentTime) 
{
	glClearColor(1,1,1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.Update();
	keyUpdate();

	glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
	glUniformMatrix4fv(lookAtMatrix_Location,1, GL_FALSE, camera.lookAtMatrix_matrix);

	Set_Model(); 
}

void display() 
{   
	CurrentTime += Speed;
	render(CurrentTime);
	glutSwapBuffers(); 
	glutPostRedisplay(); // Permet de faire une vraie loop
}

void startup()
{
	rendering_program = Shader_Compiler::Compile_Shader("Vertex_Shader.txt",
														"Fragment_Shader.txt",
														"TesselationControl_Shader.txt",
														"TesselationEvaluation_Shader.txt",
														"Geometry_Shader.txt");
	
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glFrontFace(GL_CW);
	glCullFace(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glPointSize(5.0f);
	Initialize_ALL();
}

void shutdown()
{
	glDeleteBuffers(1,&vertex_array_object);
	glDeleteBuffers(1, &buffer);
	glDeleteTextures(3, textures);
	glDeleteProgram(rendering_program);
}

int main(int argc, char *argv[])
{
	 glutInit(&argc, argv);
	 glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
     glutInitWindowSize(WindowSize[0],WindowSize[1]);
     glutCreateWindow("GL_FactorGame");
     glutDisplayFunc(display);

	 glewInit();

    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );	 //Check for error
        return false;
    }

	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else {
		printf("Not totally ready :( \n");
		exit(1);
	}

	if (glewIsSupported("GL_VERSION_4_1"))
		printf("Ready for OpenGL 4.1\n");
	else {
		printf("OpenGL 4.1 not supported\n");
		exit(1);
	}

	startup();
	glutMainLoop();
}

