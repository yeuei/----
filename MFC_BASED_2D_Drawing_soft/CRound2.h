#pragma once
#include "CGraph.h"
#include "CRoundBresenham.h"
#include "CRoundCommon.h"
class CRound2 : virtual public CGraph
{
public:
	CPoint org;
	int r;
	int color = 0;
public:
	CRound2() {};
	CRound2(CPoint org, int r) : org(org), r(r) {};
	virtual ~CRound2() {}
	void draw_way(CDraw* round) {
		mydraw = round;
	}
};

