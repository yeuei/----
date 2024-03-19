
// ex_2View.cpp: Cex2View 类的实现
//

#include "pch.h"
#include "framework.h"

// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ex_2.h"
#endif

#include "ex_2Doc.h"
#include "ex_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cex2View

IMPLEMENT_DYNCREATE(Cex2View, CView)

BEGIN_MESSAGE_MAP(Cex2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDR_bezier, &Cex2View::OnIdrBezier)
	ON_COMMAND(IDR_CIRCLE, &Cex2View::OnIdrCircle)
	ON_COMMAND(IDR_LINE, &Cex2View::OnIdrLine)
	ON_COMMAND(IDR_MUL_LINE, &Cex2View::OnIdrMulLine)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDR_RECT, &Cex2View::OnIdrRect)
	ON_COMMAND(IDM_SELECTON, &Cex2View::OnSelecton)
	ON_COMMAND(IDM_SAVE, &Cex2View::OnSave)
//	ON_COMMAND(IDD_CENTER, &Cex2View::OnIddCenter)
//	ON_COMMAND(IDD_NONCENTER, &Cex2View::OnIddNoncenter)
	ON_COMMAND(IDM_CENTER, &Cex2View::OnCenter)
	ON_COMMAND(IDM_INTER, &Cex2View::OnInter)
	ON_COMMAND(IDM_VERTICAL, &Cex2View::OnVertical)
	ON_COMMAND(IDM_READ, &Cex2View::OnRead)
	ON_COMMAND(IDM_GAI, &Cex2View::OnGai)
	ON_COMMAND(IDR_MIDD, &Cex2View::OnIdrMidd)
	ON_COMMAND(IDR_bre, &Cex2View::OnIdrBre)
	ON_COMMAND(IDM_PUTCOLOR, &Cex2View::OnPutcolor)
	ON_COMMAND(IDM_PUTCOLOR2, &Cex2View::OnPutcolor2)
	ON_COMMAND(IDR_BRECIR, &Cex2View::OnIdrBrecir)
	ON_COMMAND(IDR_beyond, &Cex2View::OnIdrBeyond)
	ON_COMMAND(IDC_PING, &Cex2View::OnPing)
	ON_COMMAND(IDC_XUAN, &Cex2View::OnXuan)
	ON_COMMAND(IDC_SUO, &Cex2View::OnSuo)
	ON_COMMAND(IDC_JIAN, &Cex2View::OnJian)
	ON_COMMAND(IDC_JIANCAI2, &Cex2View::OnJiancai2)
END_MESSAGE_MAP()

// Cex2View 构造/析构

Cex2View::Cex2View() noexcept
{
	// TODO: 在此处添加构造代码
	right_botton = false;
	left_botton = false;
	quest_vert = false;
	choice = 0; // 0:代表无 1:直线 2:圆 3:曲线 4:多义线 
	drawcnt = 0;
	xifen = 25;
	isSelect = false;
	memset(type, 0, 2*sizeof(int)); //1 直线， 2 圆形；
	memset(figure1, 0, 2*sizeof(int));
	select_num = 0;
	is_over_select = false;
	isCross = false;
	tmp_figure = -1;
	tmp_type = -1;
	last_figure = -1;
	last_type = -1;
	choice = 0;
	read = false;
	gai = false;
	nowgraph = &choose_line;
	draw_way = &bline;
	nowgraph->draw_way(draw_way);
	option = 0;
	is_tuo = false;
}

Cex2View::~Cex2View()
{
}

BOOL Cex2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Cex2View 绘图

void Cex2View::OnDraw(CDC* /*pDC*/)
{
	Cex2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CDC* pDC = GetDC();
	// TODO: 在此处为本机数据添加绘制代码
	if (!memdc.m_hDC )
	{
		memdc.CreateCompatibleDC(pDC);
		CRect rect;
		GetClientRect(&rect);                  //获取画布大小  
		bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
		memdc.SelectObject(&bitmap);
		memdc.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);
		//将屏幕DC的图像复制到内存DC中
		memdc.SelectStockObject(NULL_BRUSH);
	}
	if(pDC)
	{
		CRect rect1;
		GetClientRect(&rect1);
		pDC->BitBlt(0, 0, rect1.Width(), rect1.Height(), &memdc, 0, 0, SRCCOPY);
	}
}
void Cex2View::myupdate(CDC* pDC) {
	if(pDC)
	{
		CRect rect1;
		GetClientRect(&rect1);
		pDC->BitBlt(0, 0, rect1.Width(), rect1.Height(), &memdc, 0, 0, SRCCOPY);
	}
}
// Cex2View 打印

BOOL Cex2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Cex2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Cex2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// Cex2View 诊断

#ifdef _DEBUG
void Cex2View::AssertValid() const
{
	CView::AssertValid();
}

void Cex2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cex2Doc* Cex2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cex2Doc)));
	return (Cex2Doc*)m_pDocument;
}
#endif //_DEBUG


// Cex2View 消息处理程序


void Cex2View::OnIdrBezier()
{
	// TODO: 在此添加命令处理程序代码
	choice = 3;
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}


void Cex2View::OnIdrCircle()
{
	// TODO: 在此添加命令处理程序代码
	choice = 2;
	nowgraph = &choose_round;
	draw_way = &around;
	nowgraph->draw_way(draw_way);
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}


void Cex2View::OnIdrLine()
{
	// TODO: 在此添加命令处理程序代码
	choice = 1;
	nowgraph = &choose_line;
	draw_way = &bline;
	nowgraph->draw_way(draw_way);
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}


void Cex2View::OnIdrMulLine()
{
	// TODO: 在此添加命令处理程序代码
	choice = 4;
	nowgraph = &choose_line;
	draw_way = &bline;
	nowgraph->draw_way(draw_way);
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}


