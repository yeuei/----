#pragma once
class CBezier
{
public:
	CPoint st;
	CPoint ed;
	CPoint ctr1;
	CPoint ctr2;
	int color = 0;
public:
	CBezier() { };
	CBezier(CPoint st, CPoint ed, CPoint ctr1, CPoint ctr2) 
	{
		this->st = st;
		this->ed = ed;
		this->ctr1 = ctr1;
		this->ctr2 = ctr2;
	}
	void operator =(CBezier& a) {
		this->st = a.st;
		this->ed = a.ed;
		this->ctr1 = a.ctr1;
		this->ctr2 = a.ctr2;
	}
	virtual ~CBezier() {};
};

