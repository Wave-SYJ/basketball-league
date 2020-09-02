#pragma once
#include "Game.h"

// CEditDlg 对话框

#define DIALOG_INSERT	0
#define DIALOG_EDIT		1
#define DIALOG_UNKNOWN	2

class CEditDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditDlg)

public:
	CEditDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEditDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT };
#endif

public:
	void SetInitialValue(UINT uDlgType, UINT uIndex, const COleDateTime& time);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_strID;
	COleDateTime m_time;
	UINT m_uDlgType;
	virtual BOOL OnInitDialog();
};
