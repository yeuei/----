#pragma once
#include "afxdialogex.h"


// CNonCenter 对话框

class CNonCenter : public CDialogEx
{
	DECLARE_DYNAMIC(CNonCenter)

public:
	CNonCenter(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNonCenter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NONCENTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
