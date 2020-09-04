// TeamDlg.cpp: 实现文件
//

#include "pch.h"
#include "League.h"
#include "TeamDlg.h"
#include "afxdialogex.h"


// CTeamDlg 对话框

IMPLEMENT_DYNAMIC(CTeamDlg, CDialogEx)

CTeamDlg::CTeamDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEAM, pParent)
	, m_strTeam(_T(""))
{

}

CTeamDlg::~CTeamDlg()
{
}

void CTeamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_strTeam);
}


BEGIN_MESSAGE_MAP(CTeamDlg, CDialogEx)
END_MESSAGE_MAP()


// CTeamDlg 消息处理程序


BOOL CTeamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(_T("根据球队查询"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
