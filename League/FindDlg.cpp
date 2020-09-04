// FindDlg.cpp: 实现文件
//

#include "pch.h"
#include "League.h"
#include "FindDlg.h"
#include "afxdialogex.h"


// CFindDlg 对话框

IMPLEMENT_DYNAMIC(CFindDlg, CDialogEx)

CFindDlg::CFindDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIND, pParent)
	, m_uCount(0)
	, m_strSubject(_T(""))
{

}

CFindDlg::~CFindDlg()
{
}

void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SUBJECT, m_comboSubject);
	DDX_Text(pDX, IDC_COUNT, m_uCount);
	DDX_CBString(pDX, IDC_SUBJECT, m_strSubject);
}


BEGIN_MESSAGE_MAP(CFindDlg, CDialogEx)
END_MESSAGE_MAP()


// CFindDlg 消息处理程序


BOOL CFindDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_comboSubject.InsertString(0, _T("三分球个数"));
	m_comboSubject.InsertString(1, _T("篮板球个数"));
	m_comboSubject.InsertString(2, _T("扣篮成功次数"));
	m_comboSubject.InsertString(3, _T("抢断次数"));
	m_comboSubject.InsertString(4, _T("得分"));

	SetWindowText(_T("根据项目排序"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

