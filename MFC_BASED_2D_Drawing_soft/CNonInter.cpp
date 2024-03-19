// CNonInter.cpp: 实现文件
//

#include "pch.h"
#include "ex_2.h"
#include "afxdialogex.h"
#include "CNonInter.h"


// CNonInter 对话框

IMPLEMENT_DYNAMIC(CNonInter, CDialogEx)

CNonInter::CNonInter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NONINTER, pParent)
{

}

CNonInter::~CNonInter()
{
}

void CNonInter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNonInter, CDialogEx)
END_MESSAGE_MAP()


// CNonInter 消息处理程序
