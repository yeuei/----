#pragma once
#include "CDraw.h"
class CGraph
{
public:
	CDraw* mydraw;
	int hao_ma;
	virtual void draw_way(CDraw*) = 0;
};

