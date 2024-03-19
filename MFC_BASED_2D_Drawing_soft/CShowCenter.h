#pragma once
#include "afxdialogex.h"


// CShowCenter 对话框

class CShowCenter : public CDialogEx
{
	DECLARE_DYNAMIC(CShowCenter)
public:
	CShowCenter(int x_n, int y_n ,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CShowCenter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CENTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	CString x;
//	CString y;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	CString x;
	CString y;
};
