#pragma once
#include <iostream>	
#include <stdlib.h>
#include <time.h>

using namespace std;
class KFood
{
public:
	KFood();
	~KFood();

	int m_x, m_y, m_w, m_h;
	int flag;
	
	void EatFood();
	void Draw(HDC hdc);

	
	void Poision();
};

