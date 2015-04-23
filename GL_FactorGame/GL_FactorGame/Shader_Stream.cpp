#include "Shader_Stream.h"
#include <fstream>

char* Shader_Stream::ReadShaderFile(string File)
{
	ifstream temp(File.c_str());
	int count = 0;
	char *buf;

	temp.seekg(0, ios::end);
	count = temp.tellg();

	buf = new char[count + 1];
	memset(buf,0,count);
	temp.seekg(0, ios::beg);
	temp.read(buf, count);
	buf[count] = 0;
	temp.close();

	return buf;
}