void Cex2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnLButtonDown(nFlags, point);
	left_botton = true;
	if(choice)
	{
		mypoint.push_back(point);
		if (choice == 3)
		{
			++drawcnt;
			CDC* pDC = GetDC();
			CBrush* pOldBrush;
			CBrush mybrush;
			mybrush.CreateSolidBrush(RGB(0, 0, 0));
			pOldBrush = memdc.SelectObject(&mybrush);
			int thickness = 5; // 点的粗细
			CRect rect(point.x - thickness / 2, point.y - thickness / 2, point.x + thickness / 2, point.y + thickness / 2);
			memdc.SelectObject(pOldBrush);
			mybrush.DeleteObject();
			//ReleaseDC(pDC);
			myupdate(GetDC());
			//Invalidate();
			if (drawcnt == 2)
			{
				is_first = true;
			}
		}
		else if (choice == 4) // 多义线
		{
			CDC* pDC = GetDC();
			CPen mypen1;
			mypen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			memdc.SelectObject(&mypen1);
			left_botton = false;
			int sizes = mypoint.size();
			CPoint* tmp_points = new CPoint[sizes];
			if (sizes > 1) {
				if ((mypoint[sizes - 1].x - mypoint[0].x) * (mypoint[sizes - 1].x - mypoint[0].x) + (mypoint[sizes - 1].y - mypoint[0].y) * (mypoint[sizes - 1].y - mypoint[0].y) <= 2500)
				{
					mypoint[sizes - 1] = mypoint[0];
					CLine2 tmps(mypoint[sizes-2], mypoint[sizes - 1]);
					myline.push_back(tmps);
					CDline* lineptr = dynamic_cast<CDline*>(draw_way);
					if (lineptr) {
						lineptr->ChangePara(mypoint[sizes - 1], mypoint[sizes - 2], -1);
					}
					(nowgraph->mydraw)->DrawLine(&memdc);
					int sizes = mypoint.size();
					CPoint* tmp_points = new CPoint[sizes];
					for (int i = 0; i < sizes; i++)
					{
						tmp_points[sizes - i - 1] = mypoint.back();
						mypoint.pop_back();
					}
					int cnt = 1;
					while (cnt < sizes) {
						myline.pop_back();
						cnt++;
					}
					CMulLine tmp_a(sizes - 1, tmp_points);
					mymuline.push_back(tmp_a);
					choice = 0;
					myupdate(GetDC());
					return;
				}
				CDline* lineptr = dynamic_cast<CDline*>(draw_way);
				if (lineptr) {
					lineptr->ChangePara(mypoint[sizes - 1], mypoint[sizes - 2], -1);
				}
				(nowgraph->mydraw)->DrawLine(&memdc);
				CLine2 tmps(mypoint[sizes - 2], mypoint[sizes - 1]);
				myline.push_back(tmps);
				//ReleaseDC(pDC);
			}
			myupdate(GetDC());
			//Invalidate();
		}
		else if (choice == 6)
		{
			CDC *pDC = GetDC();
			CPen mypen1;
			mypen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			memdc.SelectObject(&mypen1);
			left_botton = false;
			int sizes = mypoint.size();
			CPoint* tmp_points = new CPoint[sizes];
			DrawPoints(pDC, mypoint[sizes - 1], 10);
			if (sizes > 3) {
				for (int i = 0; i <= 2000; i++) {
					int x = 0, y = 0;
					int tmpn = sizes - 1;
					x = (x_4[i] * mypoint[tmpn].x + x_3[i] * mypoint[tmpn - 1].x + x_2[i] * mypoint[tmpn - 2].x + x_1[i] * mypoint[tmpn - 3].x)/6;
					y = (x_4[i] * mypoint[tmpn].y + x_3[i] * mypoint[tmpn - 1].y + x_2[i] * mypoint[tmpn - 2].y + x_1[i] * mypoint[tmpn - 3].y)/6;
					//DrawPoints(pDC, CPoint(x, y),10);
					//myupdate(GetDC());
					memdc.SetPixel(x,y,RGB(0,0,0));
				}
				myupdate(GetDC());
				CPen mypen2;
				mypen2.CreatePen(PS_DASH, 1, RGB(255, 0, 0));
				pDC->SelectObject(&mypen2);
				DrawPoints(pDC, mypoint[sizes - 1], 10);
				for (int i = sizes - 1, j = sizes - 3; i >= sizes - 3; i--) {
					pDC->MoveTo(mypoint[i]);
					pDC->LineTo(mypoint[j]);
					j = i;
				}
				pDC->MoveTo(mypoint[sizes - 2]);
				CPoint tmpmid = mypoint[sizes - 1] + mypoint[sizes - 3];
				pDC->LineTo(tmpmid.x/2,tmpmid.y/2);
				DrawPoints(pDC, CPoint(tmpmid.x / 6 + mypoint[sizes - 2].x * 2 / 3, tmpmid.y / 6 + mypoint[sizes - 2].y * 2 / 3), 10);
				mypen2.DeleteObject();
				ReleaseDC(pDC);
			}
			//Invalidate();
		}
	}
	else if(!choice){
		mypoint.push_back(point);
		if (option == 0) {
			dynamic_change_color(RGB(0, 0, 0));
			while (!opts.empty())
				opts.pop_back();
			while (!seq.empty())
				seq.pop_back();
			dynamic_draw(GetDC());
		}

		if (isCross) {
			//last 是用来消除的
			//tmp 是用来指示上色的（如果不是反向取消的话）
			if (!is_over_select) {
				if (select_num) {
					//之前仅选择过一个的情况;
					if (tmp_type == type[0] && tmp_figure == figure1[0]) {
						//之前仅仅选了一个，但是这次又取消了;
						last_type = tmp_type;
						last_figure = tmp_figure;
						tmp_type = -1;

						select_num = 0;
					}
					else {
						last_type = -1;
						last_type = -1;

						type[select_num] = tmp_type;
						figure1[select_num] = tmp_figure;
						is_over_select = true;
						select_num = 0;
					}
				}
				else {//之前啥都没选过;现在select_num == 0
					last_type = -1;
					last_type = -1;

					type[select_num] = tmp_type;
					figure1[select_num] = tmp_figure;
					select_num = 1;
				}
			}
			else { // 如果已经选了两个了
				if (tmp_type == type[0] && tmp_figure == figure1[0]) { // 当前选的和第一个重叠了;
					last_type = tmp_type;
					last_figure = tmp_figure;
					tmp_type = -1;

					type[0] = type[1];
					figure1[0] = figure1[1];
					is_over_select = false;
					select_num = 1;
				}
				else if(tmp_type == type[1] && tmp_figure == figure1[1]){
					last_type = tmp_type;
					last_figure = tmp_figure;
					tmp_type = -1;

					is_over_select = false;
					select_num = 1;
				}
				else {
					last_type = type[select_num];
					last_figure = figure1[select_num];
					
					type[select_num] = tmp_type;
					figure1[select_num] = tmp_figure;
					select_num = (select_num + 1) % 2;
				}
			}
			if (tmp_type == 1) {
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				old = memdc.SelectObject(&mypen);
				CPoint st(myline[tmp_figure].st), ed(myline[tmp_figure].ed);
				myline[tmp_figure].color = RGB(255, 0, 0);
				memdc.MoveTo(st);
				memdc.LineTo(ed);
				memdc.SelectObject(old);
				mypen.DeleteObject();
				//ReleaseDC(pDC);
				myupdate(GetDC());
				//Invalidate();
			}
			else if (tmp_type == 2) {
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				myround[tmp_figure].color = RGB(255, 0, 0);
				old = memdc.SelectObject(&mypen);
				CBrush* pOldBrush;
				CBrush nullBrush;
				nullBrush.CreateStockObject(NULL_BRUSH);
				pOldBrush = memdc.SelectObject(&nullBrush);
				CPoint center(myround[tmp_figure].org);
				int radius = myround[tmp_figure].r;
				CRect rect(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
				memdc.Ellipse(rect);
				memdc.SelectObject(old);
				mypen.DeleteObject();
				//ReleaseDC(pDC);
				myupdate(GetDC());
				//Invalidate();
			}
			else if (tmp_type == 3) {
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				mymuline[tmp_figure].color = RGB(255, 0, 0);
				old = memdc.SelectObject(&mypen);
				CPoint* pts = mymuline[tmp_figure].muline;
				if(mymuline[tmp_figure].leibie == 0)
				{
					int nn = mymuline[tmp_figure].num;
					for (int i = 0; i < nn; i++) {
						memdc.MoveTo(pts[i]);
						memdc.LineTo(pts[i + 1]);
					}

					memdc.SelectObject(old);
					mypen.DeleteObject();
					//ReleaseDC(pDC);
					//Invalidate();
				}
				else if (mymuline[tmp_figure].leibie == 1) {
					auto& tmpbs = mybezier[mymuline[tmp_figure].map_bezier];
					CPen mypen2;
					CPen* old;
					mypen2.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
					tmpbs.color = RGB(255, 0, 0);
					old = memdc.SelectObject(&mypen2);
					CPoint tmp[4];
					tmp[0] = tmpbs.st;
					tmp[1] = tmpbs.ctr1;
					tmp[2] = tmpbs.ctr2;
					tmp[3] = tmpbs.ed;
					memdc.PolyBezier(tmp, 4);
					memdc.SelectObject(old);
					mypen2.DeleteObject();
				}
				myupdate(GetDC());
			}
			else if (tmp_type == 5) {
				CDC* pDC = GetDC();
				CPen mypen,*old;
				CBrush* pOldBrush;
				CBrush nullBrush;
				nullBrush.CreateStockObject(NULL_BRUSH);
				pOldBrush = memdc.SelectObject(&nullBrush);
				mypen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				myrectcolor[tmp_figure] = RGB(255, 0, 0);
				old = memdc.SelectObject(&mypen);

				CRect aa(myrect[tmp_figure]);
				CRect aa2(myrect2[tmp_figure]);

				draw_tangle(&memdc,aa,aa2);
				//memdc.Rectangle(aa);
				
				memdc.SelectObject(old);
				mypen.DeleteObject();
				nullBrush.DeleteObject();
				//ReleaseDC(pDC);
				//Invalidate();
				myupdate(GetDC());
			}
			else if (tmp_type == 6) {
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				mybyong[tmp_figure].color = RGB(255, 0, 0);
				old = memdc.SelectObject(&mypen);
				CPoint* mypoint = mybyong[tmp_figure].bpoint;
				int n_byong = mybyong[tmp_figure].n;
				for(int k = 0; k < n_byong - 3; k++){
					for (int i = 0; i <= 2000; i++) {
						int x = 0, y = 0;
						x = (x_4[i] * mypoint[k].x + x_3[i] * mypoint[k + 1].x + x_2[i] * mypoint[k+2].x + x_1[i] * mypoint[k+3].x) / 6;
						y = (x_4[i] * mypoint[k].y + x_3[i] * mypoint[k + 1].y + x_2[i] * mypoint[k+2].y + x_1[i] * mypoint[k+3].y) / 6;
						memdc.SetPixel(x, y, RGB(255, 0, 0));
					}
				}
					memdc.SelectObject(old);
					mypen.DeleteObject();
					myupdate(GetDC());
			}
			if(last_type == 1)
			{
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				myline[last_figure].color = RGB(0, 0, 0);
				old = memdc.SelectObject(&mypen);
				CPoint st(myline[last_figure].st), ed(myline[last_figure].ed);
				//(nowgraph->mydraw)->DrawLine(&memdc);
				memdc.MoveTo(st);
				memdc.LineTo(ed);
				myupdate(GetDC());
				memdc.SelectObject(old);
				mypen.DeleteObject();
				//ReleaseDC(pDC);
				//Invalidate();
				myupdate(GetDC());
				int wait = 0;
			}
			else if(last_type == 2){
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				myround[last_figure].color = RGB(0, 0, 0);
				old = memdc.SelectObject(&mypen);
				CBrush* pOldBrush;
				CBrush nullBrush;
				nullBrush.CreateStockObject(NULL_BRUSH);
				pOldBrush = memdc.SelectObject(&nullBrush);
				CPoint center(myround[last_figure].org);
				int radius = myround[last_figure].r;
				CRect rect(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
				memdc.Ellipse(rect);
				memdc.SelectObject(old);
				mypen.DeleteObject();
				//ReleaseDC(pDC);
				//Invalidate();
				myupdate(GetDC());
			}
			else if (last_type == 3) {
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				mymuline[last_figure].color = RGB(0, 0, 0);
				old = memdc.SelectObject(&mypen);
				CPoint* pts = mymuline[last_figure].muline;
				if(mymuline[last_figure].leibie == 0)
				{
					int nn = mymuline[last_figure].num;
					for (int i = 0; i < nn; i++) {
						memdc.MoveTo(pts[i]);
						memdc.LineTo(pts[i + 1]);
						if (i != nn - 1) {
							DrawPoints(pDC, pts[i + 1], 3);
						}
					}

					memdc.SelectObject(old);
					mypen.DeleteObject();
					//ReleaseDC(pDC);
					//Invalidate();
				}
				else if (mymuline[last_figure].leibie == 1) {
					auto& tmpbs = mybezier[mymuline[last_figure].map_bezier];
					CPen mypen2;
					CPen* old;
					mypen2.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
					tmpbs.color = RGB(0, 0, 0);
					old = memdc.SelectObject(&mypen2);
					CPoint tmp[4];
					tmp[0] = tmpbs.st;
					tmp[1] = tmpbs.ctr1;
					tmp[2] = tmpbs.ctr2;
					tmp[3] = tmpbs.ed;
					memdc.PolyBezier(tmp, 4);
					memdc.SelectObject(old);
					mypen2.DeleteObject();
				}
				myupdate(GetDC());
			}
			else if (last_type == 5)
			{
				CDC* pDC = GetDC();
				CPen mypen, * old;
				CBrush* pOldBrush;
				CBrush nullBrush;
				nullBrush.CreateStockObject(NULL_BRUSH);
				pOldBrush = memdc.SelectObject(&nullBrush);
				mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				myrectcolor[last_figure] = RGB(0, 0, 0);
				old = memdc.SelectObject(&mypen);

				CRect aa(myrect[last_figure]);
				CRect aa2(myrect2[last_figure]);
				draw_tangle(&memdc, aa, aa2);
				//memdc.Rectangle(aa);
				
				memdc.SelectObject(old);
				memdc.SelectObject(pOldBrush);
				nullBrush.DeleteObject();
				mypen.DeleteObject();
				//ReleaseDC(pDC);
				//Invalidate();
				myupdate(GetDC());
			}
			else if (last_type == 6) {
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				mybyong[last_figure].color = RGB(0, 0, 0);
				old = memdc.SelectObject(&mypen);
				CPoint* mypoint = mybyong[last_figure].bpoint;
				int n_byong = mybyong[last_figure].n;
				for (int k = 0; k < n_byong - 3; k++) {
					for (int i = 0; i <= 2000; i++) {
						int x = 0, y = 0;
						x = (x_4[i] * mypoint[k].x + x_3[i] * mypoint[k + 1].x + x_2[i] * mypoint[k + 2].x + x_1[i] * mypoint[k + 3].x) / 6;
						y = (x_4[i] * mypoint[k].y + x_3[i] * mypoint[k + 1].y + x_2[i] * mypoint[k + 2].y + x_1[i] * mypoint[k + 3].y) / 6;
						memdc.SetPixel(x, y, RGB(0, 0, 0));
					}
				}
				memdc.SelectObject(old);
				mypen.DeleteObject();
				myupdate(GetDC());
			}
		}
	}
	if (!choice && option) {
		pre_point = point;
		if (option == 1) {
			is_tuo = true;
		}
		else if (option == 2) {
			is_tuo = true;
		}
		else if (option == 3 ) {
			int x = pre_point.x - xuan_niu.x;
			int y = pre_point.y - xuan_niu.y;
			if (x * x + y * y <= 2500)
				is_tuo = true;
		}
		test++;
	}
	if (quest_vert) {
		quest_vert = false;
		int figure = 0;
		int flag = false;;
		for (int i = 0; i < (is_over_select ? 2 : select_num); i++) {
			if (type[i] == 1) {
				figure = figure1[i];
				flag = true;
				break;
			}
		}
		if(!flag){
			CNoLine noline;
			noline.DoModal();
			return;
		}
		CPoint st, ed;
		st = myline[figure].st;
		ed = myline[figure].ed;
		int A1, A2, B1, B2, C1, C2;
		A1 = st.y - ed.y;
		B1 = ed.x - st.x;
		C1 = st.x * ed.y - ed.x * st.y;
		A2 = B1;
		B2 = -A1;
		C2 = -A2 * point.x - B2 * point.y;

		double x0 = (double)(C2 * B1 - C1 * B2) / (B2 * A1 - B1 * A2);
		double y0 = (double)(A2 * C1 - A1 * C2) / -(A2 * B1 - A1 * B2);

		CDC* pDC = GetDC();
		CPen mypen, * old;
		mypen.CreatePen(PS_DASH, 1, RGB(0, 0, 200));
		old = memdc.SelectObject(&mypen);
		memdc.MoveTo(point);
		memdc.LineTo(int(x0), int(y0));
		if ((x0 - st.x) * (x0 - ed.x) + (y0 - st.y) * (y0 - ed.y) > 0)
			if (abs(st.x - x0) <= abs(ed.x - x0) && abs(st.y - y0) <= abs(ed.y - y0))
				memdc.LineTo(st);
			else
				memdc.LineTo(ed);
		memdc.SelectObject(old);
		mypen.DeleteObject();
		//ReleaseDC(pDC);
		//Invalidate();
		myupdate(GetDC());
	}
	//Invalidate();
}

void Cex2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);

	if (!choice && option) {
		is_tuo = false;
		select_tangle = show_select_tangle;
		if (!review.empty()) { // 恢复缩放或者旋转的最后模样。
			int type = -1, num = -1, nn = opts.size();
			// 如果为旋转，则先恢复旋转按钮
			if (option == 3) {
				xuan_niu = review.back();
				review.pop_back();
			}

			for (int i = nn - 1; i >= 0; i--) {
				type = opts[i];
				num = seq[i];
				if (type == 6) { // B样条
					CPoint* Point_xifen = mybyong[num].bpoint;
					int tmpn = mybyong[num].n;
					for (int j = 0; j < tmpn; j++) {
						Point_xifen[j] = review.back();
						review.pop_back();
					}
				}
				else if (type == 5) { // 矩形
					myrect2[num].right = review.back().x;
					myrect2[num].bottom = review.back().y;
					review.pop_back();
					myrect2[num].left = review.back().x;
					myrect2[num].top = review.back().y;
					review.pop_back();

					myrect[num].right = review.back().x;
					myrect[num].bottom = review.back().y;
					review.pop_back();
					myrect[num].left = review.back().x;
					myrect[num].top = review.back().y;
					review.pop_back();
				}
				else if (type == 4) { //bezier
					mybezier[num].ctr2 = review.back();
					review.pop_back();
					mybezier[num].ctr1 = review.back();
					review.pop_back();
					mybezier[num].ed = review.back();
					review.pop_back();
					mybezier[num].st = review.back();
					review.pop_back();
				}
				else if (type == 3) { //多义线
					CPoint* Point_xifen = mymuline[num].muline;
					int tmpn = mymuline[num].num;
					for (int j = tmpn; j >= 0; j--) {
						Point_xifen[j] = review.back();
						review.pop_back();
					}
				}
				else if (type == 2) {
					myround[num].r = review.back().x;
					review.pop_back();
					myround[num].org = review.back();
					review.pop_back();
				}
				else if (type == 1) {
					myline[num].ed = review.back();
					review.pop_back();
					myline[num].st = review.back();
					review.pop_back();
				}
			}
			dynamic_draw(GetDC());
		}
	}
	if(choice == 1 && left_botton)
	{
		CDC* pDC = GetDC();
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		memdc.SelectObject(&mypen1);
		left_botton = false;
		mypoint.push_back(point);
		CPoint ed(mypoint.back());
		mypoint.pop_back();
		CPoint st(mypoint.back());
		mypoint.pop_back();
		CLine2 tmps(st, ed);
		CDline* lineptr = dynamic_cast<CDline*>(draw_way);
		if (lineptr) {
			lineptr->ChangePara(st, ed, 0);
		}
		(nowgraph->mydraw)->DrawLine(&memdc);
		//memdc.MoveTo(tmps.st);
		//memdc.LineTo(tmps.ed);
		myline.push_back(tmps);
		//mypen1.DeleteObject();
		//ReleaseDC(pDC);
		myupdate(GetDC());
		//Invalidate();
	}
	else if(choice == 2 && left_botton) {
		CDC* pDC = GetDC();
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		memdc.SelectObject(&mypen1);
		CBrush* pOldBrush;
		CBrush nullBrush;
		nullBrush.CreateStockObject(NULL_BRUSH);
		pOldBrush = memdc.SelectObject(&nullBrush);
		left_botton = false;
		mypoint.push_back(point);
		CPoint ed(mypoint.back());
		mypoint.pop_back();
		CPoint st(mypoint.back());
		mypoint.pop_back();
		int radius = (int)sqrt(pow(st.x - ed.x, 2) + pow(st.y - ed.y, 2)) / 2;
		CPoint center((st.x + ed.x) / 2, (st.y + ed.y) / 2);
		//CRect rect(center.x - radius, center.y - radius, center.x + radius, center.y + radius);

		CDround* roundptr = dynamic_cast<CDround*>(draw_way);
		if (roundptr) {
			roundptr->ChangePara(radius, center, 0);
		}
		(nowgraph->mydraw)->DrawLine(&memdc);
		
		//memdc.Ellipse(rect);
		CRound2 tmps(center, radius);
		myround.push_back(tmps);
		mypen1.DeleteObject();
		memdc.SelectObject(pOldBrush);
		nullBrush.DeleteObject();
		myupdate(GetDC());
		//Invalidate();
	}
	else if (choice == 3 && drawcnt == 3)
	{
		CDC* pDC = GetDC();
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		memdc.SelectObject(&mypen1);
		left_botton = false;
		CPoint *tmp = new CPoint[4];
		for (int i = 2; i >= 0; i--) {
			tmp[i].x = mypoint.back().x;
			tmp[i].y = mypoint.back().y;
			mypoint.pop_back();
		}
		//控制点 tmp[2],起点 tmp[0], 终点 tmp[1] 
		
		tmp[3] = tmp[1];
		tmp[1] = tmp[2];
		//起点tmp[0], 控制点 tmp[1、2], 终点 tmp[3];
		memdc.PolyBezier(tmp, 4);
		CBezier my_b_line(tmp[0], tmp[3], tmp[1], tmp[2]);
		CPoint* aa = SaveBezier(xifen, tmp);
		CMulLine tmp_a(xifen, aa);
		tmp_a.leibie = 1;
		mybezier.push_back(my_b_line);
		tmp_a.map_bezier = mybezier.size() - 1;
		mymuline.push_back(tmp_a);
		delete[]tmp;
		drawcnt = 0;
		mypen1.DeleteObject();
		//Invalidate();
		myupdate(GetDC());
	}
	/*
	else if (choice == 4)
	{
		CDC* pDC = GetDC();
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		memdc.SelectObject(&mypen1);
		left_botton = false;
		int sizes = mypoint.size();
		CPoint* tmp_points = new CPoint[sizes];
		if (sizes > 1) {
			memdc.MoveTo(mypoint[sizes - 2]);
			memdc.LineTo(mypoint[sizes - 1]);
			CLine2 tmps(mypoint[sizes - 2], mypoint[sizes - 1]);
			myline.push_back(tmps);
			//ReleaseDC(pDC);
		}
		Invalidate();
	}
	*/
	else if (choice == 5) {
		if(mypoint.size() >= 1)
		{
			CDC* pDC = GetDC();
			CPen mypen1;
			mypen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			memdc.SelectObject(&mypen1);
			CBrush* pOldBrush;
			CBrush nullBrush;
			nullBrush.CreateStockObject(NULL_BRUSH);
			pOldBrush = memdc.SelectObject(&nullBrush);
			left_botton = false;
			mypoint.push_back(point);
			CPoint ed(mypoint.back());
			mypoint.pop_back();
			CPoint st(mypoint.back());
			mypoint.pop_back();

			CRect rect(st.x, st.y, ed.x, ed.y);
			myrect.push_back(rect);
			myrectdots.push_back(-1);
			CRect rect2(ed.x, st.y, st.x, ed.y);
			myrect2.push_back(rect2);
			myrectcolor.push_back(0);

			draw_tangle(&memdc, rect, rect2);
			//memdc.Rectangle(rect);
			memdc.SelectObject(pOldBrush);
			nullBrush.DeleteObject();
			myupdate(GetDC());
		}
		//Invalidate();
		//ReleaseDC(pDC);
	}
	else if (choice == 0 && option == 0) {
		if(!mypoint.empty())
		{
			CPoint tmp_last = mypoint.back();
			CRect A(tmp_last.x, tmp_last.y, point.x, point.y);
			select_tangle = A;
			jietu_tangle = A;
			isin_tangle(A,true);
			show_select_tangle = select_tangle;
			dynamic_change_color(RGB(0, 0, 255));
			while (!mypoint.empty())
				mypoint.pop_back();
			dynamic_draw(GetDC());
			//myupdate(GetDC());
			/*----------*/

			CDC* pDC = GetDC();
			CDC memDC;
			memDC.CreateCompatibleDC(&memdc);
			CRect rect;
			memdc.GetClipBox(&rect); // 或者使用其他方式来确定正确的尺寸
			CBitmap bitmap;
			bitmap.CreateCompatibleBitmap(&memdc, rect.Width(), rect.Height());
			CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
			memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
			
			CPen mypen1;
			CPen *old;
			mypen1.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
			old = memDC.SelectObject(&mypen1);
			CBrush* pOldBrush;
			CBrush brushHollow;
			brushHollow.CreateStockObject(HOLLOW_BRUSH);
			pOldBrush = memDC.SelectObject(&brushHollow);
			if(!is_jian)
				memDC.Rectangle(select_tangle);
			else
				memDC.Rectangle(jietu_tangle);
			memDC.SelectObject(old);
			memDC.SelectObject(pOldBrush);
			mypen1.DeleteObject();
			brushHollow.DeleteObject();

			if(pDC)
			{
				pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
				memDC.SelectObject(pOldBitmap);
				bitmap.DeleteObject();
				memDC.DeleteDC();
			}

			/*----------*/
		}
		if (is_jian) { //裁剪模式

			CRect crect;
			GetClientRect(&crect);
			double tmpc;
			tmpc = min(abs(crect.left - crect.right)*1.0 /abs(jietu_tangle.left - jietu_tangle.right), abs(crect.top - crect.bottom)*1.0 / abs(jietu_tangle.top - jietu_tangle.bottom));
			jian_fang(tmpc, tmpc, crect);
			dynamic_draw(GetDC());

			//退出剪裁模式
			is_jian = false;
		}
		if (is_jian2) { //裁剪模式2
			CRect crect;
			GetClientRect(&crect);
			double tmpc;
			tmpc = min(abs(crect.left - crect.right) * 1.0 / abs(jietu_tangle.left - jietu_tangle.right), abs(crect.top - crect.bottom) * 1.0 / abs(jietu_tangle.top - jietu_tangle.bottom));
			return_all_vector();
			jian_fang(tmpc, tmpc, crect);
			dynamic_draw(GetDC());

			//退出剪裁模式
			is_jian2 = false;
		}
	}

		left_botton = false;
		//Invalidate();
}


void Cex2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnRButtonDown(nFlags, point);
	right_botton = true;
	int sizes = mypoint.size();
	CPoint* tmp_points = new CPoint[sizes];
	for(int i = 0; i < sizes; i++)
	{
		tmp_points[sizes - i - 1] = mypoint.back();
		mypoint.pop_back();
	}

	//将多义线作为一个整体；
	if (choice == 4 && option <= 0) {
		int cnt = 1;
		while (cnt < sizes) {
			myline.pop_back();
			cnt++;
		}
		
		CMulLine tmp_a(sizes-1, tmp_points);
		mymuline.push_back(tmp_a);
		CDC* pDC = GetDC();
		CPen mypen1;
		/*
		mypen1.CreatePen(PS_SOLID, 3, RGB(200, 100, 0));
		memdc.SelectObject(&mypen1);
		//反色画图
		memdc.SetROP2(R2_NOTXORPEN);
		memdc.MoveTo(sb_st);
		memdc.LineTo(sb_ed);
		memdc.SetROP2(R2_COPYPEN);
		mypen1.DeleteObject();
		*/
		//ReleaseDC(pDC);
	}
	else if (choice == 6) {
		CByong tmp_b(sizes, tmp_points);
		mybyong.push_back(tmp_b);
	}
	choice = 0;
	//Invalidate
	myupdate(GetDC());
}


