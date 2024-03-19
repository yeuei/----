// CTwoInter.cpp: 实现文件
//

#include "pch.h"
#include "ex_2.h"
#include "afxdialogex.h"
#include "CTwoInter.h"


// CTwoInter 对话框

IMPLEMENT_DYNAMIC(CTwoInter, CDialogEx)

CTwoInter::CTwoInter(double x1, double y1, double x2, double y2, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TWO_INTER, pParent)
{
	(this->x1).Format(_T("%.3lf"), x1);
	(this->y1).Format(_T("%.3lf"), y1);
	(this->x2).Format(_T("%.3lf"), x2);
	(this->y2).Format(_T("%.3lf"), y2);
}

CTwoInter::~CTwoInter()
{
}

void CTwoInter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT6, x1);
	DDX_Text(pDX, IDC_EDIT7, y1);
	DDX_Text(pDX, IDC_EDIT4, x2);
	DDX_Text(pDX, IDC_EDIT5, y2);
}


BEGIN_MESSAGE_MAP(CTwoInter, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT6, &CTwoInter::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CTwoInter::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT4, &CTwoInter::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CTwoInter::OnEnChangeEdit5)
END_MESSAGE_MAP()


// CTwoInter 消息处理程序


void CTwoInter::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT6); // 注意：你需要使用正确的控件ID
	// 设置文本内容
	pEdit->SetWindowText(x1);
	// TODO:  在此添加控件通知处理程序代码
}


void CTwoInter::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT7); // 注意：你需要使用正确的控件ID
	// 设置文本内容
	pEdit->SetWindowText(y1);
	// TODO:  在此添加控件通知处理程序代码
}


void CTwoInter::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4); // 注意：你需要使用正确的控件ID
	// 设置文本内容
	pEdit->SetWindowText(x2);
	// TODO:  在此添加控件通知处理程序代码
}


void CTwoInter::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT5); // 注意：你需要使用正确的控件ID
	// 设置文本内容
	pEdit->SetWindowText(y2);
	// TODO:  在此添加控件通知处理程序代码
}
