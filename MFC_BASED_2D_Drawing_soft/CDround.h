#pragma once
#include "CDraw.h"
class CDround : virtual public CDraw
{
public:
	int r;
	CPoint org;
	int number;
public:
	CDround(int r, CPoint org, int number) : r(r), org(org), number(number), CDraw() {

	}
	virtual void ChangePara(int r, CPoint org, int color) = 0;
	virtual ~CDround() {};
};