void Cex2View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CView::OnRButtonUp(nFlags, point);
	if (!review.empty()) { // 恢复缩放或者旋转的最后模样。
		select_tangle = show_select_tangle;
		int type = -1, num = -1, nn = opts.size();
		if (option == 3) {
			xuan_niu = review.back();
			review.pop_back();
		}

		for (int i = nn - 1; i >= 0; i--) {
			type = opts[i];
			num = seq[i];
			if (type == 6) { // B样条
				CPoint* Point_xifen = mybyong[num].bpoint;
				int tmpn = mybyong[num].n;
				for (int j = 0; j < tmpn; j++) {
					Point_xifen[j] = review.back();
					review.pop_back();
				}
			}
			else if (type == 5) { // 矩形
				myrect2[num].right = review.back().x;
				myrect2[num].bottom = review.back().y;
				review.pop_back();
				myrect2[num].left = review.back().x;
				myrect2[num].top = review.back().y;
				review.pop_back();

				myrect[num].right = review.back().x;
				myrect[num].bottom = review.back().y;
				review.pop_back();
				myrect[num].left = review.back().x;
				myrect[num].top = review.back().y;
				review.pop_back();
			}
			else if (type == 4) { //bezier
				mybezier[num].ctr2 = review.back();
				review.pop_back();
				mybezier[num].ctr1 = review.back();
				review.pop_back();
				mybezier[num].ed = review.back();
				review.pop_back();
				mybezier[num].st = review.back();
				review.pop_back();
			}
			else if (type == 3) { //多义线
				CPoint* Point_xifen = mymuline[num].muline;
				int tmpn = mymuline[num].num;
				for (int j = tmpn; j >= 0; j--) {
					Point_xifen[j] = review.back();
					review.pop_back();
				}
			}
			else if (type == 2) {
				myround[num].r = review.back().x;
				review.pop_back();
				myround[num].org = review.back();
				review.pop_back();
			}
			else if (type == 1) {
				myline[num].ed = review.back();
				review.pop_back();
				myline[num].st = review.back();
				review.pop_back();
			}
		}
		dynamic_draw(GetDC());
	}
	right_botton = false;
	isSelect = false;
	dynamic_change_color(RGB(0, 0, 0));
	while (!opts.empty())
		opts.pop_back();
	while (!seq.empty())
		seq.pop_back();
	option = 0;
	dynamic_draw(GetDC());
	no_red_select(GetDC());
	is_jian = false;
}
bool Cex2View :: ContainsPoint(CPoint point) {
	//判断直线；
	for (int i = 0; i < myline.size(); i++) {
		CLine2 &tmps = myline[i];
		if(tmps.st.x != tmps.ed.x)
		{
			if (point.x > max(tmps.ed.x, tmps.st.x) || point.x < min(tmps.ed.x, tmps.st.x))
				continue;
		}
		else {
			if (point.y > max(tmps.ed.y, tmps.st.y) || point.y < min(tmps.ed.y, tmps.st.y))
				continue;
		}
		int A = tmps.st.y - tmps.ed.y;
		int B = tmps.ed.x - tmps.st.x;
		int C = tmps.st.x * tmps.ed.y - tmps.ed.x * tmps.st.y;
		int check = abs(point.x * A + point.y * B + C);
		if (check < 10*abs(B)|| check < 10 * abs(A)) {
				tmp_type = 1;
				tmp_figure = i;
				return true;
		}
	}
	//判断矩形； 
	for (int i = 0; i < myrect.size(); i++) {
		CRect& rect1 = myrect[i];
		CRect& rect2 = myrect2[i];
		CPoint a = CPoint(rect1.left, rect1.top);
		CPoint b = CPoint(rect2.left, rect2.top);
		CPoint c = CPoint(rect1.right, rect1.bottom);
		CPoint d = CPoint(rect2.right, rect2.bottom);
		if(is_online(a,b,point,i) || is_online(b, c, point, i) || is_online(c, d, point, i) || is_online(d, a, point, i)){
			return true;
		}
		else
			continue;
	}
	//判断圆形；
	for (int i = 0; i < myround.size(); i++) {
		CRound2 tmps = myround[i];
		int tmp_a = (point.x - tmps.org.x) * (point.x - tmps.org.x) + (point.y - tmps.org.y) * (point.y - tmps.org.y);
		if (tmp_a - (tmps.r-10) * (tmps.r-10) > 0 && tmp_a - (tmps.r + 10) * (tmps.r + 10) < 0)
		{
			tmp_type = 2;
			tmp_figure = i;
			return true;
		}
	}


// 多义线和曲线判断是否在上面  
	for (int i = 0; i < mymuline.size(); i++) {
		int tmpn = mymuline[i].num;
		CPoint* Point_xifen = mymuline[i].muline;
				for (int j = 0; j < tmpn; j++) {
					if(Point_xifen[j].x < Point_xifen[j+1].x)
					{
						if (point.x < Point_xifen[j].x || point.x > Point_xifen[j + 1].x)
							continue;
					}
					else {
						if (point.x > Point_xifen[j].x || point.x < Point_xifen[j + 1].x)
							continue;
					}
					
					int A = Point_xifen[j].y - Point_xifen[j + 1].y;
					int B = Point_xifen[j + 1].x - Point_xifen[j].x;
					int C = Point_xifen[j].x * Point_xifen[j + 1].y - Point_xifen[j + 1].x * Point_xifen[j].y;
					int check = abs(point.x * A + point.y * B + C);
					if (check < 10 * abs(B) || check < 10 * abs(A))
					{
						tmp_type = 3;
						tmp_figure = i;
						return true;
					}
				}
	}
	/*
	const int xifen = 20;
	CPoint Point_xifen[xifen+1];
	CPoint st, ed, ctr1, ctr2;
	for (int i = 0; i < mybezier.size(); i++) {
		st = mybezier[i].st;
		ed = mybezier[i].ed;
		ctr1 = mybezier[i].ctr1;
		ctr2 = mybezier[i].ctr2;

		if (st.x < ed.x) {
			if (point.x < st.x || point.x > ed.x)
				continue;
		}
		else {
			if (point.x < ed.x || point.x > st.x)
				continue;
		}

		for (int j = 0; j <= xifen; j++) {
			float t = (float)j / xifen;
			float u = 1 - t;
			float tt = t * t;
			float uu = u * u;
			float uuu = uu * u;
			float ttt = tt * t;

			float x = uuu * st.x; // (1-t)^3 * P0
			x += 3 * uu * t * ctr1.x; // 3(1-t)^2 * t * P1
			x += 3 * u * tt * ctr2.	x; // 3(1-t) * t^2 * P2
			x += ttt * ed.x; // t^3 * P3

			float y = uuu * st.y; // (1-t)^3 * P0
			y += 3 * uu * t * ctr1.y; // 3(1-t)^2 * t * P1
			y += 3 * u * tt * ctr2.y; // 3(1-t) * t^2 * P2
			y += ttt * ed.y; // t^3 * P3
			
			Point_xifen[j] = CPoint((int)x, (int)y);
		}
		for (int j = 0; j < xifen; j++) {
			if (point.x < Point_xifen[j].x || point.x > Point_xifen[j+1].x)
				continue;
			int A = Point_xifen[j].y - Point_xifen[j+1].y;
			int B = Point_xifen[j+1].x - Point_xifen[j].x;
			int C = Point_xifen[j].x * Point_xifen[j + 1].y - Point_xifen[j + 1].x * Point_xifen[j].y;
			int check = abs(point.x * A + point.y * B + C);
			if (check < 1000)
				return true;
		}
	}
	*/
	//判断B样条
	for (int i = 0; i < mybyong.size(); i++) {
		int tmpn = mybyong[i].n;
		CPoint* Point_xifen = mybyong[i].bpoint;
		int x = 0, y = 0;
		int x_l = 0, y_l = 0;
		int k;
		bool flag = true;
		for (int j = 0; j < tmpn - 3; j++) {
			for (k = 0; k < 2000; k += 80) {
				x_l = x;
				y_l = y;
				x = (x_4[k] * Point_xifen[j + 3].x + x_3[k] * Point_xifen[j + 2].x + x_2[k] * Point_xifen[j + 1].x + x_1[k] * Point_xifen[j].x) / 6;
				y = (x_4[k] * Point_xifen[j + 3].y + x_3[k] * Point_xifen[j + 2].y + x_2[k] * Point_xifen[j + 1].y + x_1[k] * Point_xifen[j].y) / 6;
				if(k)
				{
					bool flag = is_online(CPoint(x_l, y_l), CPoint(x, y), point);
					if (flag) {
						/*
						CPen mypen1, *old;
						mypen1.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
						old = memdc.SelectObject(&mypen1);
						memdc.MoveTo(CPoint(x_l, y_l));
						memdc.LineTo(CPoint(x, y));
						memdc.SelectObject(old);
						mypen1.DeleteObject();
						myupdate(GetDC());
						*/
						tmp_type = 6;
						tmp_figure = i;
						return true;
					}
				}
			}
			k = 1999;
			x_l = x;
			y_l = y;
			x = (x_4[k] * Point_xifen[j + 3].x + x_3[k] * Point_xifen[j + 2].x + x_2[k] * Point_xifen[j + 1].x + x_1[k] * Point_xifen[j].x) / 6;
			y = (x_4[k] * Point_xifen[j + 3].y + x_3[k] * Point_xifen[j + 2].y + x_2[k] * Point_xifen[j + 1].y + x_1[k] * Point_xifen[j].y) / 6;
			if (is_online(CPoint(x_l, y_l), CPoint(x, y), point)) {
				tmp_type = 6;
				tmp_figure = i;
				return true;
			}
		}
	}
	return false;
}

void Cex2View::isin_tangle(CRect optangle, bool kai) {
	//判断直线；
	int l = min(optangle.left, optangle.right);
	int t = min(optangle.top, optangle.bottom);
	int r = max(optangle.left, optangle.right);
	int b = max(optangle.top, optangle.bottom);
	int ls = INT_MAX, ts = INT_MAX, rs = INT_MIN, bs = INT_MIN;
	for (int i = 0; i < myline.size(); i++) {
		int x = (myline[i].st.x + myline[i].ed.x) / 2;
		int y = (myline[i].st.y + myline[i].ed.y) / 2;
		if(!is_jian && !is_jian2)
		{
			if (x <= r && x >= l && y <= b && y >= t) {
				opts.push_back(1);
				seq.push_back(i);
				ls = min(min(myline[i].st.x, myline[i].ed.x), ls);
				ts = min(min(myline[i].st.y, myline[i].ed.y), ts);
				rs = max(max(myline[i].st.x, myline[i].ed.x), rs);
				bs = max(max(myline[i].st.y, myline[i].ed.y), bs);
			}
		}
		else if(is_jian || is_jian2){
			if (Barsky(myline[i])){
				if (is_jian2) {
					opts.push_back(1);
					seq.push_back(tmpline.size());
					tmpline.push_back(myline[i]);
				}
				else
				{
					opts.push_back(1);
					seq.push_back(i);
				}
			}
		}
	}
	//判断矩形；
	for (int i = 0; i < myrect.size(); i++) {
		int x = (myrect[i].right + myrect[i].left) / 2;
		int y = (myrect[i].top + myrect[i].bottom) / 2;
		if(!is_jian && !is_jian2)
		{
			if (x <= r && x >= l && y <= b && y >= t) {
				opts.push_back(5);
				seq.push_back(i);
				ls = min(min(myrect[i].right, myrect[i].left), ls);
				ts = min(min(myrect[i].top, myrect[i].bottom), ts);
				rs = max(max(myrect[i].right, myrect[i].left), rs);
				bs = max(max(myrect[i].top, myrect[i].bottom), bs);

				ls = min(min(myrect2[i].right, myrect2[i].left), ls);
				ts = min(min(myrect2[i].top, myrect2[i].bottom), ts);
				rs = max(max(myrect2[i].right, myrect2[i].left), rs);
				bs = max(max(myrect2[i].top, myrect2[i].bottom), bs);
			}
		}
		else if (is_jian || is_jian2) {
				CRect& rect1 = myrect[i];
				CRect& rect2 = myrect2[i];
				CPoint as = CPoint(rect1.left, rect1.top);
				CPoint bs = CPoint(rect2.left, rect2.top);
				CPoint cs = CPoint(rect1.right, rect1.bottom);
				CPoint ds = CPoint(rect2.right, rect2.bottom);
				if (as.x <= r && as.x >= l && as.y <= b && as.y >= t) {
					if (bs.x <= r && bs.x >= l && bs.y <= b && bs.y >= t) {
						if (cs.x <= r && cs.x >= l && cs.y <= b && cs.y >= t){
							if (ds.x <= r && ds.x >= l && ds.y <= b && ds.y >= t)
							{
								if (is_jian2) {
									opts.push_back(5);
									seq.push_back(tmprect.size());
									tmprect.push_back(myrect[i]);
									tmprect2.push_back(myrect2[i]);
									tmprectcolor.push_back(myrectcolor[i]);
									tmprectdots.push_back(myrectdots[i]);
								}
								else if(is_jian)
								{
									opts.push_back(5);
									seq.push_back(i);
								}
							}
						}
					}
				}
			}
		}
	//判断圆形；
	for (int i = 0; i < myround.size(); i++) {
		int x = myround[i].org.x;
		int y = myround[i].org.y;
		if(!is_jian && !is_jian2)
		{
			if (x <= r && x >= l && y <= b && y >= t) {
				opts.push_back(2);
				seq.push_back(i);
				ls = min(myround[i].org.x - myround[i].r, ls);
				ts = min(myround[i].org.y - myround[i].r, ts);
				rs = max(myround[i].org.x + myround[i].r, rs);
				bs = max(myround[i].org.y + myround[i].r, bs);
			}
		}
		else if (is_jian || is_jian2) {
			if (myround[i].org.x - myround[i].r >= l && myround[i].org.x + myround[i].r <= r && myround[i].org.y - myround[i].r >= t && myround[i].org.y + myround[i].r <= b) {
				if (is_jian2) {
					opts.push_back(2);
					seq.push_back(tmpround.size());
					tmpround.push_back(myround[i]);
				}
				else
				{
					opts.push_back(2);
					seq.push_back(i);
				}
			}
		}
	}


	// 曲线和多义线判断是否在上面
	for (int i = 0; i < mymuline.size(); i++) {
		int tmpn = mymuline[i].num;
		CPoint* Point_xifen = mymuline[i].muline;
		int x = 0, y = 0;
		int ll, rr, tt, bb;
		ll = rr = Point_xifen[0].x;
		tt = bb = Point_xifen[0].y;
		for (int j = 1; j <= tmpn; j++) {
			if (Point_xifen[j].x > rr)
				rr = Point_xifen[j].x;

			if (Point_xifen[j].x < ll)
				ll = Point_xifen[j].x;
			if (Point_xifen[j].y > bb)
				bb = Point_xifen[j].y;
			if (Point_xifen[j].y < tt)
				tt = Point_xifen[j].y;
		}
		x = (rr + ll) / 2;
		y = (tt + bb) / 2;
		if(!is_jian && !is_jian2)
		{
			if (x <= r && x >= l && y <= b && y >= t) {
				opts.push_back(3);
				seq.push_back(i);
				if(mymuline[i].leibie == 1) {
					opts.push_back(4);
					seq.push_back(mymuline[i].map_bezier);
				}
				ls = min(ll, ls);
				ts = min(tt, ts);
				rs = max(rr, rs);
				bs = max(bb, bs);
			}
		}
		else if (is_jian || is_jian2) {
			if (rr <= r && ll >= l && tt >= t && bb <= b) {
				if (is_jian2) {
					opts.push_back(3);
					seq.push_back(tmpmuline.size());
					tmpmuline.push_back(mymuline[i]);
				}
				else if(is_jian)
				{
					opts.push_back(3);
					seq.push_back(i);
				}
				if (mymuline[i].leibie == 1) {
					if (is_jian2) {
						opts.push_back(4);
						seq.push_back(tmpbezier.size());
						tmpbezier.push_back(mybezier[mymuline[i].map_bezier]);
					}
					else if(is_jian)
					{
						opts.push_back(4);
						seq.push_back(mymuline[i].map_bezier);
					}
				}
			}
		}
	}
	// B样条判断
	for (int i = 0; i < mybyong.size(); i++) {
		int tmpn = mybyong[i].n;
		CPoint* Point_xifen = mybyong[i].bpoint;
		int x = 0, y = 0;
		int ll, rr, tt, bb;
		if(!is_jian && !is_jian2)
		{
			ll = rr = Point_xifen[0].x;
			tt = bb = Point_xifen[0].y;
			for (int j = 1; j < tmpn; j++) {
				if (Point_xifen[j].x > rr)
					rr = Point_xifen[j].x;
				if (Point_xifen[j].x < ll)
					ll = Point_xifen[j].x;
				if (Point_xifen[j].y > bb)
					bb = Point_xifen[j].y;
				if (Point_xifen[j].y < tt)
					tt = Point_xifen[j].y;
			}
			x = (rr + ll) / 2;
			y = (tt + bb) / 2;
			if (x <= r && x >= l && y <= b && y >= t) {
				opts.push_back(6);
				seq.push_back(i);
				ls = min(ll, ls);
				ts = min(tt, ts);
				rs = max(rr, rs);
				bs = max(bb, bs);
			}
		}
		else if(is_jian || is_jian2) {
			bool flag = true;
			int ln = INT_MAX, tn = INT_MAX, rn = INT_MIN, bn = INT_MIN;
			int x = 0, y = 0,k = 0;
			for (int j = 0; j < tmpn - 3; j++) {
				for (k = 0; k < 2000; k += 20) {

					x = (x_4[k] * Point_xifen[j + 3].x + x_3[k] * Point_xifen[j + 2].x + x_2[k] * Point_xifen[j + 1].x + x_1[k] * Point_xifen[j].x) / 6;
					y = (x_4[k] * Point_xifen[j + 3].y + x_3[k] * Point_xifen[j + 2].y + x_2[k] * Point_xifen[j + 1].y + x_1[k] * Point_xifen[j].y) / 6;
					if (x > rn)
						rn = x;
					if (x < ln)
						ln = x;
					if (y > bn)
						bn = y;
					if (y < tn)
						tn = y;
				}
				k = 1999;
				x = (x_4[k] * Point_xifen[j + 3].x + x_3[k] * Point_xifen[j + 2].x + x_2[k] * Point_xifen[j + 1].x + x_1[k] * Point_xifen[j].x) / 6;
				y = (x_4[k] * Point_xifen[j + 3].y + x_3[k] * Point_xifen[j + 2].y + x_2[k] * Point_xifen[j + 1].y + x_1[k] * Point_xifen[j].y) / 6;
			}
			if (rn <= r && ln >= l && tn >= t && bn <= b && ln != INT_MAX && tn != INT_MAX && rn != INT_MIN && bn != INT_MIN) {
				if (is_jian2) {
					opts.push_back(6);
					seq.push_back(tmpbyong.size());
					tmpbyong.push_back(mybyong[i]);
				}
				else if(is_jian)
				{
					opts.push_back(6);
					seq.push_back(i);
				}
			}
		}
	}
	if (kai) {
		select_tangle.left = ls;
		select_tangle.right = rs;
		select_tangle.top = ts;
		select_tangle.bottom = bs;
	}
}

