#include <iostream>
#include <vector>
#include <ctime>
#include "..\Include\glew.h"
#include "..\Include\glut.h"
#include "Load_Image.h"
#include "StaticHandle.h"
#include "Player.h"
#include "Camera.h"
#include "Map_Creator.h"
#include "Shader_Compiler.h"
#include "Collision_Helper.h"


GLuint vertex_array_object,buffer;
GLuint textures[10];
vec2 WindowSize(800,600);


DATA data = DATA();
Keyboard keyboard = Keyboard();
Camera camera = Camera();
Model_Factory Models_factory;
Map_Creator Map;
Player player;
Drawing_Manager Drawing_manager;



void keyPressed (unsigned char key, int x, int y) {keyboard.keyPressed(key);}
void keyUp (unsigned char key, int x, int y){keyboard.keyUp(key);};
void MouseMove(int x, int y)
{ 
	//camera.MouseMove(x, y);
}

void keyUpdate()
{
	camera.Keyboard_Update(keyboard);

	//Light Direction
	//if(keyboard.IsHold('u')) Light_Direction[0] += StaticHandle::GameSpeed;
	//else if(keyboard.IsHold('j')) Light_Direction[0] -= StaticHandle::GameSpeed;

	//if(keyboard.IsHold('y')) Light_Direction[1] += StaticHandle::GameSpeed;
	//else if(keyboard.IsHold('h')) Light_Direction[1] -= StaticHandle::GameSpeed;

	//if(keyboard.IsHold('o')) Light_Direction[2] += StaticHandle::GameSpeed;
	//else if(keyboard.IsHold('l')) Light_Direction[2] -= StaticHandle::GameSpeed;

	////Light Brightness 
	//if(keyboard.IsHold('R')) Light_Brightness += StaticHandle::GameSpeed * 3;
	//else if(keyboard.IsHold('F')) Light_Brightness -= StaticHandle::GameSpeed * 3; 

	////Light Radius
	//if(keyboard.IsHold('Z')) Light_Radius += StaticHandle::GameSpeed/2;
	//else if(keyboard.IsHold('X')) Light_Radius -= StaticHandle::GameSpeed/2;
	//if(Light_Radius < 0) Light_Radius = 0;
}

void Set_VertexArray()
{
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	Models_factory = Model_Factory();
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
	StaticHandle::proj_matrix = perspective(50.0f, (float)(WindowSize[0]/WindowSize[1]),	0.1f,	1000.0f);			//Initialize Matrix
	
	StaticHandle::mv_location = glGetUniformLocation(StaticHandle::rendering_program, "mv_matrix");
	StaticHandle::proj_location = glGetUniformLocation(StaticHandle::rendering_program, "proj_matrix");
	StaticHandle::lookAtMatrix_Location = glGetUniformLocation(StaticHandle::rendering_program, "lookAtMatrix_matrix");				//Initialize Uniform

	StaticHandle::light.Initialize(StaticHandle::rendering_program);

	glGenTextures(10, textures);
	Load_Image::generate_texture("BlueCircuit.jpg",textures, Load_Image::Type_Image::BlueCircuit);
	Load_Image::generate_texture("Or.jpg",textures, Load_Image::Type_Image::Or);
	Load_Image::generate_texture("Metal.jpg",textures, Load_Image::Type_Image::Metal);
	Load_Image::generate_texture("GreenEye.jpg",textures, Load_Image::Type_Image::GreenEye);
	Load_Image::generate_texture("RedEye.jpg",textures, Load_Image::Type_Image::RedEye);
	Load_Image::generate_texture("Leaf.png",textures, Load_Image::Type_Image::Leaf);
	Load_Image::generate_texture("Sand.png",textures, Load_Image::Type_Image::Sand);
	Load_Image::generate_texture("Woodbox.png",textures, Load_Image::Type_Image::WoodBox);
	Load_Image::generate_texture("LifeBarContent.png",textures,Load_Image::Type_Image::LifeBarContent);
	Load_Image::generate_texture("RedCircuit.jpg",textures,Load_Image::Type_Image::RedCircuit);
	Set_VertexArray();																					//initialize DataVertex and Model

	glUseProgram(StaticHandle::rendering_program);
	Load_Image::Initialize(StaticHandle::rendering_program);
	Load_Image::set_UniformTexture("BlueCircuit.jpg", Load_Image::Type_Image::BlueCircuit);
	Load_Image::set_UniformTexture("Or.jpg",Load_Image::Type_Image::Or);
	Load_Image::set_UniformTexture("Metal.jpg",Load_Image::Type_Image::Metal);
	Load_Image::set_UniformTexture("GreenEye.jpg",Load_Image::Type_Image::GreenEye);
	Load_Image::set_UniformTexture("RedEye.jpg",Load_Image::Type_Image::RedEye);
	Load_Image::set_UniformTexture("Leaf.png",Load_Image::Type_Image::Leaf);
	Load_Image::set_UniformTexture("Sand.png",Load_Image::Type_Image::Sand);
	Load_Image::set_UniformTexture("Woodbox.png",Load_Image::Type_Image::WoodBox);
	Load_Image::set_UniformTexture("LifeBarContent.png",Load_Image::Type_Image::LifeBarContent);
	Load_Image::set_UniformTexture("RedCircuit.jpg",Load_Image::Type_Image::RedCircuit);

	glutKeyboardFunc(keyPressed);																	//Set KeyboardFunc and Mouse Move
	glutKeyboardUpFunc(keyUp);
	glutPassiveMotionFunc(MouseMove);	

	player = Player();
	Map = Map_Creator();
	Map.SetBase_Position(vec3(-10.0f,0.0f,-20.0f));
	Map.Load("Map1.png");
	player.Set_BasePosition(player.Start_Position);
	Drawing_manager = Drawing_Manager(Models_factory);
}

void Set_Uniform()
{
	glUniformMatrix4fv(StaticHandle::proj_location, 1, GL_FALSE, StaticHandle::proj_matrix);
	glUniformMatrix4fv(StaticHandle::lookAtMatrix_Location,1, GL_FALSE, camera.lookAtMatrix_matrix);
}

void render(float CurrentTime) 
{
	glClearColor(0,0,0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	StaticHandle::light.Update(StaticHandle::CurrentTime);
	
	player.Udpate(keyboard,Models_factory);
	Collision_Helper::Update(Map,player,Drawing_manager);

	camera.Update(player.Position);

	keyUpdate();

	Set_Uniform(); 

	Map.UpdateAndDraw(Drawing_manager,Models_factory);

	Drawing_manager.Update(player);
	Drawing_manager.Draw(CurrentTime,StaticHandle::GameSpeed);
}

void display() 
{   
	StaticHandle::CurrentTime += StaticHandle::Speed;
	render(StaticHandle::CurrentTime);
	glutSwapBuffers(); 
	glutPostRedisplay(); // Permet de faire une vraie loop
}

void startup()
{
	StaticHandle::rendering_program = Shader_Compiler::Compile_Shader("Vertex_Shader.txt",
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
	glDeleteProgram(StaticHandle::rendering_program);
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

