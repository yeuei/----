#pragma once
#include "CDraw.h"
class CDline : virtual public CDraw
{
public:
	CPoint st;
	CPoint ed;
	int number;
	CDline(CPoint ss, CPoint ee, int number) : st(ss), ed(ee), number(number), CDraw() {
	}
	virtual void ChangePara(CPoint ss, CPoint ee, int color) = 0;
	virtual ~CDline() {};
};

