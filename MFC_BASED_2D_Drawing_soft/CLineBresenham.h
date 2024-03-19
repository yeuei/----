#pragma once
#include "CDline.h"
class CLineBresenham : virtual public CDline
{
	int mycolor;
public:
	CLineBresenham(CPoint st = CPoint(0,0), CPoint ed = CPoint(0,0)) : CDline(st, ed,2) {}
	void ChangePara(CPoint ss, CPoint ee,int color) {
		st = ss;
		ed = ee;
		if (color == -1) {
			color = RGB(0,205,102);
		}
		mycolor = color;
	}
	void DrawLine(CDC* pDC){
		int x, y;
		CPoint true_st = st;
		CPoint true_ed = ed;
		int SX;
		int SY;
		if (true_ed.x - true_st.x >= 0)
			SX = 1;
		else
			SX = -1;
		if (true_ed.y - true_st.y >= 0)
			SY = 1;
		else
			SY = -1;

		int abs_x = abs(true_ed.x - true_st.x);
		int abs_y = abs(true_ed.y - true_st.y);
		x = true_st.x;
		y = true_st.y;

		if (true_ed.x == true_st.x) { // 斜率特判
			//TODO:
			int length = abs(true_ed.y - true_st.y);
			for (int i = 0; i <= length; i++) {
				pDC->SetPixel(x, y, mycolor);
				y += SY;
			}
			return;
		}
		else {// 平常斜率
			double k = fabs((double)(st.y - ed.y) / (st.x - ed.x));
			if (k <= 1) {
				int e = 2 * abs_y - abs_x;
				int length = abs(true_ed.x - true_st.x);
				for (int cnt = 0; cnt <= length; cnt++) {
					pDC->SetPixel(x, y, mycolor);
					x += SX;
					if (e < 0) {
						e += 2 * abs_y;
					}
					else {
						e += 2 * abs_y - 2 * abs_x;
						y += SY;
					}
				}
			}
			else {
				int e = 2 * abs_x - abs_y;
				int length = abs(true_ed.y - true_st.y);
				for (int cnt = 0; cnt <= length; cnt++) {
					pDC->SetPixel(x, y, mycolor);
					y += SY;
					if (e < 0) {
						e += 2 * abs_x;
					}
					else {
						e += 2 * abs_x - 2 * abs_y;
						x += SX;
					}
				}

			}
		}

	}
};

