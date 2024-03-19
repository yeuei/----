#pragma once
#include "CDline.h"
class CLineCommon : virtual public CDline
{
public:
	CLineCommon(CPoint st = CPoint(0, 0), CPoint ed = CPoint(0, 0)) : CDline(st, ed, 3) { }
	void DrawLine(CDC* pDC){
		pDC->MoveTo(st);
		pDC->LineTo(ed);
	}
	void ChangePara(CPoint ss, CPoint ee, int color){
		if (color == -1) {
			color = RGB(0, 0, 0);
		}
		st = ss;
		ed = ee;
	}
};


