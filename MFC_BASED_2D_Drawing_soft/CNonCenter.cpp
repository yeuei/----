// CNonCenter.cpp: 实现文件
//

#include "pch.h"
#include "ex_2.h"
#include "afxdialogex.h"
#include "CNonCenter.h"


// CNonCenter 对话框

IMPLEMENT_DYNAMIC(CNonCenter, CDialogEx)

CNonCenter::CNonCenter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NONCENTER, pParent)
{

}

CNonCenter::~CNonCenter()
{
}

void CNonCenter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNonCenter, CDialogEx)
END_MESSAGE_MAP()


// CNonCenter 消息处理程序
