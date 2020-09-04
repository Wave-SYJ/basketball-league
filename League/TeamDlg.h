﻿#pragma once


// CTeamDlg 对话框

class CTeamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTeamDlg)

public:
	CTeamDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTeamDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strTeam;
	virtual BOOL OnInitDialog();
};
