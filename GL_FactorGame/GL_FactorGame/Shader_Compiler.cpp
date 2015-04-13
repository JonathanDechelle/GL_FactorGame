#include "Shader_Compiler.h"
#include "..\Include\glew.h"
#include "..\Include\glut.h"

unsigned int Shader_Compiler::Compile_Shader(string VS_Name, string FS_Name, string TCS_Name, string TES_Name, string GS_Name)
{
	GLuint ID_Vertex_Shader;
	GLuint ID_Fragment_Shader;
	GLuint ID_TesselationC_Shader;
	GLuint ID_TesselationE_Shader;
	GLuint ID_Geometry_Shader;
	GLuint ID_Program;

	GLchar* Text_Vertex_Shader = Shader_Stream::ReadShaderFile(VS_Name);
	GLchar* Text_Fragment_Shader = Shader_Stream::ReadShaderFile(FS_Name);
	GLchar* Text_TesselationControl_Shader = Shader_Stream::ReadShaderFile(TCS_Name);
	GLchar* Text_TesselationEvalution_Shader = Shader_Stream::ReadShaderFile(TES_Name);
	GLchar* Text_Geometry_Shader = Shader_Stream::ReadShaderFile(GS_Name);

	const GLchar * Text_Vertex_Shader_const = Text_Vertex_Shader;
	const GLchar * Text_Fragment_Shader_const = Text_Fragment_Shader;
	const GLchar * Text_TesselationControl_Shader_const = Text_TesselationControl_Shader;
	const GLchar * Text_TesselationEvalution_Shader_const = Text_TesselationEvalution_Shader;
	const GLchar * Text_Geometry_Shader_const = Text_Geometry_Shader;


	//Create and compile Vertex_Shader
	ID_Vertex_Shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(ID_Vertex_Shader,1,&Text_Vertex_Shader_const,NULL);
	glCompileShader(ID_Vertex_Shader);

	//Create and compile Fragment_Shader
	ID_Fragment_Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(ID_Fragment_Shader,1,&Text_Fragment_Shader_const,NULL);
	glCompileShader(ID_Fragment_Shader);

	//Create and compile TesselationControl_Shader
	ID_TesselationC_Shader = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(ID_TesselationC_Shader,1,&Text_TesselationControl_Shader_const,NULL);
	glCompileShader(ID_TesselationC_Shader);

	//Create and compile TesselationEvalutation_Shader
	ID_TesselationE_Shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(ID_TesselationE_Shader,1,&Text_TesselationEvalution_Shader_const,NULL);
	glCompileShader(ID_TesselationE_Shader);

	//Create and compile Geometry_Shader
	ID_Geometry_Shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(ID_Geometry_Shader,1,&Text_Geometry_Shader_const,NULL);
	glCompileShader(ID_Geometry_Shader);
	
	//CHECK ERROR
	GLchar* logbuffer = new GLchar(1024);
	glGetShaderInfoLog(ID_Vertex_Shader, 1024, NULL, logbuffer);
	if(*(logbuffer+1) != -51)
	{
		printf("V SHADER \n");
		printf(logbuffer);
	}

	glGetShaderInfoLog(ID_Fragment_Shader, 1024, NULL, logbuffer);
	if(*(logbuffer+1) != -51)
	{
		printf("F SHADER \n");
		printf(logbuffer);
	}

	glGetShaderInfoLog(ID_TesselationC_Shader, 1024, NULL, logbuffer);
	if(*(logbuffer+1) != -51)
	{
		printf("TC SHADER\n");
		printf(logbuffer);
	}

	glGetShaderInfoLog(ID_TesselationE_Shader, 1024, NULL, logbuffer);
	if(*(logbuffer+1) != -51)
	{
		printf("TE SHADER\n");
		printf(logbuffer);
	}

	glGetShaderInfoLog(ID_Geometry_Shader, 1024, NULL, logbuffer);
	if(*(logbuffer+1) != -51)
	{
		printf("G SHADER\n");
		printf(logbuffer);
	}

	/*Create program, attach shader to it, and link it*/
	ID_Program = glCreateProgram();
	glAttachShader(ID_Program,ID_Vertex_Shader);
	glAttachShader(ID_Program,ID_Fragment_Shader);
	//glAttachShader(ID_Program,ID_TesselationC_Shader);
	//glAttachShader(ID_Program,ID_TesselationE_Shader);
	//glAttachShader(ID_Program,ID_Geometry_Shader);
	glLinkProgram(ID_Program);

	/*Delete the shader as the program has them now*/
	glDeleteShader(ID_Vertex_Shader);
	glDeleteShader(ID_Fragment_Shader);
	glDeleteShader(ID_TesselationC_Shader);
	glDeleteShader(ID_TesselationE_Shader);
	glDeleteShader(ID_Geometry_Shader);
	return ID_Program;
}
