#pragma once
#include "afxdialogex.h"


// COneInter 对话框

class COneInter : public CDialogEx
{
	DECLARE_DYNAMIC(COneInter)

public:
	COneInter(double x, double y, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COneInter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ONE_INTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString x;
	CString y;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
};
