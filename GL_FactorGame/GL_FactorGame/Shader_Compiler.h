#pragma once
#include "Shader_Stream.h"

class Shader_Compiler
{
public:
	static unsigned int Compile_Shader(string VS_Name, string FS_Name, string TCS_Name, string TES_Name, string GS_Name);
};

