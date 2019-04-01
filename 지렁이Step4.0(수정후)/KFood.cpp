#include "stdafx.h"
#include "KFood.h"



KFood::KFood()
{
	m_x = rand() % 20 * 30;
	m_y = rand() % 20 * 30;
	m_w = 30;
	m_h = 30;
}


KFood::~KFood()
{
}


void KFood::EatFood()
{
	m_x = rand() % 20 * 30;
	m_y = rand() % 20 * 30;
}


void KFood::Draw(HDC hdc)
{
	Ellipse(hdc, m_x, m_y, m_x + m_w, m_y + m_h);
}


void KFood::Poision()
{
	
	flag = rand() % 8 * 25;
}
