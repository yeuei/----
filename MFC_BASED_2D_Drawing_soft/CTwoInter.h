#pragma once
#include "afxdialogex.h"


// CTwoInter 对话框

class CTwoInter : public CDialogEx
{
	DECLARE_DYNAMIC(CTwoInter)

public:
	CTwoInter(double x1, double y1, double x2, double y2, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTwoInter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TWO_INTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	CString x1;
	CString y1;
	CString x2;
	CString y2;
};