void Cex2View::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
	if (isSelect)
	{
		if (Cex2View::ContainsPoint(point))
		{

			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
			isCross = true;
		}
		else
		{
			isCross = false;
			::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
			tmp_figure = -1;
			tmp_type = -1;
		}
	}
	bool isdraw = false;
	CDC* pDC = GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(&memdc);

	// 获取原始DC的区域大小
	CRect rect;
	memdc.GetClipBox(&rect); // 或者使用其他方式来确定正确的尺寸

	// 创建一个兼容的位图
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&memdc, rect.Width(), rect.Height());

	// 选择新的位图到内存DC
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	// 从原始DC复制图形内容到内存DC（位图）
	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);
	/*
	CDC memDC;  // 设备上下文用于绘图
	memDC.SelectObject(&bitmap);
	CRect rect;
	GetClientRect(&rect);
	memDC.CreateCompatibleDC(pDC);
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(&rect, pDC->GetBkColor());
	*/

	//动态绘制： 直线
	if (choice == 1 && left_botton)
	{
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 3, RGB(200, 100, 0));
		memDC.SelectObject(&mypen1);
		CPoint st(mypoint.back());
		CDline* lineptr = dynamic_cast<CDline*>(draw_way);
		if (lineptr) {
			lineptr->ChangePara(st, point, -1);
		}
		(nowgraph->mydraw)->DrawLine(&memDC);
		//memDC.MoveTo(st);
		//memDC.LineTo(point);
		mypen1.DeleteObject();
		isdraw = true;
	}
	//动态绘制圆
	else if (choice == 2 && left_botton) {
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 1, RGB(200, 100, 0));
		memDC.SelectObject(&mypen1);
		CBrush* pOldBrush;
		CBrush brushHollow;
		brushHollow.CreateStockObject(HOLLOW_BRUSH);
		pOldBrush = memDC.SelectObject(&brushHollow);
		CPoint st(mypoint.back());
		int radius = (int)sqrt(pow(st.x - point.x, 2) + pow(st.y - point.y, 2)) / 2;
		CPoint center1((st.x + point.x) / 2, (st.y + point.y) / 2);
		//	CRect rect1(center1.x - radius, center1.y - radius, center1.x + radius, center1.y + radius);

		CDround* roundptr = dynamic_cast<CDround*>(draw_way);
		if (roundptr) {
			roundptr->ChangePara(radius, center1, -1);
		}
		//memDC.Ellipse(rect1);
		(nowgraph->mydraw)->DrawLine(&memDC);
		memDC.SelectObject(pOldBrush);
		brushHollow.DeleteObject();
		mypen1.DeleteObject();
		isdraw = true;
	}
	//动态绘制曲线
	else if (choice == 3 && drawcnt == 2)
	{
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 3, RGB(200, 100, 0));
		memDC.SelectObject(&mypen1);
		CPoint* tmp = new CPoint[4];
		tmp[0].x = mypoint[1].x;
		tmp[0].y = mypoint[1].y;
		tmp[3].x = mypoint[0].x;
		tmp[3].y = mypoint[0].y;
		tmp[1].x = tmp[2].x = point.x;
		tmp[1].y = tmp[2].y = point.y;
		memDC.PolyBezier(tmp, 4);
		is_first = false;
		delete[]tmp;
		mypen1.DeleteObject();
		isdraw = true;
	}
	else if (choice == 4)
	{
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 1, RGB(200, 100, 0));
		memDC.SelectObject(&mypen1);
		int sizes = mypoint.size();
		if (sizes > 0) {
			//memDC.MoveTo(mypoint[sizes - 1]);
			//memDC.LineTo(point);
			if ((point.x - mypoint[0].x) * (point.x - mypoint[0].x) + (point.y - mypoint[0].y) * (point.y - mypoint[0].y) <= 2500)
				point = mypoint[0];
			CDline* lineptr = dynamic_cast<CDline*>(draw_way);
			if (lineptr) {
				lineptr->ChangePara(mypoint[sizes - 1], point, -1);
			}
			(nowgraph->mydraw)->DrawLine(&memDC);
			sb_st = mypoint[sizes - 1];
			sb_ed = point;
		}
		isdraw = true;
	}
	else if (choice == 5 && left_botton) {
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 3, RGB(200, 100, 0));
		memDC.SelectObject(&mypen1);
		CBrush* pOldBrush;
		CBrush brushHollow;
		brushHollow.CreateStockObject(HOLLOW_BRUSH);
		pOldBrush = memDC.SelectObject(&brushHollow);
		CPoint st(mypoint.back());
		CRect rect1(st.x, st.y, point.x, point.y);
		memDC.Rectangle(rect1);
		memdc.SelectObject(pOldBrush);
		brushHollow.DeleteObject();
		isdraw = true;
	}
	else if (choice == 6) {
		left_botton = false;
		int sizes = mypoint.size();
		if (sizes > 2) {
			for (int i = 0; i <= 2000; i++) {
				int x = 0, y = 0;
				int tmpn = sizes - 1;
				x = (x_4[i] * point.x + x_3[i] * mypoint[tmpn].x + x_2[i] * mypoint[tmpn - 1].x + x_1[i] * mypoint[tmpn - 2].x) / 6;
				y = (x_4[i] * point.y + x_3[i] * mypoint[tmpn].y + x_2[i] * mypoint[tmpn - 1].y + x_1[i] * mypoint[tmpn - 2].y) / 6;
				//DrawPoints(pDC, CPoint(x, y),10);
				//myupdate(GetDC());
				memDC.SetPixel(x, y, RGB(0, 0, 255));
			}
			CPen mypen2;
			mypen2.CreatePen(PS_DASH, 1, RGB(255, 0, 0));
			memDC.SelectObject(&mypen2);
			DrawPoints(&memDC, point, 10);
			DrawPoints(&memDC, mypoint[sizes - 1], 10);
			DrawPoints(&memDC, mypoint[sizes - 2], 10);
			memDC.MoveTo(mypoint[sizes - 1]);
			memDC.LineTo(mypoint[sizes - 2]);
			memDC.MoveTo(mypoint[sizes - 2]);
			memDC.LineTo(point);
			memDC.LineTo(mypoint[sizes - 1]);
			CPoint tmpmid = point + mypoint[sizes - 2];
			memDC.LineTo(tmpmid.x / 2, tmpmid.y / 2);
			DrawPoints(&memDC, CPoint(tmpmid.x / 6 + mypoint[sizes - 1].x * 2 / 3, tmpmid.y / 6 + mypoint[sizes - 1].y * 2 / 3), 10);
			mypen2.DeleteObject();
			isdraw = true;
		}
		//Invalidate();
	}
	//选择矩形

	else if (!choice && left_botton && option == 0) {
		CPen mypen1;
		mypen1.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		memDC.SelectObject(&mypen1);
		CBrush* pOldBrush;
		CBrush brushHollow;
		brushHollow.CreateStockObject(HOLLOW_BRUSH);
		pOldBrush = memDC.SelectObject(&brushHollow);
		CPoint st(mypoint.back());
		CRect rect1(st.x, st.y, point.x, point.y);
		memDC.Rectangle(rect1);
		memdc.SelectObject(pOldBrush);
		brushHollow.DeleteObject();
		isdraw = true;
	}

	if (!choice && option == 1)// 平移
	{
		
		if (is_tuo)
		{
			CPoint dd = point - pre_point;
			pre_point = point;
			int nn = opts.size();
			int type = -1;
			int num = -1;
			show_select_tangle.bottom += dd.y;
			show_select_tangle.top += dd.y;
			show_select_tangle.left += dd.x;
			show_select_tangle.right += dd.x;
			for (int i = 0; i < nn; i++) {
				type = opts[i];
				num = seq[i];
				if (type == 1) {
					myline[num].st += dd;
					myline[num].ed += dd;
					myline[num].color = RGB(0, 0, 255);
				}
				else if (type == 2) {
					myround[num].org += dd;
					myround[num].color = RGB(0, 0, 255);
				}
				else if (type == 3) { //多义线
					CPoint* Point_xifen = mymuline[num].muline;
					int tmpn = mymuline[num].num;
					int x = 0, y = 0;
					mymuline[num].color = RGB(0,0,255);
					for (int j = 0; j <= tmpn; j++) {
						Point_xifen[j] += dd;
					}
				}
				else if (type == 4) { // Bezier
					mybezier[num].ctr1 += dd;
					mybezier[num].ctr2 += dd;
					mybezier[num].st += dd;
					mybezier[num].ed += dd;

					mybezier[num].color = RGB(0, 0, 255);

				}
				else if (type == 5) { // 矩形
					myrect[num].bottom += dd.y;
					myrect[num].top += dd.y;
					myrect[num].left += dd.x;
					myrect[num].right += dd.x;

					myrect2[num].bottom += dd.y;
					myrect2[num].top += dd.y;
					myrect2[num].left += dd.x;
					myrect2[num].right += dd.x;

					myrectcolor[num] = RGB(0, 0, 255);
				}
				else if (type == 6) { // B样条
					CPoint* Point_xifen = mybyong[num].bpoint;
					int tmpn = mybyong[num].n;
					mybyong[num].color = RGB(0, 0, 255);
					int x = 0, y = 0;
					for (int j = 0; j < tmpn; j++) {
						Point_xifen[j] += dd;
					}
				}
			}
			
		}
		dynamic_draw(GetDC());
		//记录上一次移动到的点；
	}
	else if (!choice && option == 2)// 缩放
	{
		int nn = opts.size();
		int type = -1;
		int num = -1;

		if (is_tuo)
		{
			while (!review.empty())
				review.pop_back();
			std::vector<CPoint> tmp_p;
			orgp = CPoint((select_tangle.left + select_tangle.right) / 2 , (select_tangle.top + select_tangle.bottom) / 2);
			//CPoint orgp(0, 0);
			double xm = (select_tangle.left + select_tangle.right) / 2.0;
			double ym = (select_tangle.top + select_tangle.bottom) / 2.0;
			double x1 = point.x;
			double x2 = pre_point.x;
			tmp_c = x1/x2;

			/*选择矩阵的缩放*/
			CPoint aa = CPoint(select_tangle.left, select_tangle.top);
			CPoint bb = CPoint(select_tangle.right, select_tangle.bottom);
			cal_suo(aa, xm, ym, tmp_c);
			cal_suo(bb, xm, ym, tmp_c);
			show_select_tangle.left = aa.x;
			show_select_tangle.right = bb.x;
			show_select_tangle.top = aa.y;
			show_select_tangle.bottom = bb.y;
			/*结束*/

			for (int i = 0; i < nn; i++) {
				type = opts[i];
				num = seq[i];
				if (type == 1) {
					tmp_p.push_back(myline[num].st);
					tmp_p.push_back(myline[num].ed);
					cal_suo(myline[num].st, xm, ym, tmp_c);
					cal_suo(myline[num].ed, xm, ym, tmp_c);
					review.push_back(myline[num].st);
					review.push_back(myline[num].ed);
					myline[num].color = RGB(0, 0, 255);
				}
				else if (type == 2) {
					CPoint a = myround[num].org;
					CPoint b = CPoint(myround[num].r, myround[num].r);
					tmp_p.push_back(a);
					tmp_p.push_back(b);

					cal_suo(a, xm, ym, tmp_c);
					cal_suo(b, 0, 0, tmp_c);
					
					review.push_back(a);
					review.push_back(b);
					
					myround[num].org = a;
					myround[num].r = b.x;
					myround[num].color = RGB(0, 0, 255);
				}
				else if (type == 3) { //多义线
					CPoint* Point_xifen = mymuline[num].muline;
					int tmpn = mymuline[num].num;
					mymuline[num].color = RGB(0, 0, 255);
					for (int j = 0; j <= tmpn; j++) {
						tmp_p.push_back(Point_xifen[j]);
						cal_suo(Point_xifen[j], xm, ym, tmp_c);
						review.push_back(Point_xifen[j]);
					}
				}
				else if (type == 4) { // Bezier
					tmp_p.push_back(mybezier[num].st);
					tmp_p.push_back(mybezier[num].ed);
					tmp_p.push_back(mybezier[num].ctr1);
					tmp_p.push_back(mybezier[num].ctr2);
					
					cal_suo(mybezier[num].st, xm, ym, tmp_c);
					cal_suo(mybezier[num].ed, xm, ym, tmp_c);
					cal_suo(mybezier[num].ctr1, xm, ym, tmp_c);
					cal_suo(mybezier[num].ctr2, xm, ym, tmp_c);

					review.push_back(mybezier[num].st);
					review.push_back(mybezier[num].ed);
					review.push_back(mybezier[num].ctr1);
					review.push_back(mybezier[num].ctr2);

					mybezier[num].color = RGB(0, 0, 255);
				}
				else if (type == 5) { // 矩形
					CPoint a = CPoint(myrect[num].left, myrect[num].top);
					CPoint b = CPoint(myrect[num].right, myrect[num].bottom);
					CPoint a2 = CPoint(myrect2[num].left, myrect2[num].top);
					CPoint b2 = CPoint(myrect2[num].right, myrect2[num].bottom);
					tmp_p.push_back(a);
					tmp_p.push_back(b);
					tmp_p.push_back(a2);
					tmp_p.push_back(b2);

					cal_suo(a, xm, ym, tmp_c);
					cal_suo(b, xm, ym, tmp_c);
					cal_suo(a2, xm, ym, tmp_c);
					cal_suo(b2, xm, ym, tmp_c);

					review.push_back(a);
					review.push_back(b);
					review.push_back(a2);
					review.push_back(b2);

					myrect[num].left = a.x;
					myrect[num].right = b.x;
					myrect[num].top = a.y;
					myrect[num].bottom = b.y;

					myrect2[num].left = a2.x;
					myrect2[num].right = b2.x;
					myrect2[num].top = a2.y;
					myrect2[num].bottom = b2.y;

					myrectcolor[num] = RGB(0, 0, 255);
				}
				else if (type == 6) { // B样条
					CPoint* Point_xifen = mybyong[num].bpoint;
					int tmpn = mybyong[num].n;
					mybyong[num].color = RGB(0, 0, 255);
					for (int j = 0; j < tmpn; j++) {
						tmp_p.push_back(Point_xifen[j]);
						cal_suo(Point_xifen[j], xm, ym, tmp_c);
						review.push_back(Point_xifen[j]);
					}
				}
			}
			dynamic_draw(GetDC());

			for (int i = nn - 1; i >= 0; i--) {
				type = opts[i];
				num = seq[i];
			    if (type == 6) { // B样条
					CPoint* Point_xifen = mybyong[num].bpoint;
					int tmpn = mybyong[num].n;
					for (int j = 0; j < tmpn; j++) {
						Point_xifen[j] = tmp_p.back();
						tmp_p.pop_back();
					}
				}
				else if (type == 5) { // 矩形
					myrect2[num].right = tmp_p.back().x;
					myrect2[num].bottom = tmp_p.back().y;
					tmp_p.pop_back();
					myrect2[num].left = tmp_p.back().x;
					myrect2[num].top = tmp_p.back().y;
					tmp_p.pop_back();

					myrect[num].right = tmp_p.back().x;
					myrect[num].bottom = tmp_p.back().y;
					tmp_p.pop_back();
					myrect[num].left = tmp_p.back().x;
					myrect[num].top = tmp_p.back().y;
					tmp_p.pop_back();
				}
				else if (type == 4) { //bezier
					mybezier[num].ctr2 = tmp_p.back();
					tmp_p.pop_back();
					mybezier[num].ctr1 = tmp_p.back();
					tmp_p.pop_back();
					mybezier[num].ed = tmp_p.back();
					tmp_p.pop_back();
					mybezier[num].st = tmp_p.back();
					tmp_p.pop_back();
				}
				else if (type == 3) { //多义线
					CPoint* Point_xifen = mymuline[num].muline;
					int tmpn = mymuline[num].num;
					for (int j = tmpn; j >= 0; j--) {
						Point_xifen[j]= tmp_p.back();
						tmp_p.pop_back();
					}
				}
				else if (type == 2) {
					myround[num].r = tmp_p.back().x;
					tmp_p.pop_back();
					myround[num].org = tmp_p.back();
					tmp_p.pop_back();
				}
				else if (type == 1) {
					myline[num].ed = tmp_p.back();
					tmp_p.pop_back();
					myline[num].st = tmp_p.back();
					tmp_p.pop_back();
				}
			}
		}

	}
		else if (!choice && option == 3)// 旋转
		{
			if(left_botton && !is_tuo)
			{
				int dx = point.x - xuan_center.x;
				int dy = point.y - xuan_center.y;
				if (dx * dx + dy * dy <= 900) {
					xuan_center = point;
					dynamic_draw(GetDC());
				}
			}

			int nn = opts.size();
			int type = -1;
			int num = -1;
			if (is_tuo)
			{
				while (!review.empty())
					review.pop_back();
				std::vector<CPoint> tmp_p;
				double ss, cc, ssc, ccc, sst,cct;
				int dx = point.x - xuan_center.x , dy = - point.y + xuan_center.y , dl ;
				int dcx = xuan_niu.x - xuan_center.x, dcy = -xuan_niu.y + xuan_center.y, dcl;

				dl = sqrt(dx * dx + dy * dy);
				dcl = sqrt(dcx * dcx + dcy * dcy);
				sst = (double)dx / dl;
				cct = (double)dy / dl;

				ssc = (double)dcx / dcl;
				ccc = (double)dcy / dcl;

				ss = sst * ccc - cct * ssc;
				cc = cct * ccc + sst * ssc;

				for (int i = 0; i < nn; i++) {
					type = opts[i];
					num = seq[i];
					if (type == 1) {
						tmp_p.push_back(myline[num].st);
						tmp_p.push_back(myline[num].ed);

						cal_xuan(myline[num].st,cc,ss);
						cal_xuan(myline[num].ed,cc,ss);
						
						review.push_back(myline[num].st);
						review.push_back(myline[num].ed);
						myline[num].color = RGB(0, 0, 255);
					}
					else if (type == 2) {
						CPoint a = myround[num].org;
						CPoint b = CPoint(myround[num].r, myround[num].r);
						tmp_p.push_back(a);
						tmp_p.push_back(b);
						
						cal_xuan(a, cc, ss);
						
						review.push_back(a);
						review.push_back(b);

						myround[num].org = a;
						myround[num].r = b.x;
						myround[num].color = RGB(0, 0, 255);
					}
					else if (type == 3) { //多义线
						CPoint* Point_xifen = mymuline[num].muline;
						int tmpn = mymuline[num].num;
						mymuline[num].color = RGB(0, 0, 255);
						for (int j = 0; j <= tmpn; j++) {
							tmp_p.push_back(Point_xifen[j]);
							
							cal_xuan(Point_xifen[j], cc, ss);
							
							review.push_back(Point_xifen[j]);
						}
					}
					else if (type == 4) { // Bezier
						tmp_p.push_back(mybezier[num].st);
						tmp_p.push_back(mybezier[num].ed);
						tmp_p.push_back(mybezier[num].ctr1);
						tmp_p.push_back(mybezier[num].ctr2);

						cal_xuan(mybezier[num].st, cc, ss);
						cal_xuan(mybezier[num].ed, cc, ss);
						cal_xuan(mybezier[num].ctr1, cc, ss);
						cal_xuan(mybezier[num].ctr2, cc, ss);

						review.push_back(mybezier[num].st);
						review.push_back(mybezier[num].ed);
						review.push_back(mybezier[num].ctr1);
						review.push_back(mybezier[num].ctr2);

						mybezier[num].color = RGB(0, 0, 255);
					}
					else if (type == 5) { // 矩形
						/*
						int ls, ts, rs, bs;
						if (myrect[num].left < myrect[num].right) {
							ls = myrect[num].left;
							rs = myrect[num].right;
						}
						else {
							ls = myrect[num].right;
							rs = myrect[num].left;
						}
						if (myrect[num].top < myrect[num].bottom) {
							ts = myrect[num].top;
							bs = myrect[num].bottom;
						}
						else {
							ts = myrect[num].bottom;
							bs = myrect[num].top;
						}
						*/

						CPoint a = CPoint(myrect[num].left, myrect[num].top);
						CPoint b = CPoint(myrect[num].right, myrect[num].bottom);
						CPoint a2 = CPoint(myrect2[num].left, myrect2[num].top);
						CPoint b2 = CPoint(myrect2[num].right, myrect2[num].bottom);
						tmp_p.push_back(a);
						tmp_p.push_back(b);
						tmp_p.push_back(a2);
						tmp_p.push_back(b2);
						
						cal_xuan(a, cc, ss);
						cal_xuan(b, cc, ss);
						cal_xuan(a2, cc, ss);
						cal_xuan(b2, cc, ss);
						
						review.push_back(a);
						review.push_back(b);
						review.push_back(a2);
						review.push_back(b2);

						myrect[num].left = a.x;
						myrect[num].right = b.x;
						myrect[num].top = a.y;
						myrect[num].bottom = b.y;

						myrect2[num].left = a2.x;
						myrect2[num].right = b2.x;
						myrect2[num].top = a2.y;
						myrect2[num].bottom = b2.y;
						myrectcolor[num] = RGB(0, 0, 255);
					}
					else if (type == 6) { // B样条
						CPoint* Point_xifen = mybyong[num].bpoint;
						int tmpn = mybyong[num].n;
						mybyong[num].color = RGB(0, 0, 255);
						for (int j = 0; j < tmpn; j++) {
							tmp_p.push_back(Point_xifen[j]);
							
							cal_xuan(Point_xifen[j], cc, ss);
							
							review.push_back(Point_xifen[j]);
						}
					}
				}
				// 旋转按钮
				tmp_p.push_back(xuan_niu);
				cal_xuan(xuan_niu, cc, ss);
				review.push_back(xuan_niu);
				dynamic_draw(GetDC());
				xuan_niu = tmp_p.back();
				tmp_p.pop_back();
				for (int i = nn - 1; i >= 0; i--) {
					type = opts[i];
					num = seq[i];
					if (type == 6) { // B样条
						CPoint* Point_xifen = mybyong[num].bpoint;
						int tmpn = mybyong[num].n;
						for (int j = 0; j < tmpn; j++) {
							Point_xifen[j] = tmp_p.back();
							tmp_p.pop_back();
						}
					}
					else if (type == 5) { // 矩形
						myrect2[num].right = tmp_p.back().x;
						myrect2[num].bottom = tmp_p.back().y;
						tmp_p.pop_back();
						myrect2[num].left = tmp_p.back().x;
						myrect2[num].top = tmp_p.back().y;
						tmp_p.pop_back();

						myrect[num].right = tmp_p.back().x;
						myrect[num].bottom = tmp_p.back().y;
						tmp_p.pop_back();
						myrect[num].left = tmp_p.back().x;
						myrect[num].top = tmp_p.back().y;
						tmp_p.pop_back();
					}
					else if (type == 4) { //bezier
						mybezier[num].ctr2 = tmp_p.back();
						tmp_p.pop_back();
						mybezier[num].ctr1 = tmp_p.back();
						tmp_p.pop_back();
						mybezier[num].ed = tmp_p.back();
						tmp_p.pop_back();
						mybezier[num].st = tmp_p.back();
						tmp_p.pop_back();
					}
					else if (type == 3) { //多义线
						CPoint* Point_xifen = mymuline[num].muline;
						int tmpn = mymuline[num].num;
						for (int j = tmpn; j >= 0; j--) {
							Point_xifen[j] = tmp_p.back();
							tmp_p.pop_back();
						}
					}
					else if (type == 2) {
						myround[num].r = tmp_p.back().x;
						tmp_p.pop_back();
						myround[num].org = tmp_p.back();
						tmp_p.pop_back();
					}
					else if (type == 1) {
						myline[num].ed = tmp_p.back();
						tmp_p.pop_back();
						myline[num].st = tmp_p.back();
						tmp_p.pop_back();
					}
				}
			}

	}
		/*----------------*/

		lastpoint = point;
		if (isdraw && pDC)
		{

			pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
			memDC.SelectObject(pOldBitmap);
			bitmap.DeleteObject();
			memDC.DeleteDC();
		}
}



