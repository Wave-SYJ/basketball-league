// CEditDlg.cpp: 实现文件
//

#include "pch.h"
#include "League.h"
#include "EditGameDlg.h"
#include "afxdialogex.h"


// CEditDlg 对话框

IMPLEMENT_DYNAMIC(CEditGameDlg, CDialogEx)

CEditGameDlg::CEditGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT_GAME, pParent), m_strID(_T(""))
	, m_time(COleDateTime::GetCurrentTime())
	, m_uDlgType(DIALOG_UNKNOWN)
{

}

CEditGameDlg::~CEditGameDlg()
{
}

void CEditGameDlg::SetInitialValue(UINT uDlgType, UINT uIndex, const COleDateTime& time)
{
	m_uDlgType = uDlgType;
	m_strID.Format(_T("%d"), uIndex + 1);
	m_time = time;
	
}

void CEditGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID, m_strID);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_time);
}


BEGIN_MESSAGE_MAP(CEditGameDlg, CDialogEx)
END_MESSAGE_MAP()


// CEditDlg 消息处理程序


BOOL CEditGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (m_uDlgType == DIALOG_INSERT)
		SetWindowText(_T("添加比赛"));
	else
		SetWindowText(_T("修改比赛"));

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
