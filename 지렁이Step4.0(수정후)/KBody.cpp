#include "stdafx.h"
#include "KBody.h"


KBody::KBody()
{
	m_w = 30;
	m_h = 30;
}


KBody::~KBody()
{
}

void KBody::Ini(int x, int y)
{
	m_x = x;
	m_y = y;
}


void KBody::Draw(HDC hdc)
{
	Ellipse(hdc, m_x, m_y, m_x + m_w, m_y + m_h);
}


