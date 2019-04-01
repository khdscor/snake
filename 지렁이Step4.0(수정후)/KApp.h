#pragma once
#include <iostream>	
#include <stdlib.h>
#include <time.h>
#include "KHead.h"
#include "KBody.h"
#include "KFood.h"
#include "KLogin.h"
#include "KKeyGen.h"
#include <vector>


using namespace std;
class KApp
{
public:
	KApp();
	~KApp();
	void OnCreate(HWND hWnd);
	void OnDraw(HDC hdc);
	void OnKeyDown(int key);
	void OnLButtonDown(int x, int y);
	HWND m_hWnd;

	KHead m_Head;
	KFood m_Food[2];
	KLogin m_Login;
	KKeyGen m_Keygen;
	vector<KBody> m_Bodys;
	int m_BodyLen;
	int m_w, m_h;
	int m_Type;

	void CheckEat();
	void Follow();
	void OnTimer(int id);
	void CheckCrash();
	void Stage();
};

