#pragma once
class CMulLine
{
public:
	int num;
	CPoint* muline;
	int color = 0;
	int dots = -1;
	int leibie = 0; // 0 : ¶àÒåÏß£¬ 1 £ºBezier
	int map_bezier = -1;
public:
	CMulLine() { dots = -1; leibie = 0; map_bezier = -1;
	};
	CMulLine(int n, CPoint a[])
	{
		num = n;
		muline = a;
		dots = -1;
		leibie = 0;
		map_bezier = -1;
	}
	void operator = (CMulLine a) {
		this->num = a.num;
		this->muline = a.muline;
		this->dots = a.dots;
		this->leibie = a.leibie;
		this->map_bezier = a.map_bezier;
	}
	virtual ~CMulLine() {};
};