void Cex2View::OnIdrRect()
{
	// TODO: 在此添加命令处理程序代码
	choice = 5;
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}

CPoint* Cex2View::SaveBezier(int xifen, CPoint tmps[]) {

	CPoint *Point_xifen = new CPoint[xifen + 1];
	CPoint st, ed, ctr1, ctr2;
		st = tmps[0];
		ed = tmps[3];
		ctr1 = tmps[1];
		ctr2 = tmps[2];
		for (int j = 0; j <= xifen; j++) {
			float t = (float)j / xifen;
			float u = 1 - t;
			float tt = t * t;
			float uu = u * u;
			float uuu = uu * u;
			float ttt = tt * t;

			float x = uuu * st.x; // (1-t)^3 * P0
			x += 3 * uu * t * ctr1.x; // 3(1-t)^2 * t * P1
			x += 3 * u * tt * ctr2.x; // 3(1-t) * t^2 * P2
			x += ttt * ed.x; // t^3 * P3

			float y = uuu * st.y; // (1-t)^3 * P0
			y += 3 * uu * t * ctr1.y; // 3(1-t)^2 * t * P1
			y += 3 * u * tt * ctr2.y; // 3(1-t) * t^2 * P2
			y += ttt * ed.y; // t^3 * P3
			Point_xifen[j] = CPoint((int)x, (int)y);
			/*
			CDC *pDC = GetDC();
			CPen mypen;
			mypen.CreatePen(PS_SOLID, 3, RGB(255, 0 ,0));
			memdc.SelectObject(&mypen);
			if (j > 0) {
				memdc.MoveTo(Point_xifen[j - 1]);
				memdc.LineTo(Point_xifen[j]);
			}
			*/
		}
		return Point_xifen;
}

void Cex2View::OnSelecton()
{
	// TODO: 在此添加命令处理程序代码
	if(choice == 0)
	{
		isSelect = !isSelect;
	}
	if (!isSelect)
	{
		no_red_select(GetDC());
		select_num = 0;
		is_over_select = false;
		last_figure = -1;
		last_type = -1;

	}
	else {
		right_botton = false;
		dynamic_change_color(RGB(0, 0, 0));
		while (!opts.empty())
			opts.pop_back();
		while (!seq.empty())
			seq.pop_back();
		dynamic_draw(GetDC());
		myupdate(GetDC());
		option = -1;
	}
	//Invalidate();
}


void Cex2View::OnSave()
{
	// TODO: 在此添加命令处理程序代码
	CString folderPath;
	CFolderPickerDialog folderPickerDialog(NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT, this);
	if (folderPickerDialog.DoModal() == IDOK)
	{
		// 用户选择了一个文件夹并按下了“确定”
		folderPath = folderPickerDialog.GetPathName();  // 获取选择的文件夹路径
	}
	else {
		Invalidate();
		return;
	}
	CImage image;
	CRect rect;
	GetClientRect(&rect); // 获取客户区尺寸
	image.Create(rect.Width(), rect.Height(), 24); // 创建24位图像

	CDC* pDC = GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(CBitmap::FromHandle(image));
	memDC.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY); // 将图像内容从窗口DC复制到内存DC
	memDC.SelectObject(pOldBitmap);
	image.Save(folderPath + _T("\\实验2上次保存的图像.png"), Gdiplus::ImageFormatPNG); // 保存为PNG格式
	//ReleaseDC(pDC);
	
	std::fstream myfile1;
	std::fstream myfile2;
	std::fstream myfile3;
	std::fstream myfile4;
	std::fstream myfile5;
	std::fstream myfile6;
	std::fstream myfile7;

	myfile1.open(folderPath + _T("\\我的直线.txt"), std::ios::out);
	myfile2.open(folderPath + _T("\\我的圆形.txt"), std::ios::out);
	myfile3.open(folderPath + _T("\\我的矩形.txt"), std::ios::out);
	myfile4.open(folderPath + _T("\\我的多义线.txt"), std::ios::out);
	myfile5.open(folderPath + _T("\\我的曲线.txt"), std::ios::out);
	myfile6.open(folderPath + _T("\\我的B样条曲线.txt"), std::ios::out);
	myfile7.open(folderPath + _T("\\我的颜色.txt"), std::ios::out);

	for (int i = 0; i < myline.size(); i++) {
		myfile1 << myline[i].st.x << " " << myline[i].st.y << " ";
		myfile1 << myline[i].ed.x <<" " << myline[i].ed.y << " ";
		myfile1 << std::endl;
	}
	for (int i = 0; i < myround.size(); i++) {
		myfile2 << myround[i].r << " ";
		myfile2 << myround[i].org.x << " " << myround[i].org.y << " ";
		myfile2 << std::endl;
	}
	for (int i = 0; i < myrect.size(); i++) {
		myfile3 << myrect[i].left << " " << myrect[i].top << " " << myrect[i].right << " " << myrect[i].bottom << " ";
		myfile3 << myrect2[i].left << " " << myrect2[i].top << " " << myrect2[i].right << " " << myrect2[i].bottom << " ";
		myfile3 << myrectdots[i] << " ";
		myfile3 << std::endl;
	}
	for (int i = 0; i < mymuline.size(); i++) {
		CPoint* tmp = mymuline[i].muline;
		myfile4 << mymuline[i].num << " ";
		for (int j = 0; j <= mymuline[i].num; j++) {
			myfile4 << tmp[j].x << " " << tmp[j].y << " ";
		}
		myfile4 << mymuline[i].dots << " ";
		myfile4 << mymuline[i].leibie << " ";
		myfile4 << mymuline[i].map_bezier << " ";
		myfile4 << std::endl;
	}
	for (int i = 0; i < mybezier.size(); i++) {
		CBezier &tmpb = mybezier[i];
		myfile5 << tmpb.st.x << " " << tmpb.st.y << " ";
		myfile5 << tmpb.ctr1.x << " " << tmpb.ctr1.y << " ";
		myfile5 << tmpb.ctr2.x << " " << tmpb.ctr2.y << " ";
		myfile5 << tmpb.ed.x << " " << tmpb.ed.y << " ";
		myfile5 << std::endl;
	}
	if(myfile6.good())
	for (int i = 0; i < mybyong.size(); i++) {
		int n = mybyong[i].n;
		CPoint* tmpb = mybyong[i].bpoint;
		myfile6 << n << " ";
		for (int j = 0; j < n; j++) {
			myfile6 << tmpb[j].x << " " << tmpb[j].y << " ";
		}
		myfile6 << std::endl;
	}
	if (myfile7.good()) {
		for (int i = 0; i < mycolordots.size(); i++) {
			long long nn = mycolordots[i].colordots.size();
			auto &ptmps1 = mycolordots[i];
			myfile7 << nn << " ";
			for (long long j = 0; j < nn; j++) {
				auto &ptmps2 = ptmps1.colordots[j];
				myfile7 << ptmps2.x << " " << ptmps2.y << " ";
			}
			myfile7 << std::endl;
		}
	}

	myfile1.close();
	myfile2.close();
	myfile3.close();
	myfile4.close();
	myfile5.close();
	myfile6.close();
	myfile7.close();
}



void Cex2View::OnCenter()
{
	// TODO: 在此添加命令处理程序代码
	is_have_circle = false;
	for (int i = 0; i < (is_over_select ? 2 : select_num); i++) {
		if (type[i] == 2) {
			if(!is_have_circle)
				is_have_circle = true;
			CShowCenter tmp(myround[figure1[i]].org.x, myround[figure1[i]].org.y);
			if (IDOK == tmp.DoModal()) {
				
				DrawPoints(GetDC(), myround[figure1[i]].org, 10);
			}
		}
	}
	if (!is_have_circle) {
		CNonCenter p;
		p.DoModal();
	}
}


void Cex2View::OnInter()
{
	// TODO: 在此添加命令处理程序代码
	if (!is_over_select && !select_num) {
		CNonInter noninter;
		noninter.DoModal();
	}
	else {
		if (type[0] == 2 && type[1] == 2) { // 两个圆形;
			if (!is_over_select) {
				CNonInter noninter;
				noninter.DoModal();
				return;
			}
			CPoint org1 = myround[figure1[0]].org;
			double r1 = myround[figure1[0]].r;
			CPoint org2 = myround[figure1[1]].org;
			double r2 = myround[figure1[1]].r;


			double d = sqrt((org1.x - org2.x) * (org1.x - org2.x) + (org1.y - org2.y) * (org1.y - org2.y));
			if (d > r1 + r2 || d < fabs(r1 - r2)) {
				CNonInter noninter;
				noninter.DoModal();
			}
			else {
				double cc = r1 + r2 + d;
				double ss = sqrt((cc / 2) * ((cc / 2) - r1) * ((cc / 2) - r2) * ((cc / 2) - d));
				double h = ss * 2 / d;
			    double m1 = r1 * r1 - h * h;
				double m2 = r2 * r2 - h * h;
				double ratio = 1 / (1 + sqrt(m1 / m2));
				double x0 = org1.x * ratio + org2.x * (1 - ratio);
				double y0 = org1.y * ratio + org2.y * (1 - ratio);
				if (h <= 5) {
					COneInter oneinter(x0, y0);
					if (oneinter.DoModal() == IDOK) {
						DrawPoints(GetDC(), CPoint(x0,y0), 10);
					}
				}
				else
				{
					double xc, yc, xd, yd;
					xc = x0 - h / d * (org2.y - org1.y);
					yc = y0 + h / d * (org2.x - org1.x);
					xd = x0 + h / d * (org2.y - org1.y);
					yd = y0 - h / d * (org2.x - org1.x);
					CPen mypen, * old;
					CDC* pDC = GetDC();
					CTwoInter twointer(xc, yc, xd, yd);
					if (twointer.DoModal() == IDOK) {
						DrawPoints(GetDC(), CPoint(xc, yc), 10);
						DrawPoints(GetDC(), CPoint(xd, yd), 10);
					}
				}
			}
		}
		else if (type[0] + type[1] == 3) // 线段和圆;
		{
			if (!is_over_select) {
				CNonInter noninter;
				noninter.DoModal();
				return;
			}
			CPoint st, ed, org;
			double r;
			if (type[0] == 1) {
				st = myline[figure1[0]].st;
				ed = myline[figure1[0]].ed;
				org = myround[figure1[1]].org;
				r = myround[figure1[1]].r;
			}
			else {
				st = myline[figure1[1]].st;
				ed = myline[figure1[1]].ed;
				org = myround[figure1[0]].org;
				r = myround[figure1[0]].r;
			}

			int check = 0;
			double x1, y1, x2, y2;
			GetPoint(org, r, st, ed, x1, y1, x2, y2, check);
			if (check == 0) {
				CNonInter noninter;
				noninter.DoModal();
			}
			else if (check == 1) {
				COneInter oneinter(x1, y1);
				if (IDOK == oneinter.DoModal()) {
					DrawPoints(GetDC(), CPoint(x1, y1), 10);
				}
			}
			else {
				CTwoInter twointer(x1, y1, x2, y2);
				if (twointer.DoModal() == IDOK) {
					DrawPoints(GetDC(), CPoint(x1, y1), 10);
					DrawPoints(GetDC(), CPoint(x2, y2), 10);
				}
			}
		}
		else if (type[0] + type[1] == 2) // 两条线段；
		{
			if (!is_over_select) {
				CNonInter noninter;
				noninter.DoModal();
				return;
			}
			CPoint st1, st2, ed1, ed2;
			st1 = myline[figure1[0]].st;
			st2 = myline[figure1[1]].st;
			ed1 = myline[figure1[0]].ed;
			ed2 = myline[figure1[1]].ed;
			int A1, A2, B1, B2, C1, C2;
			A1 = st1.y - ed1.y;
			B1 = ed1.x - st1.x;
			C1 = st1.x * ed1.y - ed1.x * st1.y;
			A2 = st2.y - ed2.y;
			B2 = ed2.x - st2.x;
			C2 = st2.x * ed2.y - ed2.x * st2.y;

	
			//判断是否平行
			if (A1 * B2 == A2 * B1 ) {
				CNonInter noninter;
				noninter.DoModal();
				return;
			}
			
			double x0 = (double)(C2 * B1 - C1 * B2) / (B2 * A1 - B1 * A2);
			double y0 = (double)(A2 * C1 - A1 * C2) / -(A2 * B1 - A1 * B2);
			
			if ((x0 - st1.x) * (x0 - ed1.x) + (y0 - st1.y) * (y0 - ed1.y) > 0) {
				CNonInter noninter;
				noninter.DoModal();
				return;
			}

			if ((x0 - st2.x) * (x0 - ed2.x) + (y0 - st2.y) * (y0 - ed2.y) > 0) {
				CNonInter noninter;
				noninter.DoModal();
				return;
			}
			COneInter oneinter(x0, y0);
			if (IDOK == oneinter.DoModal()) {
				DrawPoints(GetDC(), CPoint(x0, y0), 10);
			}
		}
		else {
			CNonInter noninter;
			noninter.DoModal();
		}
	}
}


void Cex2View::OnVertical()
{
	quest_vert = true;
	// TODO: 在此添加命令处理程序代码
}


