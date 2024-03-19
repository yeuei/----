#pragma once
class CByong
{public:
	int n;
	CPoint* bpoint;
	int color = 0;
public:
	CByong(int n, CPoint a[]) : n(n) {
		bpoint = a;
	};
	~CByong() {};
};

