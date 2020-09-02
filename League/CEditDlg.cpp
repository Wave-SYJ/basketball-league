// CEditDlg.cpp: 实现文件
//

#include "pch.h"
#include "League.h"
#include "CEditDlg.h"
#include "afxdialogex.h"


// CEditDlg 对话框

IMPLEMENT_DYNAMIC(CEditDlg, CDialogEx)

CEditDlg::CEditDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EDIT, pParent), m_strID(_T(""))
	, m_time(COleDateTime::GetCurrentTime())
	, m_uDlgType(DIALOG_UNKNOWN)
{

}

CEditDlg::~CEditDlg()
{
}

void CEditDlg::SetInitialValue(UINT uDlgType, UINT uIndex, const COleDateTime& time)
{
	m_uDlgType = uDlgType;
	m_strID.Format(_T("%d"), uIndex);
	m_time = time;
	
}

void CEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ID, m_strID);
	DDX_DateTimeCtrl(pDX, IDC_DATE, m_time);
}


BEGIN_MESSAGE_MAP(CEditDlg, CDialogEx)
END_MESSAGE_MAP()


// CEditDlg 消息处理程序


BOOL CEditDlg::OnInitDialog()
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