void Cex2View::OnRead()
{
	std::fstream myfile1;
	std::fstream myfile2;
	std::fstream myfile3;
	std::fstream myfile4;
	std::fstream myfile5;
	std::fstream myfile6;
	std::fstream myfile7;
	CString folderPath;
	CFolderPickerDialog folderPickerDialog(NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT, this);
	if (folderPickerDialog.DoModal() == IDOK)
	{
		// 用户选择了一个文件夹并按下了“确定”
		folderPath = folderPickerDialog.GetPathName();  // 获取选择的文件夹路径
	}
	else {
		return;
	}
	//清屏
	if (gai) {
		while (!myline.empty()) {
			myline.pop_back();
		}
		while (!myrect.empty()) {
			myrect.pop_back();
			myrect2.pop_back();
			myrectdots.pop_back();
			myrectcolor.pop_back();
		}
		while (!myround.empty()) {
			myround.pop_back();
		}
		while (!mybezier.empty()) {
			mybezier.pop_back();
		}
		while (!mymuline.empty()) {
			CPoint* tmpm = mymuline.back().muline;
			delete[]tmpm;
			mymuline.pop_back();
		}
		while (!mypoint.empty()) {
			mypoint.pop_back();
		}
		while (!mybyong.empty()) {
			CPoint* tmpm = mybyong.back().bpoint;
			delete[]tmpm;
			mybyong.pop_back();
		}
		while (!mycolordots.empty()) {
			mycolordots.pop_back();
		}
		gai = false;
		CRect rect;             //创建一个矩形
		GetClientRect(rect);    //使矩形与客户窗口大小一致
		CBrush BkBrush;         //新建画刷
		BkBrush.CreateSolidBrush(RGB(255, 255, 255));  //设置画刷颜色
		memdc.FillRect(rect, &BkBrush);   //填充矩形
	}
	myfile1.open(folderPath + _T("\\我的直线.txt"), std::ios::in);
	myfile2.open(folderPath + _T("\\我的圆形.txt"), std::ios::in);
	myfile3.open(folderPath + _T("\\我的矩形.txt"), std::ios::in);
	myfile4.open(folderPath + _T("\\我的多义线.txt"), std::ios::in);
	myfile5.open(folderPath + _T("\\我的曲线.txt"), std::ios::in);
	myfile6.open(folderPath + _T("\\我的B样条曲线.txt"), std::ios::in);
	myfile7.open(folderPath + _T("\\我的颜色.txt"), std::ios::in);
	while (!myfile1.eof()) {
		CPoint st, ed;
		if (!(myfile1 >> st.x)) {
			break;
		}
		myfile1 >> st.y;
		myfile1 >> ed.x >> ed.y;
		CLine2 ee(st, ed);
		myline.push_back(ee);
	}
	while (!myfile2.eof()) {
		CPoint org;
		int r;
		if (!(myfile2 >> r))
			break;
		myfile2 >> org.x >> org.y;
		CRound2 tmp(org, r);
		myround.push_back(tmp);
	}
	while (!myfile3.eof()) {
		int l;
		int t;
		int r;
		int b;
		if (!(myfile3 >> l)) {
			break;
		}
		myfile3 >> t >> r >> b;
		CRect tmpr(l, t, r, b);

		myfile3 >> l >> t >> r >> b;

		CRect tmpr2(l, t, r, b);
		
		int dots;
		myfile3 >> dots;
		myrect.push_back(tmpr);
		myrect2.push_back(tmpr2);
		myrectdots.push_back(dots);
		myrectcolor.push_back(0);
		//myrect.push_back(0);
	}
	while (!myfile4.eof()) {
		int nn;
		myfile4 >> nn;
		if (myfile4.eof())
			break;
		CPoint* tmp = new CPoint[nn + 1];
		for (int j = 0; j <= nn; j++) {
			myfile4 >> tmp[j].x >> tmp[j].y;
		}
		int dots;
		myfile4 >> dots;
		int leibie;
		myfile4 >> leibie;
		int map;
		myfile4 >> map;
		CMulLine tmpm(nn, tmp);
		tmpm.dots = dots;
		tmpm.leibie = leibie;
		tmpm.map_bezier = map;
		mymuline.push_back(tmpm);
	}
	while(!myfile5.eof()) {
		CPoint st, ctr1, ctr2, ed;
		myfile5 >> st.x;
		if (myfile5.eof())
			break;
		myfile5 >> st.y;
		myfile5 >> ctr1.x >> ctr1.y >> ctr2.x >> ctr2.y >> ed.x >> ed.y;
		CBezier tmpb(st, ed, ctr1, ctr2);
		mybezier.push_back(tmpb);
	}
	if(myfile6.good())
	while (!myfile6.eof()) {
		int nn;
		myfile6 >> nn;
		if (myfile6.eof())
			break;
		CPoint* tmp = new CPoint[nn + 1];
		for (int j = 0; j < nn; j++) {
			myfile6 >> tmp[j].x >> tmp[j].y;
		}
		CByong tmpm(nn, tmp);
		mybyong.push_back(tmpm);
	}
	if (myfile7.good())
		while (!myfile7.eof()) {
		long long nn;
			myfile7 >> nn;
			if (myfile7.eof())
				break;
			CColorPut tmpas;
			int x, y;
			for (long long j = 0; j < nn; j++) {
				myfile7 >> x >> y;
				tmpas.colordots.push_back(CPoint(x,y));
			}
			mycolordots.push_back(tmpas);
		}
	myfile1.close();
	myfile2.close();
	myfile3.close();
	myfile4.close();
	myfile5.close();
	myfile6.close();
	myfile7.close();
	Invalidate();
	read = true;
	CDC* pDC = GetDC();
	CPen mypen1;
	mypen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	memdc.SelectObject(&mypen1);
	for (int i = 0; i < myline.size(); i++) {
		CLine2 tmps(myline[i]);
		memdc.MoveTo(tmps.st);
		memdc.LineTo(tmps.ed);
	}
	CBrush* pOldBrush;
	CBrush nullBrush;
	nullBrush.CreateStockObject(NULL_BRUSH);
	pOldBrush = memdc.SelectObject(&nullBrush);
	for (int i = 0; i < myround.size(); i++)
	{
		int r = myround[i].r;
		CPoint org = myround[i].org;
		CRect rect(org.x - r, org.y - r, org.x + r, org.y + r);
		memdc.Ellipse(rect);
	}

	for (int i = 0; i < mymuline.size(); i++)
	{
		if(mymuline[i].leibie == 0)
		{
			CPoint* nowl = mymuline[i].muline;
			int sizes = mymuline[i].num;
			for (int j = 0; j < sizes; j++)
			{
				memdc.MoveTo(nowl[j]);
				memdc.LineTo(nowl[j + 1]);
			}
		}
	}

	for (int i = 0; i < mybezier.size(); i++)
	{
		CPen mypen2;
		CPen* old;
		mypen2.CreatePen(PS_SOLID, 1, mybezier[i].color);
		old = memdc.SelectObject(&mypen2);
		CPoint tmp[4];
		tmp[0] = mybezier[i].st;
		tmp[1] = mybezier[i].ctr1;
		tmp[2] = mybezier[i].ctr2;
		tmp[3] = mybezier[i].ed;
		memdc.PolyBezier(tmp, 4);
		memdc.SelectObject(old);
		mypen2.DeleteObject();
	}

	for (int k = 0; k < mybyong.size(); k++)
	{
		CPoint* nowl = mybyong[k].bpoint;
		int sizes = mybyong[k].n;
		OnIdrBeyond();
		for (int tmpn = 3; tmpn < sizes; tmpn++)
		{
			int x = 0, y = 0;
			for(int i = 0; i <= 2000; i++)
			{
				x = (x_4[i] * nowl[tmpn].x + x_3[i] * nowl[tmpn - 1].x + x_2[i] * nowl[tmpn - 2].x + x_1[i] * nowl[tmpn - 3].x) / 6;
				y = (x_4[i] * nowl[tmpn].y + x_3[i] * nowl[tmpn - 1].y + x_2[i] * nowl[tmpn - 2].y + x_1[i] * nowl[tmpn - 3].y) / 6;
				memdc.SetPixel(x, y, RGB(0, 0, 0));
			}
		}
		choice = 0;
	}
		pOldBrush = memdc.SelectObject(&nullBrush);
		for (int i = 0; i < myrect.size(); i++)
		{
			CRect rect(myrect[i]);
			CRect rect2(myrect2[i]);
			draw_tangle(&memdc, rect, rect2);
			//memdc.Rectangle(rect);
		}
		memdc.SelectObject(pOldBrush);
		nullBrush.DeleteObject();
		//ReleaseDC(pDC);

		/*
		*这是不用**画，太慢了
		for (int i = 0; i < mycolordots.size(); i++)
		{
			auto& nowl = mycolordots[i].colordots;
			long long sizes = nowl.size();
			for (long long j = 0; j < sizes; j++)
			{
				memdc.SetPixel(nowl[j], RGB(0, 255, 0));
			}
		}
		*/
		Invalidate();
		dynamic_draw(GetDC()); //点睛之笔；
}


void Cex2View::OnGai()
{
	//Invalidate(TRUE);
	//UpdateWindow();
	gai = true;
	OnRead();
	// TODO: 在此添加命令处理程序代码
}
void Cex2View::GetPoint(CPoint org, double r, CPoint st, CPoint ed, double& x1, double& y1, double& x2, double& y2, int& check) {
	//(x - cx )^2 + (y - cy)^2 = r^2
	//y = kx +b
	int cx = org.x;
	int cy = org.y;
	int stx = st.x;
	int sty = st.y;
	int edx = ed.x;
	int edy = ed.y;

	// 求得直线方程
	if (stx == edx) {
		if (cx + r < stx || cx - r > stx)
		{
			check = 0;
		}
		else if (stx == cx + r || stx == cx - r) {
			check = 1;
			x1 = stx;
			y1 = cy;
		}
		else {
			check = 2;
			x1 = stx;
			x2 = stx;
			y1 = cy + sqrt(r * r - (cx - stx) * (cx - stx));
			y2 = cy - sqrt(r * r - (cx - stx) * (cx - stx));
		}
	}
	else
	{
		double k = ((double)(edy - sty)) / (edx - stx);
		double b = edy - k * edx;

		// 列方程
		/*
		  (1 + k^2)*x^2 - x*(2*cx -2*k*(b -cy) ) + cx*cx + ( b - cy)*(b - cy) - r*r = 0
		*/
		double c = cx * cx + (b - cy) * (b - cy) - r * r;
		double a = (1 + k * k);
		double b1 = (2 * cx - 2 * k * (b - cy));
		// 得到下面的简化方程
		// a*x^2 - b1*x + c = 0;

		double tmp = b1 * b1 - 4 * a * c;
		if (tmp < 0) {
			check = 0;
		}
		else if (tmp < -1e6 && tmp > 0) {
			check = 1;
			x1 = b1 / (2 * a);
		}
		else
		{
			tmp = sqrt(tmp);
			check = 2;
			x1 = (b1 + tmp) / (2 * a);
			y1 = k * x1 + b;
			x2 = (b1 - tmp) / (2 * a);
			y2 = k * x2 + b;
		}
	}

	if (check == 1) {
		double p1 = (x1 - stx) * (x1 - edx) + (y1 - sty) * (y1 - edy);
		if (p1 > 0)
			check = 0;
	}
	else if (check == 2) {
		double p1 = (x2 - stx) * (x2 - edx) + (y2 - sty) * (y2 - edy);
		if (p1 > 0)
			check--;
		p1 = (x1 - stx) * (x1 - edx) + (y1 - sty) * (y1 - edy);
		if (p1 > 0)
		{
			check--;
			if (check == 1) {
				x1 = x2;
				y1 = y2;
			}
		}
	}
}
void Cex2View::DrawPoints(CDC* pDC, CPoint& a, int sizes, int color) {
	CBrush* pOldBrush;
	CBrush mybrush;
	mybrush.CreateSolidBrush(color);
	pOldBrush = pDC->SelectObject(&mybrush);
	int thickness = sizes; // 点的粗细
	CRect rect(a.x - thickness / 2, a.y - thickness / 2, a.x + thickness / 2, a.y + thickness / 2);
	pDC->Ellipse(rect);
	pDC->SelectObject(pOldBrush);
	mybrush.DeleteObject();
}


void Cex2View::OnIdrMidd()
{
	choice = 1;
	nowgraph = &choose_line;
	draw_way = &cline;
	nowgraph->draw_way(draw_way);
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}


void Cex2View::OnIdrBre()
{
	// TODO: 在此添加命令处理程序代码
	choice = 1;
	nowgraph = &choose_line;
	draw_way = &aline;
	nowgraph->draw_way(draw_way);
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}


void Cex2View::OnPutcolor()
{
	isput_color = 1;
	// TODO: 在此添加命令处理程序代码
	for (int i = 0; i < (is_over_select ? 2 : select_num); i++) {
		if (type[i] == 5) {
			CRect tmpr(myrect[figure1[i]]);
			CRect tmpr2(myrect2[figure1[i]]);
			CPoint* a = new CPoint [4];
			a[0] = CPoint(tmpr.left,tmpr.top);
			a[1] = CPoint(tmpr2.left, tmpr2.top);
			a[2] = CPoint(tmpr.right, tmpr.bottom);
			a[3] = CPoint(tmpr2.right, tmpr2.bottom);
			Fence_Full(&memdc, a, a[0].x, RGB(255, 100, 0), 4);
			if (figure1[i] >=0 )
				myrectdots[figure1[i]] = mycolordots.size() - 1;
			delete[]a;
		}
		else if (type[i] == 3) { 
			int nn = mymuline[figure1[i]].num;
			CPoint* aa = mymuline[figure1[i]].muline;
			if (aa[0] == aa[nn]) {
				Fence_Full(&memdc, aa, aa[0].x, RGB(255, 100, 0), nn);
				if (figure1[i] >= 0)
					mymuline[figure1[i]].dots = mycolordots.size() - 1;
			}
		}
	}
	myupdate(GetDC());
}


void Cex2View::OnPutcolor2()
{
	isput_color = 2;
	// TODO: 在此添加命令处理程序代码
	for (int i = 0; i < (is_over_select ? 2 : select_num); i++) {
		if (type[i] == 5) {
			CRect tmpr(myrect[figure1[i]]);
			CRect tmpr2(myrect2[figure1[i]]);
			CPoint* a = new CPoint[4];
			a[0] = CPoint(tmpr.left, tmpr.top);
			a[1] = CPoint(tmpr2.left, tmpr2.top);
			a[2] = CPoint(tmpr.right, tmpr.bottom);
			a[3] = CPoint(tmpr2.right, tmpr2.bottom);
			LineSeed_begin(&memdc, a, 4, RGB(255, 100, 0));
			if(figure1[i] >= 0)
				myrectdots[figure1[i]] = mycolordots.size() - 1;
			delete[]a;
		}
		else if (type[i] == 3) {
			int nn = mymuline[figure1[i]].num;
			CPoint* aa = mymuline[figure1[i]].muline;
			if (aa[0] == aa[nn]) {
			LineSeed_begin(&memdc, aa, nn, RGB(255, 100, 0));
			if (figure1[i] >= 0)
				mymuline[figure1[i]].dots = mycolordots.size() - 1;
			}
		}
	}
	myupdate(GetDC());
}

void  Cex2View::Fence_Full(CDC* pDC, CPoint a[], int x, int mycolor, int n) { //默认为三角形；
	//a[]为多边形顶点坐标, x为栅栏的横坐标, n为多边形的边数，默认为3，即三角形
	int max_x, min_x, max_y, min_y, xi;
	std::set<CPoint, CMP> tmp_set;
	for (int i = 0; i < n; i++) {
		max_y = (a[i].y > a[(i + 1) % n].y) ? a[i].y : a[(i + 1) % n].y;
		min_y = (a[i].y < a[(i + 1) % n].y) ? a[i].y : a[(i + 1) % n].y;
		for (int y = min_y; y < max_y; y++) {
			//该直线为纵坐标为y的时候，横坐标为x；
			int A = a[i].y - a[(i + 1) % n].y;
			int B = a[(i + 1) % n].x - a[i].x;
			int C = a[i].x * a[(i + 1) % n].y - a[i].y * a[(i + 1) % n].x;
			xi = -(B * y + C) / (float)A;
			max_x = (x > xi) ? x : xi;
			min_x = (x < xi) ? x : xi;
			for (int j = min_x; j < max_x; j++) {
				std::set<CPoint, CMP>::iterator check = tmp_set.find(CPoint(j, y));
				if (check != tmp_set.end()) {//如果该点还没有染色
					tmp_set.erase(check);
				}
				else {
					tmp_set.insert(CPoint(j, y));
				}
			}
		}
	}
	CColorPut tmpas;
		for (auto iter = tmp_set.rbegin(); iter != tmp_set.rend(); iter++) {
			memdc.SetPixel((*iter), mycolor);
			tmpas.colordots.push_back((*iter));
		}
		mycolordots.push_back(tmpas);
}

bool Cex2View::is_in_graph(CPoint a[], int n, int xc, int yc) {
	CPoint P(xc, yc);
	int wn = 0;
	for (int i = 0, j = n-1; i < n; i++) {
		CPoint P1 = a[j];  //顺时针中前一点
		CPoint P2 = a[i];  //顺时针中后一点
		CPoint V1 = P2 - P1;
		CPoint V2 = P - P1;
		int k = V1.x * V2.y - V1.y * V2.x; //用于判断被测点在有向边的左右
		int d1 = P1.y - P.y; //用于判断向上还是向下穿过
		int d2 = P2.y - P.y;
		//V1在V2的顺时针方向即测试点在有向边左边 并且有向边向上穿过
		if (k > 0 && d1 <= 0 && d2 > 0) wn--;
		//V1在V2的逆时针方向即测试点在有向边右边 并且有向边向下穿过
		if (k < 0 && d1>0 && d2 <= 0) wn++;
		j = i;
	}
	return (wn != 0);
}

