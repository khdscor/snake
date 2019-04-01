#include "stdafx.h"
#include "KApp.h"

#define _CRT_SECURE_NO_WARNNING

KApp::KApp()
{
	m_Type = 0;
	m_w = 600;
	m_h = 600;
	
	m_Food[0].flag = 50;
	m_Food[1].flag = 101;
	
}


KApp::~KApp()
{
}


void KApp::OnCreate(HWND hWnd)
{
	m_hWnd = hWnd;

	SetTimer(m_hWnd, 1, 200,NULL);
	SetTimer(m_hWnd, 2, 250, NULL);
}


void KApp::OnDraw(HDC hdc)
{
	if (0 == m_Type) m_Login.Draw(hdc);
	else
	{
		Rectangle(hdc, 0, 0, m_w, m_h);

		for (int i = 0; i < 2; i++) m_Food[i].Draw(hdc);
		m_Head.Draw(hdc);

		for (int i = 0; i < m_Bodys.size(); i++) m_Bodys[i].Draw(hdc);

		//TCHAR msg[200];
		//wsprintf(msg, _T("Leng : %d flag1 : %d flag2 : %d"), m_BodyLen, m_Food[0].flag, m_Food[1].flag);
		//TextOut(hdc, 100, 90, msg, lstrlen(msg));

		TCHAR ID[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, m_Login.m_Key, strlen(m_Login.m_Key), ID, 256);
		//wsprintf(ID, _T("ID : %s"), m_Login.m_Key);
		TextOut(hdc, 650, 80, ID, lstrlen(ID));

		TCHAR NativeKey[256] = { 0, }; 
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, m_Keygen.m_CNativeKey, strlen(m_Keygen.m_CNativeKey), NativeKey, 256);
		TextOut(hdc, 650, 120, NativeKey, lstrlen(NativeKey));

		TCHAR FirstKey[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, m_Keygen.m_FirstKey, strlen(m_Keygen.m_FirstKey), FirstKey, 256);
		TextOut(hdc, 650, 140, FirstKey, lstrlen(FirstKey));

		TCHAR FinalKey[256] = { 0, };
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, m_Keygen.m_FinalKey, strlen(m_Keygen.m_FinalKey), FinalKey, 256);
		TextOut(hdc, 650, 160, FinalKey, lstrlen(FinalKey));

	}

}

void KApp::OnTimer(int id)
{
	if (1 == m_Type)
	{
		if (1 == id)
		{
			Follow();
			CheckEat();

			m_Head.Move();

			InvalidateRect(m_hWnd, NULL, TRUE);
		}
		if (2 == id)
		{
			CheckCrash();
		}
	}
}



void KApp::OnKeyDown(int key)
{	
	if (0 == m_Type)
	{
		switch (key)
		{
		case VK_RETURN:
			if (true == m_Login.Check()) m_Type = 1;
			
			else MessageBox(m_hWnd, _T("다시 입력해주세요"), _T("잘못된 아이디"), MB_OK);

			strcpy_s(m_Keygen.m_UserId, m_Login.m_Key);

			break;
		case VK_BACK:
			if (0 < m_Login.index)
			{
				m_Login.index--;
				m_Login.m_Key[m_Login.index] = NULL;
				InvalidateRect(m_hWnd, NULL, TRUE);
			}

			break;
		default:
			key = tolower(key);
			m_Login.m_Key[m_Login.index] = key;
			m_Login.index++;
			m_Login.m_Key[m_Login.index] = 0;
			
			break;
		}
	}

	if (1 == m_Type)
	{
		switch (key)
		{
		case VK_UP:
			if (VK_DOWN == m_Head.m_Dir) m_Head.m_Dir = VK_DOWN;
			else m_Head.m_Dir = VK_UP;

			break;
		case VK_DOWN:
			if (VK_UP == m_Head.m_Dir) m_Head.m_Dir = VK_UP;
			else m_Head.m_Dir = VK_DOWN;

			break;
		case VK_LEFT:
			if (VK_RIGHT == m_Head.m_Dir) m_Head.m_Dir = VK_RIGHT;
			else m_Head.m_Dir = VK_LEFT;

			break;
		case VK_RIGHT:
			if (VK_LEFT == m_Head.m_Dir) m_Head.m_Dir = VK_LEFT;
			else m_Head.m_Dir = VK_RIGHT;
			break;
		default:
			break;
		}
	}

	InvalidateRect(m_hWnd, NULL, TRUE);
}


