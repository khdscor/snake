#pragma once

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class KHead
{
public:
	KHead();
	~KHead();


	int m_x, m_y, m_w, m_h;
	int m_Dir;
	int m_Speed;

	void Move();
	void Draw(HDC hdc);
};

