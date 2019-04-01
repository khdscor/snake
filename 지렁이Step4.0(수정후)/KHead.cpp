#include "stdafx.h"
#include "KHead.h"


KHead::KHead()
{
	m_x = 300;
	m_y = 300;
	m_w = 30;
	m_h = 30;

	m_Speed = 30;
}


KHead::~KHead()
{
}


void KHead::Move()
{
	switch (m_Dir)
	{
	case VK_UP:
		m_y -= m_Speed;
		break;
	case VK_DOWN:
		m_y += m_Speed;
		break;
	case VK_LEFT:
		m_x -= m_Speed;
		break;
	case VK_RIGHT:
		m_x += m_Speed;
		break;
	}
}


void KHead::Draw(HDC hdc)
{
	Rectangle(hdc, m_x, m_y, m_x + m_w, m_y + m_h);
}