void KApp::CheckEat()
{
	RECT HEAD = { m_Head.m_x, m_Head.m_y, m_Head.m_x + m_Head.m_w, m_Head.m_y + m_Head.m_h };
	
	for (int i = 0; i < 2; i++)
	{
		RECT FOOD = { m_Food[i].m_x, m_Food[i].m_y, m_Food[i].m_x + m_Food[i].m_w, m_Food[i].m_y + m_Food[i].m_h };
		RECT CRASH;

		if (TRUE == IntersectRect(&CRASH, &HEAD, &FOOD))
		{
			srand((unsigned int)time(NULL));

			if (0 <= m_Food[i].flag && m_Food[i].flag <= 100)  // 음식 먹으면 죽는부분
			{
					/*KillTimer(m_hWnd, 1);
					KillTimer(m_hWnd, 2);
					MessageBox(m_hWnd, _T("GameOver"), _T("Info"), MB_OK);
					exit(1);*/

				KBody body;
				body.Ini(m_Food[i].m_x, m_Food[i].m_y);
				m_Bodys.push_back(body);
				m_BodyLen++;
				Stage();
			
			}
			else if (101 <= m_Food[i].flag && m_Food[i].flag <= 200)
			{
				KBody body;
				body.Ini(m_Food[i].m_x, m_Food[i].m_y);
				m_Bodys.push_back(body);
				m_BodyLen++;
				Stage();
			}
			for (int j = 0; j<2; j++)
			{
				m_Food[j].Poision();
				m_Food[j].EatFood();
			}
			
		}
	}
}


void KApp::Follow()
{
	if (1 <= m_BodyLen)
	{
		for (int i = m_Bodys.size() - 1; i > 0; i--)
		{
			m_Bodys[i].m_x = m_Bodys[i - 1].m_x;
			m_Bodys[i].m_y = m_Bodys[i - 1].m_y;
		}

		m_Bodys[0].m_x = m_Head.m_x;
		m_Bodys[0].m_y = m_Head.m_y;

	}
}

void KApp::CheckCrash()
{
	RECT Head = { m_Head.m_x, m_Head.m_y, m_Head.m_x + m_Head.m_w, m_Head.m_y + m_Head.m_h };
	
	for (int i = 0; i < m_Bodys.size(); i++)
	{
		RECT Body = { m_Bodys[i].m_x, m_Bodys[i].m_y, m_Bodys[i].m_x + m_Bodys[i].m_w, m_Bodys[i].m_y + m_Bodys[i].m_h };
		RECT Crash;

		if (TRUE == IntersectRect(&Crash, &Head, &Body))
		{
			KillTimer(m_hWnd, 1);
			KillTimer(m_hWnd, 2);
			MessageBox(m_hWnd, _T("GameOver"), _T("Info"), MB_OK);
			exit(1);
		}
	}

	if (m_Head.m_x < 0 || m_w < m_Head.m_x + m_Head.m_w)
	{
		KillTimer(m_hWnd, 1);
		KillTimer(m_hWnd, 2);
		MessageBox(m_hWnd, _T("GameOver"), _T("Info"), MB_OK);
		exit(1);
	}
	else if (m_Head.m_y < 0 || m_h < m_Head.m_y + m_Head.m_h)
	{
		KillTimer(m_hWnd, 1);
		KillTimer(m_hWnd, 2);
		MessageBox(m_hWnd, _T("GameOver"), _T("Info"), MB_OK);
		exit(1);
	}


}



void KApp::OnLButtonDown(int x, int y)
{
}





void KApp::Stage()
{
	m_Keygen.Run(m_BodyLen);
}
