#pragma once
#include "afxdialogex.h"


// CNonInter 对话框

class CNonInter : public CDialogEx
{
	DECLARE_DYNAMIC(CNonInter)

public:
	CNonInter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNonInter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NONINTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
