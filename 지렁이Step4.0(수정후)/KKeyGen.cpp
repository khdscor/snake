#include "stdafx.h"
#include "KKeyGen.h"


KKeyGen::KKeyGen()
{
	strcpy_s(m_Key, "abcdefghijklmnopqrstuvwxyz");

	ZeroMemory(m_FirstKey, strlen(m_FirstKey));
	ZeroMemory(m_FinalKey, strlen(m_FinalKey));
}


KKeyGen::~KKeyGen()
{
}


void KKeyGen::Run(int Stage)
{
	switch (Stage)
	{
	case 1:
		strcpy_s(m_NativeKey, "WormGameIsVeryFunny!");
		break;
	case 5:
		C_NativeKey();
		break;
	case 10:
		Cross();
		break;
	case 11:
		strcpy_s(m_GameKey, "Go");
		break;
	case 12:
		strcat_s(m_GameKey, "ld");
		break;
	case 13:
		strcat_s(m_GameKey, "en");
		break;
	case 14:
		strcat_s(m_GameKey, "key");
		break;
	case 15:
		Genius();
		break;
	}
}


void KKeyGen::C_NativeKey()
{
	for (int i = 0; i<20; i++)
	{
		m_CNativeKey[i] = m_NativeKey[i] + 5;

		if (126 < m_CNativeKey[i])
		{
			m_CNativeKey[i] -= 126 + 33;
		}
	}
}


void KKeyGen::Cross()
{
	strcpy_s(m_UserKey, m_UserId);

	int temp = strlen(m_UserKey);


	for (int i = 0; (temp + i + 1) < 21; i++)
	{
		m_UserKey[temp + i] = m_UserKey[i];
	}


	for (int j = 0; j < 20; j++)
	{
		m_FirstKey[j] = m_CNativeKey[j] & m_UserKey[j];
	}

}


void KKeyGen::Genius()
{
	int temp = strlen(m_GameKey);

	for (int i = 0; (temp + i + 1) < 21; i++)
	{
		m_GameKey[temp + i] = m_GameKey[i];
	}


	for (int j = 0; j < 20; j++)
	{
		m_FirstKey[j] += m_GameKey[j];
		m_FirstKey[j] *= -1;
	}

	
	for (int j = 0; j < 7; j++)
	{
		m_FirstKey[3 * j] = (m_FirstKey[3 * j] % 10) + 48;
		m_FirstKey[3 * j + 1] = (m_FirstKey[3 * j + 1] % 26) + 65;
		m_FirstKey[3 * j + 2] = (m_FirstKey[3 * j + 2] % 26) + 97;
	}
	

	for (int j = 0; j < 20; j++)
	{
		m_FinalKey[j] = m_FirstKey[j];
		if (0 < m_FinalKey[6]) m_FinalKey[6] = 97;
		if (0 < m_FinalKey[15]) m_FinalKey[15] = 71;
	}

}
