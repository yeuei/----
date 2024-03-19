#pragma once
#include "CDround.h"
class CRoundBresenham :virtual public CDround
{
public:
	int mycolor;
public:
	CRoundBresenham(int r = 0, CPoint org = CPoint(0, 0)): CDround(r,org,2) {};
	void ChangePara(int rr, CPoint ss, int color) {
		org = ss;
		r = rr;
		if (color == -1) {
			color = RGB(0, 205, 102);
		}
		mycolor = color;
	}
	void DrawLine(CDC* pDC) {
		int orgx = org.x, orgy = org.y;
		int x, y, d1, d2, direction;
		//初始化坐标相对变化量;
		x = 0;
		y = r;
		int d = 2 * (1 - r);// 判别式1初值。
			while (y >= 0) {
				pDC->SetPixel(orgx + x, orgy + y, mycolor);
				pDC->SetPixel(orgx - x, orgy + y, mycolor);
				pDC->SetPixel(orgx - x, orgy - y, mycolor);
				pDC->SetPixel(orgx + x, orgy - y, mycolor);
				if (d < 0) {// d < 0， 此时需要竖直方向上的判别式d1 = d上 + d下
					d1 = 2 * (d + y) - 1;
					if (d1 <= 0)
						direction = 1;
					else
						direction = 2;
				}
				else if (d > 0) {//d > 0，此时需要水平方向的判别式d2 = d左 + d右
					d2 = 2 * (d - x) - 1;
					if (d2 <= 0)
						direction = 2;
					else
						direction = 3;
				}
				else
					direction = 3;
				//迭代更新
				switch (direction) {
					case 1: {
						x++;
						d += 2 * x + 1;
						break;
					}
					case 2: {
						x++;
						y--;
						d += 2 * (x - y + 1);
						break;
					}
					case 3: {
						y--;
						d += -2 * y + 1;
						break;
					}
				}
			}
	}
};

