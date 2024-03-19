#pragma once
class CDraw
{
public:
	CDraw() {}
	virtual void DrawLine(CDC* pDC) = 0;
};

