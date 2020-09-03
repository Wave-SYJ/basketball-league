#pragma once
#include "Game.h"

// CEditDlg 对话框



class CEditGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditGameDlg)

public:
	CEditGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEditGameDlg();

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
