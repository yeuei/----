#pragma once
#include "afxdialogex.h"


// CNoLine 对话框

class CNoLine : public CDialogEx
{
	DECLARE_DYNAMIC(CNoLine)

public:
	CNoLine(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNoLine();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
