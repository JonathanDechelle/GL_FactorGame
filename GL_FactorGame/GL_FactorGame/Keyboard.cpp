#include "Keyboard.h"

#define A 0

Keyboard::Keyboard(void)
{

}


Keyboard::~Keyboard(void)
{

}

void Keyboard::keyPressed (unsigned char key)
{
	int TypeOfCar = 0; 
	int Depart = 0;

	TypeOfCar = GetCodeTypeChar(key,Depart);

	if(TypeOfCar != 2)
	{
		for(int Index=0; Index < 26; Index++)
			if((int)key == Index + Depart) m_KeyActive[Index] = true;
	}
	else
		if((int)key == 32) m_KeyActive[26] = true; //space
}

void Keyboard::keyUp (unsigned char key)
{
	int TypeOfCar = 0; 
	int Depart = 0;

	TypeOfCar = GetCodeTypeChar(key,Depart);

	int i;
	for (i = 0; i < 27; i++)
	{
		m_OldKeyActive[i] = false;
	}

	if(TypeOfCar != 2)
	{
		for(int Index=0; Index < 26; Index++)
			if((int)key == Index + Depart) m_KeyActive[Index] = false;
	}
	else
		if((int)key == 32) m_KeyActive[26] = false; //space
}

bool Keyboard::IsPressed(unsigned char key)
{
	int TypeOfCar = 0; 
	int Depart = 0;
	int Index = 0;

	TypeOfCar = GetCodeTypeChar(key,Depart);
	if(TypeOfCar == 2) Index = 26;
	else Index = (int)key-Depart;

	//Update OldKeyActive
	int i;
	for (i = 0; i < 27; i++)
	{
		if(!m_OldKeyActive[i] && m_KeyActive[i])
		{
			if(Index == i)
			{
				m_OldKeyActive[i] = true;
				return true;
			}

		}
	}
	return false;
	//
}

bool Keyboard::IsHold(unsigned char key)
{
	int TypeOfCar = 0; 
	int Depart = 0;
	int Index = 0;
	int i;

	TypeOfCar = GetCodeTypeChar(key,Depart);
	if(TypeOfCar == 2) Index = 26;
	else Index = (int)key-Depart;
	return m_KeyActive[Index];
}

void Keyboard::SetActive(unsigned char key,bool On)
{
	int TypeOfCar = 0; 
	int Depart = 0;
	int Index = 0;

	TypeOfCar = GetCodeTypeChar(key,Depart);
	if(TypeOfCar == 2) Index = 26;
	else Index = (int)key-Depart;

	m_KeyActive[Index] = On;
}

int Keyboard::GetCodeTypeChar(unsigned char key,int& Depart)
{
	int TypeOfCar = 0; 
	if((int)key >= 65 && (int)key <= 90) TypeOfCar = 1; //UpperCase
	else if ((int)key >=97 && (int)key <= 122) TypeOfCar = 0; //LowerCase
	else TypeOfCar = 2; //Special car

	switch(TypeOfCar)
	{
	case 0: Depart = 97;
		break;
	case 1: Depart = 65;
		break;
	case 2: // Depart = 0; :)
		break;
	}

	return TypeOfCar;
}
