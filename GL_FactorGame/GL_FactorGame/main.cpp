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
#include "Model_Factory.h"
#include "Player.h"

float CurrentTime = 0;
float Speed = 0.0005f;
float SpeedChange = 0.001f;
GLuint rendering_program;
GLuint vertex_array_object,buffer;
GLuint textures[6];
GLint mv_location, proj_location, lookAtMatrix_Location;
mat4 mv_matrix, proj_matrix;
vec2 WindowSize(800,600);
unsigned int* Map;


DATA data = DATA();
Keyboard keyboard = Keyboard();
Camera camera = Camera();
Model_Factory Models_factory = Model_Factory();
Player player;

void keyPressed (unsigned char key, int x, int y) {keyboard.keyPressed(key);}
void keyUp (unsigned char key, int x, int y){keyboard.keyUp(key);};
void MouseMove(int x, int y)
{ 
	//camera.MouseMove(x, y);
}

void keyUpdate()
{
	//Camera Position X
	//if(keyboard.IsHold('W')) camera.Position += SpeedChange * camera.center;
	//if(keyboard.IsHold('S')) camera.Position -= SpeedChange * camera.center;
	//if(keyboard.IsHold('A')) camera.Position -= normalize(cross(camera.center, camera.Up)) * SpeedChange * 2;
	//if(keyboard.IsHold('D')) camera.Position += normalize(cross(camera.center, camera.Up)) * SpeedChange * 2; 
	//
	////Camera Position Z
	//if(keyboard.IsHold('Q')) camera.Position[1] += SpeedChange;
	//else if(keyboard.IsHold('E')) camera.Position[1] -= SpeedChange;

	////Camera Rotation
	//if(keyboard.IsHold('J')) camera.center[0] += SpeedChange;
	//else if(keyboard.IsHold('L')) camera.center[0] -= SpeedChange;

	//if(keyboard.IsHold('I')) camera.center[1] += SpeedChange;
	//else if(keyboard.IsHold('K')) camera.center[1] -= SpeedChange;

	//if(keyboard.IsHold('U')) camera.center[2] += SpeedChange;
	//else if(keyboard.IsHold('O')) camera.center[2] -= SpeedChange;

	//camera.Position[1] = 0.0f;
}

void Set_VertexArray()
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	Models_factory.Load_Models();
	for (int i =0; i < Models_factory.NbModels; i++)
	{
		glBufferData(GL_ARRAY_BUFFER, 
			Models_factory.Models[i].GetArraySize(),
			Models_factory.Models[i].ArrayPoints, 
			GL_STATIC_DRAW);
	}

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
	

	glGenTextures(5, textures);
	Load_Image::generate_texture("Circuit.jpg",textures, Load_Image::Type_Image::Circuit);
	Load_Image::generate_texture("Or.jpg",textures, Load_Image::Type_Image::Or);
	Load_Image::generate_texture("Metal.jpg",textures, Load_Image::Type_Image::Metal);
	Load_Image::generate_texture("GreenEye.jpg",textures, Load_Image::Type_Image::GreenEye);
	Load_Image::generate_texture("RedEye.jpg",textures, Load_Image::Type_Image::RedEye);
	Set_VertexArray();																					//initialize DataVertex and Model

	glUseProgram(rendering_program);
	Load_Image::set_UniformTexture("Circuit.jpg", Load_Image::Type_Image::Circuit, rendering_program);
	Load_Image::set_UniformTexture("Or.jpg",Load_Image::Type_Image::Or, rendering_program);
	Load_Image::set_UniformTexture("Metal.jpg",Load_Image::Type_Image::Metal, rendering_program);
	Load_Image::set_UniformTexture("GreenEye.jpg",Load_Image::Type_Image::GreenEye,rendering_program);
	Load_Image::set_UniformTexture("RedEye.jpg",Load_Image::Type_Image::RedEye,rendering_program);

	glutKeyboardFunc(keyPressed);																	//Set KeyboardFunc and Mouse Move
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(MouseMove);	

	player = Player(mv_location,rendering_program);
}

void Set_Model()
{
	glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj_matrix);
	glUniformMatrix4fv(lookAtMatrix_Location,1, GL_FALSE, camera.lookAtMatrix_matrix);
	player.Draw(Models_factory,CurrentTime);
}

void render(float CurrentTime) 
{
	glClearColor(1,1,1, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.Update();
	player.Udpate(keyboard);
	keyUpdate();

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

