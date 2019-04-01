#pragma once
#include <stdlib.h>
#include <string>

class KKeyGen
{
public:
	KKeyGen();
	~KKeyGen();


	char m_Key[30];
	char m_UserId[30];
	char m_UserKey[30];

	char m_NativeKey[30];
	char m_CNativeKey[30];

	char m_GameKey[30];
	char m_FirstKey[30];
	char m_FinalKey[30];
	void Run(int Stage);
	void C_NativeKey();
	void Cross();
	void Genius();
};

