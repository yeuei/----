#pragma once
#include "CGraph.h"
#include "CLineBresenham.h"
#include "CLineCommon.h"
#include "CLineMiddle.h"
class CLine2 : virtual public CGraph
{
public:
	CPoint st;
	CPoint ed;
	int color = 0;
public:
	CLine2(){ 
		mydraw = NULL;
	}
	CLine2(CPoint a, CPoint b){
		mydraw = NULL;
	hao_ma = 1;
	if(a.x < b.x)
	{
		st.x = a.x;
		st.y = a.y;
		ed.x = b.x;
		ed.y = b.y;
	}
	else {
		st.x = b.x;
		st.y = b.y;
		ed.x = a.x;
		ed.y = a.y;
	}
	}
	void operator =(CLine2& tmps) {
		st = tmps.st;
		ed = tmps.ed;
	}
	void draw_way(CDraw *line) {
		mydraw = line;
	}
};

