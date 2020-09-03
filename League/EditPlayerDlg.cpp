// EditPlayerDlg.cpp: 实现文件
//

#include "pch.h"
#include "League.h"
#include "EditPlayerDlg.h"
#include "afxdialogex.h"
#include "Player.h"

// CEditPlayerDlg 对话框

IMPLEMENT_DYNAMIC(CEditPlayerDlg, CDialogEx)

CEditPlayerDlg::CEditPlayerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT_PLAYER, pParent)
	, m_uId(0)
	, m_strName(_T(""))
	, m_strTeam(_T(""))
	, m_uThreePointer(0)
	, m_uRebound(0)
	, m_uDrunk(0)
	, m_uSteal(0)
	, m_uScore(0)
{

}

CEditPlayerDlg::~CEditPlayerDlg()
{
}

void CEditPlayerDlg::SetInitialValue(UINT uDlgType, UINT uIndex, const CPlayer * player)
{
	m_uDlgType = uDlgType;
	m_uId = uIndex;
	if (uDlgType == DIALOG_EDIT) {
		m_strName = player->m_strName;
		m_strTeam = player->m_strTeam;
		m_uThreePointer = player->m_uThreePointer;
		m_uRebound = player->m_uRebound;
		m_uDrunk = player->m_uDrunk;
		m_uSteal = player->m_uSteal;
		m_uScore = player->m_uScore;
	}
}

void CEditPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	  DDX_Text(pDX, IDC_ID, m_uId);
	  DDX_Text(pDX, IDC_NAME, m_strName);
	  DDX_Text(pDX, IDC_TEAM, m_strTeam);
	  DDX_Text(pDX, IDC_THREE_POINTER, m_uThreePointer);
	  DDX_Text(pDX, IDC_REBOUND, m_uRebound);
	  DDX_Text(pDX, IDC_DRUNK, m_uDrunk);
	  DDX_Text(pDX, IDC_STEAL, m_uSteal);
	  DDX_Text(pDX, IDC_SCORE, m_uScore);
}


BEGIN_MESSAGE_MAP(CEditPlayerDlg, CDialogEx)
END_MESSAGE_MAP()


// CEditPlayerDlg 消息处理程序
