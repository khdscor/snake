#pragma once
class KLogin
{
public:
	KLogin();
	~KLogin();

	int m_x, m_y, m_w, m_h;
	int index;
	char m_Key[30];
	TCHAR m_ID[30];

	void Draw(HDC hdc);
	bool Check();
};

