#pragma once
#include "CDline.h"
class CLineMiddle : virtual public CDline
{
	int mycolor;
public:
	CLineMiddle(CPoint st = CPoint(0, 0), CPoint ed = CPoint(0, 0)) : CDline(st, ed,1) {};
	void ChangePara(CPoint ss, CPoint ee, int color) {
		st = ss;
		ed = ee;
		if (color == -1) {
			color = RGB(0, 0, 255);
		}
		mycolor = color;
	}
	void DrawLine(CDC* pDC) {
			//保存要画出的起点
			int x;
			int y;
			CPoint true_st = st;
			CPoint true_ed = ed;

			int A = true_st.y - true_ed.y;
			int B = true_ed.x - true_st.x;
			int C = true_st.x * true_ed.y - true_st.y * true_ed.x;
			double M = fabs((double)(st.y - ed.y) / (st.x - ed.x));
			int SX[3] = { 0 }; // x的增量;
			int SY[3] = { 0 }; // y的增量;

			x = true_st.x;
			y = true_st.y;

			if (B <= 0)
				SX[0] = -1, SX[1] = 0, SX[2] = -1;
			else
				SX[0] = 1, SX[1] = 1, SX[2] = 0;
			if (-A <= 0)
				SY[0] = -1, SY[1] = 0, SY[2] = -1;
			else
				SY[0] = 1, SY[1] = 1, SY[2] = 0;

			if (M <= 1) {
				if (B < 0) {
					B = -B;
					A = -A;
					C = -C;
				}
				int delta = 2 * A * SX[0] + B * SY[0];
				int deta_da = 2 * A * SX[0] + 2 * B * SY[1];
				int deta_xiao = 2 * A * SX[0] + 2 * B * SY[2];
				int length = abs(true_ed.x - x);
				for (int cnt = 0; cnt <= length; cnt++) {
					pDC->SetPixel(x, y, mycolor);
					x += SX[0];
					if (delta < 0) {
						delta += deta_da;
						y += SY[1];
					}
					else {
						delta += deta_xiao;
						y += SY[2];
					}
				}
			}
			else {
				if (A > 0) {
					A = -A;
					B = -B;
					C = -C;
				}

				int delta = 2 * B * SY[0] + A * SX[0];
				int deta_da = 2 * B * SY[0] + 2 * A * SX[1];
				int deta_xiao = 2 * B * SY[0] + 2 * A * SX[2];
				int length = abs(true_ed.y - y);
				for (int cnt = 0; cnt <= length; cnt++) {
					pDC->SetPixel(x, y, mycolor);
					y += SY[0];
					if (delta < 0) {
						delta += deta_xiao;
						x += SX[2];
					}
					else {
						delta += deta_da;
						x += SX[1];
					}
				}

			}
	}
};

