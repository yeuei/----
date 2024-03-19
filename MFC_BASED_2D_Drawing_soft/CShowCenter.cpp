// CShowCenter.cpp: 实现文件
//

#include "pch.h"
#include "ex_2.h"
#include "afxdialogex.h"
#include "CShowCenter.h"


// CShowCenter 对话框

IMPLEMENT_DYNAMIC(CShowCenter, CDialogEx)

CShowCenter::CShowCenter(int x_n, int y_n, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CENTER, pParent)
{
	x.Format(_T("%d"), x_n);
	y.Format(_T("%d"), y_n);
}

CShowCenter::~CShowCenter()
{
}

void CShowCenter::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, x);
    DDX_Text(pDX, IDC_EDIT2, y);
}


BEGIN_MESSAGE_MAP(CShowCenter, CDialogEx)
    ON_EN_CHANGE(IDC_EDIT1, &CShowCenter::OnEnChangeEdit1)
    ON_EN_CHANGE(IDC_EDIT2, &CShowCenter::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CShowCenter 消息处理程序

void CShowCenter::OnEnChangeEdit1()
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogEx::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。
    CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1); // 注意：你需要使用正确的控件ID
    // 设置文本内容
    pEdit->SetWindowText(x);
    // TODO:  在此添加控件通知处理程序代码
}


void CShowCenter::OnEnChangeEdit2()
{
    // TODO:  如果该控件是 RICHEDIT 控件，它将不
    // 发送此通知，除非重写 CDialogEx::OnInitDialog()
    // 函数并调用 CRichEditCtrl().SetEventMask()，
    // 同时将 ENM_CHANGE 标志“或”运算到掩码中。
    CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT2); // 注意：你需要使用正确的控件ID
    // 设置文本内容
    pEdit->SetWindowText(y);
    // TODO:  在此添加控件通知处理程序代码
}
