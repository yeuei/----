#pragma once
#include "afxdialogex.h"


// CINSTRUCTION 对话框

class CINSTRUCTION : public CDialogEx
{
	DECLARE_DYNAMIC(CINSTRUCTION)

public:
	CINSTRUCTION(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CINSTRUCTION();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDM_HELP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
