#pragma once
class KBody
{
public:
	KBody();
	~KBody();

	int m_x, m_y, m_w, m_h;


	void Draw(HDC hdc);
	void Ini(int x, int y);
};

