#pragma once
#include <vector>
class CColorPut
{
public:
	std::vector<class CPoint> colordots;
	int flag = 1;
public:
	CColorPut() { flag = 1; };
	virtual ~CColorPut() {};
};

