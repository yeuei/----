#pragma once
#include "CDround.h"
class CRoundCommon :virtual public CDround
{
public:
	CRoundCommon(int r = 0, CPoint org = CPoint(0, 0)) : CDround(r, org, 1) {};
	void ChangePara(int rr, CPoint ss,int color) {
		if (color == -1) {
			color = RGB(0, 0, 0);
		}
		org = ss;
		r = rr;
	}
	void  DrawLine(CDC* pDC) {
		CRect rect(org.x - r, org.y - r, org.x + r, org.y + r);
		pDC->Ellipse(rect);
	}
};

