#pragma once
class Keyboard
{
public:
	Keyboard(void);
	~Keyboard(void);
	void keyPressed (unsigned char key);
	void keyUp (unsigned char key);
	bool IsHold(unsigned char key);
	bool IsPressed(unsigned char key);
	void SetActive(unsigned char key,bool On);
private:
	bool m_KeyActive[27];
	bool m_OldKeyActive[27];
	int GetCodeTypeChar(unsigned char key,int& Depart);
};