void Cex2View::LineSeed_begin(CDC* pDC, CPoint a[],int n, int mycolor) {
	std::vector<CPoint> stack;//实现扫描线种子填充法的必要栈；
	//
	/*
	float xc, yc;
	int x1 = a[1].x;
	int y1 = a[1].y;
	int x2 = (int)(a[0].x + a[2].x) / 2;
	int y2 = (int)(a[0].y + a[2].y) / 2;
	int x3 = a[0].x;
	int y3 = a[0].y;
	int x4 = (int)(a[1].x + a[2].x) / 2;
	int y4 = (int)(a[1].y + a[2].y) / 2;
	int A1 = y1 - y2;
	int B1 = x2 - x1;
	int C1 = x1 * y2 - x2 * y1;
	int A2 = y3 - y4;
	int B2 = x4 - x3;
	int C2 = x3 * y4 - x4 * y3;
	xc = (float)(B1 * C2 - B2 * C1) / (B2 * A1 - B1 * A2);
	yc = (float)(C1 + A1 * xc) / (-B1);
	LineSeed_FUll(pDC, a, xc, yc, n ,mycolor,stack);
	*/
	//int add_x[8] = { 0,1,1,1,0,-1,-1,-1 };
	//int add_y[8] = { -1,-1,0,1,1,1,0,-1 };
	int xc, yc;
	for (int i = 0, j = n - 1, k = n-2 ; i < n; i++) {
		xc = (a[i].x + a[k].x) / 4 + a[j].x / 2;
		yc = (a[i].y + a[k].y) / 4 + a[j].y / 2;
		if (is_in_graph(a, n, xc, yc)) {
			LineSeed_FUll(pDC, a, xc, yc, n, mycolor, stack);
			//DrawPoints(&memdc, CPoint(xc, yc), 10);
			myupdate(GetDC());
			return;
		}
		k = j;
		j = i;
	}
	return;
}
void Cex2View::Bresenham_Line(class CPoint& st, class CPoint& ed, std::set<CPoint, CMP>& save) {
	int x;
	int y;
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
			save.insert(CPoint(x, y));
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
				//pDC->SetPixel(x, y, RGB(255, 0, 0));
				save.insert(CPoint(x, y));
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
				//pDC->SetPixel(x, y, RGB(255, 0, 0));
				save.insert(CPoint(x, y));
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
void Cex2View::LineSeed_FUll(CDC* pDC, CPoint a[], int x, int y, int n,int mycolor, std::vector<CPoint>& stack) {
	stack.push_back(CPoint(x, y));
	std::vector<CPoint> save;
	//使用bresenham画线法将边界点存入tmps_edge中
	std::set<CPoint, CMP> tmps_edge;
	for (int i = 0; i < n; i++) {
		Bresenham_Line(a[i], a[(i + 1) % n], tmps_edge);
	}
	while (!stack.empty()) {
		x = stack.back().x;
		y = stack.back().y;
		//pDC->SetPixel(x, y, mycolor);
		save.push_back(CPoint(x, y));
		tmps_edge.insert(stack.back());
		int x_l = x, x_r = x;
		stack.pop_back();
		//向左探索
		while (/*!isnotedge(pDC, a, 3, x_l - 1, y)*/tmps_edge.find(CPoint(x_l - 1, y)) == tmps_edge.end()) {
			x_l--;
			//pDC->SetPixel(x_l, y, mycolor);
			save.push_back(CPoint(x_l, y));
			tmps_edge.insert(CPoint(x_l, y));
		}; // 如果不使用画布上的像素点判断边界，则使用模拟的方式将边界存储在容器中然后判断当前点是否在容器中。
		while (/*!isnotedge(pDC, a, 3, x_r + 1, y) */tmps_edge.find(CPoint(x_r + 1, y)) == tmps_edge.end()) {
			x_r++;
			//pDC->SetPixel(x_r, y, mycolor);
			save.push_back(CPoint(x_r, y));
			tmps_edge.insert(CPoint(x_r, y));
		}
		int i = x_r;
		int flag = true;
		while (i >= x_l) {
			//int color1 = pDC->GetPixel(i, y + 1);
			if (/*(color1 == RGB(255, 255, 255)) */tmps_edge.find(CPoint(i, y + 1)) == tmps_edge.end()) {
				if (!flag) {
					i--;
					continue;
				}
				flag = false;
				//LineSeed_FUll(pDC, a, i, y + 1, save, stack);
				stack.push_back(CPoint(i, y + 1));
			}
			else {
				flag = true;
			}
			i--;
		}



		i = x_r;
		flag = true;
		while (i >= x_l) {
			//int color1 = pDC->GetPixel(i, y - 1);
			if (/*(color1 == RGB(255, 255, 255))*/tmps_edge.find(CPoint(i, y - 1)) == tmps_edge.end()) {
				if (!flag) {
					i--;
					continue;
				}
				flag = false;
				stack.push_back(CPoint(i, y - 1));
				//LineSeed_FUll(pDC, a, i, y - 1, save, stack);
			}
			else {
				flag = true;
			}
			i--;
		}
	}
	CColorPut tmpas;
	for (long long i = 0; i < save.size(); i++) {
		pDC->SetPixel(save[i], mycolor);
		tmpas.colordots.push_back(save[i]);
	}
	mycolordots.push_back(tmpas);
}

void Cex2View::OnIdrBrecir()
{

	// TODO: 在此添加命令处理程序代码
	choice = 2;
	nowgraph = &choose_round;
	draw_way = &bround;
	nowgraph->draw_way(draw_way);
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}


void Cex2View::OnIdrBeyond()
{
	choice = 6;
	int cnt = 0;
	if(!byong_cal)
		for (float t = 0; t <= 1; t += 0.0005) {
			float t2 = t * t;
			float t3 = t2 * t;
			x_1[cnt] = (-t3 + 3 * t2 - 3*t + 1);
			x_2[cnt] = (3 * t3 - 6 * t2 + 4);
			x_3[cnt] = -3 * t3 + 3 * t2 + 3 * t + 1;
			x_4[cnt] = t3;
			cnt++;
		}
	byong_cal = true;
	no_select_tangle();
	while (!mypoint.empty())
		mypoint.pop_back();
}


void Cex2View::dynamic_change_color(int color) {
	int type = 1;
	int num = -1;
	int nn = opts.size();
	for (int i = 0; i < nn; i++) {
		type = opts[i];
		num = seq[i];
		if (type == 1) {
			myline[num].color = color;
		}
		else if (type == 2) {
			myround[num].color = color;
		}
		else if (type == 3) { //多义线
			mymuline[num].color = color;
		}
		else if (type == 4) { // Bezier
			mybezier[num].color = color;
		}
		else if (type == 5) { // 矩形
			myrectcolor[num] = color;
		}
		else if (type == 6) { // B样条
			mybyong[num].color = color;
			}
	}
}
void Cex2View::dynamic_change_all_color(int color) {
	;
}
void Cex2View::dynamic_draw(CDC* pDC) {
	//清屏
	CRect rect;             //创建一个矩形
	GetClientRect(rect);    //使矩形与客户窗口大小一致
	CBrush BkBrush;         //新建画刷
	BkBrush.CreateSolidBrush(RGB(255, 255, 255));  //设置画刷颜色
	memdc.FillRect(rect, &BkBrush);   //填充矩形

	CPen mypen1;
	mypen1.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	memdc.SelectObject(&mypen1);
	for (int i = 0; i < myline.size(); i++) {
		CPen mypen2;
		CPen *old;
		mypen2.CreatePen(PS_SOLID, 1,myline[i].color);
		old = memdc.SelectObject(&mypen2);
		CLine2 tmps(myline[i]);
		memdc.MoveTo(tmps.st);
		memdc.LineTo(tmps.ed);
		memdc.SelectObject(old);
	}
	CBrush* pOldBrush;
	CBrush nullBrush;
	nullBrush.CreateStockObject(NULL_BRUSH);
	pOldBrush = memdc.SelectObject(&nullBrush);
	for (int i = 0; i < myround.size(); i++)
	{
		CPen mypen2;
		CPen* old;
		mypen2.CreatePen(PS_SOLID, 1, myround[i].color);
		old = memdc.SelectObject(&mypen2);
		int r = myround[i].r;
		CPoint org = myround[i].org;
		CRect rect(org.x - r, org.y - r, org.x + r, org.y + r);
		memdc.Ellipse(rect);
		memdc.SelectObject(old);
	}

	for (int i = 0; i < mymuline.size(); i++)
	{
		if(mymuline[i].leibie == 0)
		{
			CPoint* nowl = mymuline[i].muline;
			int sizes = mymuline[i].num;
			CPen mypen2;
			CPen* old;
			mypen2.CreatePen(PS_SOLID, 1, mymuline[i].color);
			old = memdc.SelectObject(&mypen2);
			if (mymuline[i].dots != -1)
			{
				CBrush MyBrush, * OldBrush;//定义填充画刷
				MyBrush.CreateSolidBrush(RGB(255, 100, 0));//创建绿色画刷
				OldBrush = memdc.SelectObject(&MyBrush);//选中画刷到设备山下文
				memdc.Polygon(nowl, sizes);//p为点集，4表示有4个点
				memdc.SelectObject(OldBrush); // 填充为红色
				MyBrush.DeleteObject();//删除画刷
			}
			for (int j = 0; j < sizes; j++)
			{
				memdc.MoveTo(nowl[j]);
				memdc.LineTo(nowl[j + 1]);
			}
			memdc.SelectObject(old);
		}
	}
	//画Bezier
	for (int i = 0; i < mybezier.size(); i++)
	{
		CPen mypen2;
		CPen* old;
		mypen2.CreatePen(PS_SOLID, 1, mybezier[i].color);
		old = memdc.SelectObject(&mypen2);
		CPoint tmp[4];
		tmp[0] = mybezier[i].st;
		tmp[1] = mybezier[i].ctr1;
		tmp[2] = mybezier[i].ctr2;
		tmp[3] = mybezier[i].ed;
		memdc.PolyBezier(tmp, 4);
		memdc.SelectObject(old);
		mypen2.DeleteObject();
	}

	for (int k = 0; k < mybyong.size(); k++)
	{
		CPoint* nowl = mybyong[k].bpoint;
		int tmp_color = mybyong[k].color;
		int sizes = mybyong[k].n;
		/*--------*/
		//防止循环调用
		int cnt = 0;
		if (!byong_cal)
			for (float t = 0; t <= 1; t += 0.0005) {
				float t2 = t * t;
				float t3 = t2 * t;
				x_1[cnt] = (-t3 + 3 * t2 - 3 * t + 1);
				x_2[cnt] = (3 * t3 - 6 * t2 + 4);
				x_3[cnt] = -3 * t3 + 3 * t2 + 3 * t + 1;
				x_4[cnt] = t3;
				cnt++;
			}
		byong_cal = true;

		/*--------*/
		for (int tmpn = 3; tmpn < sizes; tmpn++)
		{
			int x = 0, y = 0;
			for (int i = 0; i <= 2000; i++)
			{
				x = (x_4[i] * nowl[tmpn].x + x_3[i] * nowl[tmpn - 1].x + x_2[i] * nowl[tmpn - 2].x + x_1[i] * nowl[tmpn - 3].x) / 6;
				y = (x_4[i] * nowl[tmpn].y + x_3[i] * nowl[tmpn - 1].y + x_2[i] * nowl[tmpn - 2].y + x_1[i] * nowl[tmpn - 3].y) / 6;
				memdc.SetPixel(x, y, tmp_color);
			}
		}
	}
	pOldBrush = memdc.SelectObject(&nullBrush);
	for (int i = 0; i < myrect.size(); i++)
	{
		CPen mypen2;
		CPen* old;
		mypen2.CreatePen(PS_SOLID, 1, myrectcolor[i]);
		old = memdc.SelectObject(&mypen2);
		CRect rect(myrect[i]);
		CRect rect2(myrect2[i]);

		CPoint a[4];
		a[0] = CPoint(rect.left, rect.top);
		a[1] = CPoint(rect2.left, rect2.top);
		a[2] = CPoint(rect.right, rect.bottom);
		a[3] = CPoint(rect2.right, rect2.bottom);
		if (myrectdots[i] != -1)
		{
			CBrush MyBrush, * OldBrush;//定义填充画刷
			MyBrush.CreateSolidBrush(RGB(255, 100, 0));//创建绿色画刷
			OldBrush = memdc.SelectObject(&MyBrush);//选中画刷到设备山下文
			memdc.Polygon(a, 4);//p为点集，4表示有4个点
			memdc.SelectObject(OldBrush); // 填充为红色
			MyBrush.DeleteObject();//删除画刷
		}

		draw_tangle(&memdc, rect, rect2);
		//memdc.Rectangle(rect);

		memdc.SelectObject(old);
	}
	//确定中心点
	//DrawPoints(&memdc, orgp, 10);

	//如果是旋转，则画出中心点和旋转按钮
	if(option == 3)
	{
		DrawPoints(&memdc, xuan_center, 10);
		DrawPoints(&memdc, xuan_niu, 30, RGB(100,255,255));
	}
	if (is_jian || is_jian2) {
		CPen mypen1, * old;
		mypen1.CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
		old = memdc.SelectObject(&mypen1);
		memdc.Rectangle(jietu_tangle);
		memdc.SelectObject(old);
		mypen1.DeleteObject();
	}

	if (option == 1 || option == 2) {
		CPen mypen1, * old;
		mypen1.CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
		old = memdc.SelectObject(&mypen1);
		memdc.Rectangle(show_select_tangle);
		memdc.SelectObject(old);
		mypen1.DeleteObject();
	}
	memdc.SelectObject(pOldBrush);
	nullBrush.DeleteObject();
	myupdate(pDC);
}


void Cex2View::OnPing() //平移
{
	option = 1;
	isSelect = false;
	xiugai_tangle();
	dynamic_draw(GetDC());
	// TODO: 在此添加命令处理程序代码
}

void Cex2View::OnXuan()
{
	option = 3;
	isSelect = false;
	// 更新 Center
	xuan_center = CPoint((select_tangle.left + select_tangle.right) / 2, (select_tangle.top + select_tangle.bottom) / 2);
	xuan_niu = CPoint(xuan_center.x, min(select_tangle.top,select_tangle.bottom)) + CPoint(0, -30);
	CRect rectss;
	GetClientRect(&rectss);
	xuan_niu.x = max(rectss.left, xuan_niu.x);
	xuan_niu.x = min(xuan_niu.x, rectss.right);
	xuan_niu.y = max(rectss.top, xuan_niu.y);
	xuan_niu.y = min(xuan_niu.y, rectss.bottom);
	
	//只需要加两个点即可，所以直接覆盖颜色好了。
	dynamic_draw(GetDC());
	// TODO: 在此添加命令处理程序代码
}


void Cex2View::OnSuo()
{
	option = 2;
	isSelect = false;
	xiugai_tangle();
	dynamic_draw(GetDC());
	// TODO: 在此添加命令处理程序代码
}

void Cex2View::cal_suo(CPoint &a, double xm, double ym, double tmp_x, double tmp_y, bool singleway) {
	if(singleway)
	{
		a.x = a.x * tmp_x + xm * (1 - tmp_x) + 0.5;
		a.y = a.y * tmp_x + ym * (1 - tmp_x) + 0.5;
	}
	else {
		a.x = a.x * tmp_x + xm * (1 - tmp_x) + 0.5;
		a.y = a.y * tmp_y + ym * (1 - tmp_y) + 0.5;
	}
}

void Cex2View::no_select_tangle() {
	dynamic_change_color(RGB(0, 0, 0));
	while (!opts.empty())
		opts.pop_back();
	while (!seq.empty())
		seq.pop_back();
	dynamic_draw(GetDC());
	myupdate(GetDC());
	option = -1;
}
void Cex2View :: cal_xuan(CPoint& a, double cc, double ss) {
	a -= xuan_center;
	int x = a.x, y = a.y;
	a.x = x * cc - y * ss + 0.5;
	a.y = x * ss + y * cc + 0.5;
	a += xuan_center;
}
void Cex2View :: draw_tangle(CDC* pDC, CRect& rect1, CRect& rect2) {
	CPoint a[4];
	a[0] = CPoint(rect1.left, rect1.top);
	a[1] = CPoint(rect2.left, rect2.top);
	a[2] = CPoint(rect1.right, rect1.bottom);
	a[3] = CPoint(rect2.right, rect2.bottom);
	for (int j = 3, i = 0; i <= 3; i++) {
		pDC->MoveTo(a[j]);
		pDC->LineTo(a[i]);
		j = i;
	}
}

bool Cex2View::is_online(CPoint&st, CPoint&ed, CPoint& np, int i) {
	CPoint a, b;
	if (st.x < ed.x)
		a = st, b = ed;
	else
		a = ed, b = st;
	CLine2 tmps(a,b);
	CPoint point = np;
	if (point.x > tmps.ed.x || point.x < tmps.st.x) {
		return false;
	}
	else
	{
		int A = tmps.st.y - tmps.ed.y;
		int B = tmps.ed.x - tmps.st.x;
		int C = tmps.st.x * tmps.ed.y - tmps.ed.x * tmps.st.y;
		int check = abs(point.x * A + point.y * B + C);
		if (check < 10 * abs(B) || check < 10 * abs(A)) {
			tmp_type = 5;
			tmp_figure = i;
			return true;
		}
		else
			return false;
	}
}
bool Cex2View::is_online(CPoint& st, CPoint& ed, CPoint& np) {
	CPoint a, b;
	if (st.x < ed.x)
		a = st, b = ed;
	else if(st.x > ed.x)
		a = ed, b = st;
	else
		return false;
	CLine2 tmps(a, b);
	CPoint point = np;
	if (point.x > tmps.ed.x || point.x < tmps.st.x) {
		return false;
	}
	else
	{
		int A = tmps.st.y - tmps.ed.y;
		int B = tmps.ed.x - tmps.st.x;
		int C = tmps.st.x * tmps.ed.y - tmps.ed.x * tmps.st.y;
		int check = abs(point.x * A + point.y * B + C);
		if (check < 10 * abs(B) || check < 10 * abs(A)) {
			return true;
		}
		else
			return false;
	}
}



void Cex2View :: no_red_select(CDC* p) {
	for (int i = 0; i < ((is_over_select || select_num) ? 2 : select_num); i++)

	{
		if (type[i] == 1)
		{
			CDC* pDC = GetDC();
			CPen mypen, * old;
			mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			old = memdc.SelectObject(&mypen);
			myline[figure1[i]].color = RGB(0, 0, 0);
			CPoint st(myline[figure1[i]].st), ed(myline[figure1[i]].ed);
			memdc.MoveTo(st);
			memdc.LineTo(ed);
			memdc.SelectObject(old);
			mypen.DeleteObject();
			//ReleaseDC(pDC);
			//Invalidate();
			myupdate(GetDC());
		}
		else if (type[i] == 2) {
			CDC* pDC = GetDC();
			CPen mypen, * old;
			mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			myround[figure1[i]].color = RGB(0, 0, 0);
			old = memdc.SelectObject(&mypen);
			CBrush* pOldBrush;
			CBrush nullBrush;
			nullBrush.CreateStockObject(NULL_BRUSH);
			pOldBrush = memdc.SelectObject(&nullBrush);
			CPoint center(myround[figure1[i]].org);
			int radius = myround[figure1[i]].r;
			CRect rect(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
			memdc.Ellipse(rect);
			memdc.SelectObject(old);
			mypen.DeleteObject();
			//ReleaseDC(pDC);
			//Invalidate();
			myupdate(GetDC());
		}
		else if (type[i] == 3) {
			if(mymuline[figure1[i]].leibie == 0)
			{
				CDC* pDC = GetDC();
				CPen mypen, * old;
				mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				mymuline[figure1[i]].color = RGB(0, 0, 0);
				old = memdc.SelectObject(&mypen);
				CPoint* pts = mymuline[figure1[i]].muline;
				int nn = mymuline[figure1[i]].num;
				for (int i = 0; i < nn; i++) {
					memdc.MoveTo(pts[i]);
					memdc.LineTo(pts[i + 1]);
				}

				memdc.SelectObject(old);
				mypen.DeleteObject();
				//ReleaseDC(pDC);
				//Invalidate();
				myupdate(GetDC());
			}
			else if(mymuline[figure1[i]].leibie == 1) {
				CPen mypen2;
				CPen* old;
				int nnn = mymuline[figure1[i]].map_bezier;
				mybezier[mymuline[figure1[i]].map_bezier].color = RGB(0, 0, 0);
				mypen2.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				old = memdc.SelectObject(&mypen2);
				CPoint tmp[4];
				tmp[0] = mybezier[nnn].st;
				tmp[1] = mybezier[nnn].ctr1;
				tmp[2] = mybezier[nnn].ctr2;
				tmp[3] = mybezier[nnn].ed;
				memdc.PolyBezier(tmp, 4);
				memdc.SelectObject(old);
				mypen2.DeleteObject();
				myupdate(GetDC());
			}
		}
		else if (type[i] == 5) {
			CDC* pDC = GetDC();
			CPen mypen, * old;
			mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			myrectcolor[figure1[i]] = RGB(0, 0, 0);
			old = memdc.SelectObject(&mypen);
			CBrush* pOldBrush;
			CBrush nullBrush;
			nullBrush.CreateStockObject(NULL_BRUSH);
			pOldBrush = memdc.SelectObject(&nullBrush);

			CRect tmpr(myrect[figure1[i]]);
			CRect tmpr2(myrect2[figure1[i]]);
			draw_tangle(&memdc, tmpr, tmpr2);
			//memdc.Rectangle(tmpr);
			memdc.SelectObject(old);
			mypen.DeleteObject();
			//ReleaseDC(pDC);
			//Invalidate();
			myupdate(GetDC());
		}
		else if (type[i] == 6) {
			CDC* pDC = GetDC();
			CPen mypen, * old;
			mypen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			mybyong[figure1[i]].color = RGB(0, 0, 0);
			old = memdc.SelectObject(&mypen);
			CPoint* mypoint = mybyong[figure1[i]].bpoint;
			int n_byong = mybyong[figure1[i]].n;
			for (int k = 0; k < n_byong - 3; k++) {
				for (int i = 0; i <= 2000; i++) {
					int x = 0, y = 0;
					x = (x_4[i] * mypoint[k].x + x_3[i] * mypoint[k + 1].x + x_2[i] * mypoint[k + 2].x + x_1[i] * mypoint[k + 3].x) / 6;
					y = (x_4[i] * mypoint[k].y + x_3[i] * mypoint[k + 1].y + x_2[i] * mypoint[k + 2].y + x_1[i] * mypoint[k + 3].y) / 6;
					memdc.SetPixel(x, y, RGB(0, 0, 0));
				}
			}
			memdc.SelectObject(old);
			mypen.DeleteObject();
			myupdate(GetDC());
		}
	}
	select_num = 0;
	is_over_select = false;
	last_figure = -1;
	last_type = -1;
}

bool Cex2View::Barsky(CLine2 &tmps) {
	int x_min, x_max;
	double xt, xu;
	int ylow, ytop, xleft, xright;
	ylow = min(jietu_tangle.bottom, jietu_tangle.top);
	ytop = max(jietu_tangle.bottom, jietu_tangle.top);
	xleft = min(jietu_tangle.left, jietu_tangle.right);
	xright = max(jietu_tangle.left, jietu_tangle.right);
	int A = tmps.st.y - tmps.ed.y;
	int B = tmps.ed.x - tmps.st.x;
	int C = tmps.st.x * tmps.ed.y - tmps.ed.x * tmps.st.y;
	xt = (double)(B * ylow + C) / (-A);
	xu = (double)(B * ytop + C) / (-A);
	x_min = max(max(xleft, min(tmps.st.x, tmps.ed.x)), min(xt, xu));
	x_max = min(min(xright, max(tmps.st.x, tmps.ed.x)), max(xt, xu));

	if (x_min > x_max)
		return false;

	if (x_min == x_max)
	{
		tmps.st.x = x_min;
		tmps.st.y = ylow;

		tmps.ed.x = x_max;
		tmps.ed.y = ytop;
	}
	else
	{
		tmps.st.x = x_min;
		tmps.st.y = (double)(C + A * x_min) / (-B) + 0.5;

		tmps.ed.x = x_max;
		tmps.ed.y = (double)(C + A * x_max) / (-B) + 0.5;
	}
	return true;
}



void Cex2View::OnJian()
{
	// TODO: 在此添加命令处理程序代码
	isSelect = false;
	no_red_select(GetDC());
	right_botton = false;
	dynamic_change_color(RGB(0, 0, 0));
	while (!opts.empty())
		opts.pop_back();
	while (!seq.empty())
		seq.pop_back();
	dynamic_draw(GetDC());
	myupdate(GetDC());
	jietu_tangle = CRect(0, 0, 0, 0);
	select_tangle = CRect(0, 0, 0, 0);
	option = 0;
	choice = 0;
	is_jian = true;
	is_jian2 = false;
}

void Cex2View::jian_fang(double tmpcx, double tmpcy, CRect &crect) // x轴的放大倍数， y轴的放大倍数， 窗口矩形的参数
{
	CPoint corg((crect.left + crect.right) / 2,(crect.top + crect.bottom) / 2);
	CPoint norg((jietu_tangle.left + jietu_tangle.right) / 2, (jietu_tangle.top + jietu_tangle.bottom) / 2);
	CPoint Pingyi = corg - norg;
	pingyi(Pingyi);
	suofang(tmpcx, tmpcy, crect);
}

void Cex2View::pingyi(CPoint& Pingyi) {
	CPoint dd = Pingyi;
	jietu_tangle.bottom += dd.y;
	jietu_tangle.top += dd.y;
	jietu_tangle.left += dd.x;
	jietu_tangle.right += dd.x;
	int nn = opts.size();
	int type = -1, num = -1;
	for (int i = 0; i < nn; i++) {
		type = opts[i];
		num = seq[i];
		if (type == 1) {
			myline[num].st += dd;
			myline[num].ed += dd;
			myline[num].color = RGB(0, 0, 255);
		}
		else if (type == 2) {
			myround[num].org += dd;
			myround[num].color = RGB(0, 0, 255);
		}
		else if (type == 3) { //多义线
			CPoint* Point_xifen = mymuline[num].muline;
			int tmpn = mymuline[num].num;
			int x = 0, y = 0;
			mymuline[num].color = RGB(0, 0, 255);
			for (int j = 0; j <= tmpn; j++) {
				Point_xifen[j] += dd;
			}
		}
		else if (type == 4) { // Bezier
			mybezier[num].st += dd;
			mybezier[num].ed += dd;
			mybezier[num].ctr1 += dd;
			mybezier[num].ctr2 += dd;
			mybezier[num].color = RGB(0, 0, 255);
		}
		else if (type == 5) { // 矩形
			myrect[num].bottom += dd.y;
			myrect[num].top += dd.y;
			myrect[num].left += dd.x;
			myrect[num].right += dd.x;

			myrect2[num].bottom += dd.y;
			myrect2[num].top += dd.y;
			myrect2[num].left += dd.x;
			myrect2[num].right += dd.x;

			myrectcolor[num] = RGB(0, 0, 255);
		}
		else if (type == 6) { // B样条
			CPoint* Point_xifen = mybyong[num].bpoint;
			int tmpn = mybyong[num].n;
			mybyong[num].color = RGB(0, 0, 255);
			int x = 0, y = 0;
			for (int j = 0; j < tmpn; j++) {
				Point_xifen[j] += dd;
			}
		}
	}
}
void Cex2View :: suofang(double tmpcx, double tmpcy, CRect& crect) {
	int nn = opts.size();
	int num = -1, type = -1;
	double xm = (crect.left + crect.right) / 2.0;
	double ym = (crect.top + crect.bottom) / 2.0;


	CPoint aa = CPoint(jietu_tangle.left, jietu_tangle.top);
	CPoint bb = CPoint(jietu_tangle.right, jietu_tangle.bottom);
	cal_suo(aa, xm, ym, tmpcx);
	cal_suo(bb, xm, ym, tmpcx);
	jietu_tangle.left = aa.x;
	jietu_tangle.right = bb.x;
	jietu_tangle.top = aa.y;
	jietu_tangle.bottom = bb.y;

	for (int i = 0; i < nn; i++) {
		type = opts[i];
		num = seq[i];
		if (type == 1) {
			cal_suo(myline[num].st, xm, ym, tmpcx);
			cal_suo(myline[num].ed, xm, ym, tmpcx);
			myline[num].color = RGB(0, 0, 255);
		}
		else if (type == 2) {
			CPoint a = myround[num].org;
			CPoint b(myround[num].r, myround[num].r);
			cal_suo(a, xm, ym, tmpcx);
			cal_suo(b, 0, 0, tmpcx);
			myround[num].org = a;
			myround[num].r = b.x;
		}
		else if (type == 3) { //多义线
			CPoint* Point_xifen = mymuline[num].muline;
			int tmpn = mymuline[num].num;
			mymuline[num].color = RGB(0, 0, 255);
			for (int j = 0; j <= tmpn; j++) {
				cal_suo(Point_xifen[j], xm, ym, tmpcx);
			}
		}
		else if (type == 4) { // Bezier
			cal_suo(mybezier[num].st, xm, ym, tmpcx);
			cal_suo(mybezier[num].ed, xm, ym, tmpcx);
			cal_suo(mybezier[num].ctr1, xm, ym, tmpcx);
			cal_suo(mybezier[num].ctr2, xm, ym, tmpcx);
			mybezier[num].color = RGB(0, 0, 255);
		}
		else if (type == 5) { // 矩形
			CPoint a = CPoint(myrect[num].left, myrect[num].top);
			CPoint b = CPoint(myrect[num].right, myrect[num].bottom);
			CPoint a2 = CPoint(myrect2[num].left, myrect2[num].top);
			CPoint b2 = CPoint(myrect2[num].right, myrect2[num].bottom);
			cal_suo(a, xm, ym, tmpcx);
			cal_suo(b, xm, ym, tmpcx);
			cal_suo(a2, xm, ym, tmpcx);
			cal_suo(b2, xm, ym, tmpcx);

			myrect[num].left = a.x;
			myrect[num].right = b.x;
			myrect[num].top = a.y;
			myrect[num].bottom = b.y;

			myrect2[num].left = a2.x;
			myrect2[num].right = b2.x;
			myrect2[num].top = a2.y;
			myrect2[num].bottom = b2.y;
			myrectcolor[num] = RGB(0, 0, 255);
		}
		else if (type == 6) { // B样条
			CPoint* Point_xifen = mybyong[num].bpoint;
			int tmpn = mybyong[num].n;
			mybyong[num].color = RGB(0, 0, 255);
			for (int j = 0; j < tmpn; j++) {
				cal_suo(Point_xifen[j], xm, ym, tmpcx);
			}
		}
	}
}

void Cex2View::OnJiancai2()
{
	isSelect = false;
	no_red_select(GetDC());
	right_botton = false;
	dynamic_change_color(RGB(0, 0, 0));
	while (!opts.empty())
		opts.pop_back();
	while (!seq.empty())
		seq.pop_back();
	dynamic_draw(GetDC());
	myupdate(GetDC());
	jietu_tangle = CRect(0, 0, 0, 0);
	select_tangle = CRect(0, 0, 0, 0);
	option = 0;
	choice = 0;
	is_jian2 = true;
	is_jian = false;
}
void Cex2View::return_all_vector() {
	while (!myline.empty()) {
		myline.pop_back();
	}
	while (!myrect.empty()) {
		myrect.pop_back();
		myrect2.pop_back();
		myrectdots.pop_back();
		myrectcolor.pop_back();
	}
	while (!myround.empty()) {
		myround.pop_back();
	}
	while (!mybezier.empty()) {
		mybezier.pop_back();
	}
	while (!mymuline.empty()) {
		mymuline.pop_back();
	}
	while (!mypoint.empty()) {
		mypoint.pop_back();
	}
	while (!mybyong.empty()) {
		mybyong.pop_back();
	}
	while (!mycolordots.empty()) {
		mycolordots.pop_back();
	}


	for (int i = 0; i < tmpline.size(); i++) {
		myline.push_back(tmpline[i]);
	}
	for (int i = 0; i < tmpround.size(); i++) {
		myround.push_back(tmpround[i]);
	}
	for (int i = 0; i < tmprect.size(); i++) {
		myrect.push_back(tmprect[i]);
		myrect2.push_back(tmprect2[i]);
		myrectcolor.push_back(tmprectcolor[i]);
		myrectdots.push_back(tmprectdots[i]);
	}
	for (int i = 0; i < tmpbezier.size(); i++) {
		mybezier.push_back(tmpbezier[i]);
	}
	for (int i = 0; i < tmpmuline.size(); i++) {
		mymuline.push_back(tmpmuline[i]);
	}
	for (int i = 0; i < tmpbyong.size(); i++) {
		mybyong.push_back(tmpbyong[i]);
	}
	//不存CCOLORPUT
	//不存MYPOINT


	while (!tmpline.empty()) {
		tmpline.pop_back();
	}
	while (!tmprect.empty()) {
		tmprect.pop_back();
		tmprect2.pop_back();
		tmprectdots.pop_back();
		tmprectcolor.pop_back();
	}
	while (!tmpround.empty()) {
		tmpround.pop_back();
	}
	while (!tmpbezier.empty()) {
		tmpbezier.pop_back();
	}
	while (!tmpmuline.empty()) {
		tmpmuline.pop_back();
	}
	while (!tmppoint.empty()) {
		tmppoint.pop_back();
	}
	while (!tmpbyong.empty()) {
		tmpbyong.pop_back();
	}
	while (!tmpcolordots.empty()) {
		tmpcolordots.pop_back();
	}
}
void Cex2View :: xiugai_tangle() {
	int nn = opts.size();
	int type = -1;
	int num = -1;
	int ls = INT_MAX, ts = INT_MAX, rs = INT_MIN, bs = INT_MIN;
	for (int i = 0; i < nn; i++) {
		type = opts[i];
		num = seq[i];
		if (type == 1) {
			ls = min(min(myline[num].st.x, myline[num].ed.x), ls);
			ts = min(min(myline[num].st.y, myline[num].ed.y), ts);
			rs = max(max(myline[num].st.x, myline[num].ed.x), rs);
			bs = max(max(myline[num].st.y, myline[num].ed.y), bs);
			myline[num].color = RGB(0, 0, 255);
		}
		else if (type == 2) {
			ls = min(myround[num].org.x - myround[num].r, ls);
			ts = min(myround[num].org.y - myround[num].r, ts);
			rs = max(myround[num].org.x + myround[num].r, rs);
			bs = max(myround[num].org.y + myround[num].r, bs);
			myround[num].color = RGB(0, 0, 255);
		}
		else if (type == 3) { //多义线
			CPoint* Point_xifen = mymuline[num].muline;
			int ll, rr, tt, bb;
			ll = rr = Point_xifen[0].x;
			tt = bb = Point_xifen[0].y;
			for (int j = 1; j <= mymuline[num].num; j++){
				if (Point_xifen[j].x > rr)
					rr = Point_xifen[j].x;
			if (Point_xifen[j].x < ll)
				ll = Point_xifen[j].x;
			if (Point_xifen[j].y > bb)
				bb = Point_xifen[j].y;
			if (Point_xifen[j].y < tt)
				tt = Point_xifen[j].y;
			}
			ls = min(ll, ls);
			ts = min(tt, ts);
			rs = max(rr, rs);
			bs = max(bb, bs);
			mymuline[num].color = RGB(0, 0, 255);
			/*--------*/
		}
		else if (type == 5) { // 矩形
			ls = min(min(myrect[num].right, myrect[num].left), ls);
			ts = min(min(myrect[num].top, myrect[num].bottom), ts);
			rs = max(max(myrect[num].right, myrect[num].left), rs);
			bs = max(max(myrect[num].top, myrect[num].bottom), bs);

			ls = min(min(myrect2[num].right, myrect2[num].left), ls);
			ts = min(min(myrect2[num].top, myrect2[num].bottom), ts);
			rs = max(max(myrect2[num].right, myrect2[num].left), rs);
			bs = max(max(myrect2[num].top, myrect2[num].bottom), bs);
			myrectcolor[num] = RGB(0, 0, 255);
		}
		else if (type == 6) { // B样条
			CPoint* Point_xifen = mybyong[num].bpoint;
			int ll, rr, tt, bb;
			ll = rr = Point_xifen[0].x;
			tt = bb = Point_xifen[0].y;
			for (int j = 1; j < mybyong[num].n; j++) {
				if (Point_xifen[j].x > rr)
					rr = Point_xifen[j].x;
				if (Point_xifen[j].x < ll)
					ll = Point_xifen[j].x;
				if (Point_xifen[j].y > bb)
					bb = Point_xifen[j].y;
				if (Point_xifen[j].y < tt)
					tt = Point_xifen[j].y;
			}
			ls = min(ll, ls);
			ts = min(tt, ts);
			rs = max(rr, rs);
			bs = max(bb, bs);
		}
	}
	select_tangle.left = ls;
	select_tangle.right = rs;
	select_tangle.top = ts;
	select_tangle.bottom = bs;
	show_select_tangle = select_tangle;
}

