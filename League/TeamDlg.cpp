﻿// TeamDlg.cpp: 实现文件
//

#include "pch.h"
#include "League.h"
#include "TeamDlg.h"
#include "afxdialogex.h"


// CTeamDlg 对话框

IMPLEMENT_DYNAMIC(CTeamDlg, CDialogEx)

CTeamDlg::CTeamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEAM, pParent)
{

}

CTeamDlg::~CTeamDlg()
{
}

void CTeamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTeamDlg, CDialogEx)
END_MESSAGE_MAP()


// CTeamDlg 消息处理程序