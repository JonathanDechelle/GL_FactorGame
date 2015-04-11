#include "Shader_Stream.h"
#include <fstream>

char* Shader_Stream::ReadShaderFile(string File)
{
	ifstream fichier(File, ios::in);  
	ifstream is (File, std::ifstream::in);
	char * Retour = new char;

	if(fichier)  // si l'ouverture a réussi
	{ 
		char caractere; 
		char* TempTab_Caractere = new char [2000];
		char* RealTab_Caractere;
		int NbCarac = 0;

		while(fichier.get(caractere))
		{
			TempTab_Caractere[NbCarac] = caractere;
			NbCarac++;
		}

		//Remplis le vrai tableau sans les caractere de fin de fichier
		RealTab_Caractere = new char [NbCarac];
		for(int i =0; i < NbCarac; i++)
		{
			RealTab_Caractere[i] = TempTab_Caractere[i];
		}
		fichier.close(); 
		RealTab_Caractere[NbCarac] = 0;
		Retour = RealTab_Caractere;
	}

	return Retour;
}
