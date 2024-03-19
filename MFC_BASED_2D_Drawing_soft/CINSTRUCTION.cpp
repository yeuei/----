// CINSTRUCTION.cpp: 实现文件
//

#include "pch.h"
#include "ex_2.h"
#include "afxdialogex.h"
#include "CINSTRUCTION.h"


// CINSTRUCTION 对话框

IMPLEMENT_DYNAMIC(CINSTRUCTION, CDialogEx)

CINSTRUCTION::CINSTRUCTION(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDM_HELP, pParent)
{

}

CINSTRUCTION::~CINSTRUCTION()
{
}

void CINSTRUCTION::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CINSTRUCTION, CDialogEx)
END_MESSAGE_MAP()


// CINSTRUCTION 消息处理程序
