// CNoLine.cpp: 实现文件
//

#include "pch.h"
#include "ex_2.h"
#include "afxdialogex.h"
#include "CNoLine.h"


// CNoLine 对话框

IMPLEMENT_DYNAMIC(CNoLine, CDialogEx)

CNoLine::CNoLine(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CNoLine::~CNoLine()
{
}

void CNoLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNoLine, CDialogEx)
END_MESSAGE_MAP()


// CNoLine 消息处理程序
