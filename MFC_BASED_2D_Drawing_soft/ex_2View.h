
// ex_2View.h: Cex2View 类的接口
//

#pragma once
#include <vector>
#include "CLine2.h"
#include "CRound2.h"
#include "CBezier.h"
#include "CMulLine.h"
#include "CNonCenter.h"
#include "CShowCenter.h"
#include "CTwoInter.h"
#include "COneInter.h"
#include "CNonInter.h"
#include "CNoLine.h"
#include "CByong.h"
#include <fstream>
#include <iostream>
#include <afxdlgs.h> 
#include <set>
#include "CColorPut.h"

class Cex2View : public CView
{
protected: // 仅从序列化创建
	Cex2View() noexcept;
	DECLARE_DYNCREATE(Cex2View)

// 特性
public:
	Cex2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Cex2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	struct CMP {
		bool operator()(CPoint a, CPoint b)const {
			if (a.x == b.x) {
				return a.y < b.y;
			}
			return a.x < b.x;
		}
	};
	afx_msg void OnIdrBezier();
	afx_msg void OnIdrCircle();
	afx_msg void OnIdrLine();
	afx_msg void OnIdrMulLine();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CPoint* SaveBezier(int xifen, CPoint tmps[]);
	void Bresenham_Line(CDC* pDC, class CPoint& st, class CPoint& ed, std::vector<class CPoint>& save);
	void GetPoint(CPoint org, double r, CPoint st, CPoint ed, double& x1, double& y1, double& x2, double& y2, int& check);
	void DrawPoints(CDC* pDC, CPoint& a, int sizes, int color = RGB(255, 0, 0));
	bool ContainsPoint(CPoint point);
	bool is_online(CPoint& st, CPoint& ed, CPoint& np, int i);
	bool is_online(CPoint& st, CPoint& ed, CPoint& np);
	void no_red_select(CDC* pDC);
	void myupdate(CDC* pDC);
	void Fence_Full(CDC* pDC, CPoint a[], int x, int mycolor, int n);
	void LineSeed_begin(CDC* pDC, CPoint a[], int n, int mycolor);
	void Bresenham_Line(class CPoint& st, class CPoint& ed, std::set<CPoint, CMP>& save);
	void LineSeed_FUll(CDC* pDC, CPoint a[], int x, int y, int n, int mycolor, std::vector<CPoint>& stack);
	bool is_in_graph(CPoint a[], int n, int xc, int yc);
public:
	bool right_botton;
	bool left_botton;
	int isput_color = 0;
	bool byong_cal = false;
	std::vector<class CLine2> myline;
	std::vector<class CPoint> mypoint;
	std::vector<class CRound2> myround;
	std::vector<int> myrectcolor;
	std::vector<class CRect> myrect;
	std::vector<class CRect> myrect2;
	std::vector<class CBezier> mybezier;
	std::vector<class CMulLine> mymuline;
	std::vector<class CByong> mybyong;
	std::vector<class CColorPut> mycolordots;
	std::vector<int> myrectdots;

	std::vector<class CLine2> tmpline;
	std::vector<class CPoint> tmppoint;
	std::vector<class CRound2> tmpround;
	std::vector<int> tmprectcolor;
	std::vector<class CRect> tmprect;
	std::vector<class CRect> tmprect2;
	std::vector<class CBezier> tmpbezier;
	std::vector<class CMulLine> tmpmuline;
	std::vector<class CByong> tmpbyong;
	std::vector<class CColorPut> tmpcolordots;
	std::vector<int> tmprectdots;


	
	CGraph* nowgraph;
	CDraw* draw_way;
	CLineBresenham aline;
	CLineCommon bline;
	CLineMiddle cline;
	CLine2 choose_line;
	CRound2 choose_round;
	CRoundBresenham bround;
	CRoundCommon around;
	

	int last_type;
	int last_figure;
	int choice;
	int drawcnt;
	int xifen;
	int tmp_type;
	int tmp_figure;
	int type[2]; //1 直线， 2 圆形；
	int figure1[2];
	int select_num;
	CPoint lastpoint;
	bool is_over_select;
	bool is_first;
	bool is_have_circle;
	bool is_have_inter;
	bool isSelect;
	bool isCross;
	bool quest_vert;
	bool read;
	CDC memdc;
	CBitmap bitmap;
	CPoint sb_st;
	CPoint sb_ed;
	bool gai;
	float x_1[10010] = { 0 };
	float x_2[10010] = { 0 };
	float x_3[10010] = { 0 };
	float x_4[10010] = { 0 };

	std::vector<int> opts; // 矩形框选的图形编号
	std::vector<int> seq; // 矩形框选的图形的内部序号
	int option; // 0: 不进行任何图形变化，1: 平移， 2 : 缩放 3 ： 旋转
	CPoint pre_point;
	CRect select_tangle = (0, 0, 0, 0);
	CRect jietu_tangle = (0, 0, 0, 0);
	CRect show_select_tangle = 0;
	bool is_tuo;

	void isin_tangle(CRect optangle, bool kai = false);
	void dynamic_draw(CDC* pDC); 
	void dynamic_draw_0(CDC* pDC);
	void dynamic_change_color(int color);
	void dynamic_change_all_color(int color);
	void cal_suo(CPoint& a, double xm, double ym, double tmp_x, double tmp_y = 0, bool singleway = true);
	void cal_xuan(CPoint& a, double cc, double ss); // 默认绕着xuan_center转，这是全局变量不需要传参。
	void draw_tangle(CDC* pDC, CRect& rect1, CRect& rect2);
	void no_select_tangle(); // 取消选中所有选择矩形中的东西;
	bool Cex2View::Barsky(CLine2& line);// 梁氏裁剪直线的方法
	void jian_fang(double tmpcx, double tmpcy, CRect& crect); //裁剪放大，会调用到下面的全局平移和缩放函数
	void pingyi(CPoint& Pingyi);
	void suofang(double tmpcx, double tmpcy, CRect &cerect);
	void return_all_vector();
	void xiugai_tangle();

	double tmp_c = 0.5;
	std::vector<CPoint> review;
	CPoint xuan_center;
	CPoint xuan_niu;
	bool is_jian = false;
	bool is_jian2 = false;
	/*DEBUG变量*/
	int test = 0;
	CPoint orgp;
	

	afx_msg void OnIdrRect();
	afx_msg void OnSelecton();
	afx_msg void OnSave();
//	afx_msg void OnIddCenter();
//	afx_msg void OnIddNoncenter();
	afx_msg void OnCenter();
	afx_msg void OnInter();
	afx_msg void OnVertical();
	afx_msg void OnRead();
	afx_msg void OnGai();
	afx_msg void OnIdrMidd();
	afx_msg void OnIdrBre();
	afx_msg void OnPutcolor();
	afx_msg void OnPutcolor2();
	afx_msg void OnIdrBrecir();
	afx_msg void OnIdrBeyond();
	afx_msg void OnPing();
	afx_msg void OnXuan();
	afx_msg void OnSuo();
	afx_msg void OnJian();
	afx_msg void OnJiancai2();
};

#ifndef _DEBUG  // ex_2View.cpp 中的调试版本
inline Cex2Doc* Cex2View::GetDocument() const
   { return reinterpret_cast<Cex2Doc*>(m_pDocument); }
#endif

