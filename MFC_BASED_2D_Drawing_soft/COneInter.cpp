// COneInter.cpp: 实现文件
//

#include "pch.h"
#include "ex_2.h"
#include "afxdialogex.h"
#include "COneInter.h"


// COneInter 对话框

IMPLEMENT_DYNAMIC(COneInter, CDialogEx)

COneInter::COneInter(double x, double y, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ONE_INTER, pParent)
{
	(this->x).Format(_T("%.3lf"),x);
	(this->y).Format(_T("%.3lf"),y);
}

COneInter::~COneInter()
{
}

void COneInter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, x);
	DDX_Text(pDX, IDC_EDIT4, y);
}


BEGIN_MESSAGE_MAP(COneInter, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT3, &COneInter::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &COneInter::OnEnChangeEdit4)
END_MESSAGE_MAP()


// COneInter 消息处理程序


void COneInter::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT3); // 注意：你需要使用正确的控件ID
	// 设置文本内容
	pEdit->SetWindowText(x);
	// TODO:  在此添加控件通知处理程序代码
}


void COneInter::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT4); // 注意：你需要使用正确的控件ID
	// 设置文本内容
	pEdit->SetWindowText(y);
	// TODO:  在此添加控件通知处理程序代码
}
