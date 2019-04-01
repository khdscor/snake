#include "stdafx.h"
#include "KLogin.h"


KLogin::KLogin()
{
	m_x = 0;
	m_y = 0;
	m_w = 600;
	m_h = 600;
}


KLogin::~KLogin()
{
}


void KLogin::Draw(HDC hdc)
{
	Rectangle(hdc, m_x, m_y, m_x + m_w, m_y + m_h);

	TCHAR msg[20];
	wsprintf(msg, _T("ID: "));
	TextOut(hdc, m_x + m_w / 2 - 20, m_y + m_h / 2, msg, lstrlen(msg));


	TCHAR szUniCode[256] = { 0, }; //<= 반드시 초기화 필요 
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, m_Key, strlen(m_Key), szUniCode, 256);
	TextOut(hdc, m_x + m_w / 2, m_y + m_h / 2, szUniCode, lstrlen(szUniCode));
}


bool KLogin::Check()
{
	if (8 == strlen(m_Key))
	{
		return true;
	}
	return false;
}
