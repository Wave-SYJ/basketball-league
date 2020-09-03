
#include "pch.h"
#include "framework.h"
#include "ViewList.h"
#include "LeagueView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewList::CViewList(UINT uStatus) noexcept
	: m_uStatus(uStatus)
{
}

CViewList::~CViewList()
{
}

BEGIN_MESSAGE_MAP(CViewList, CListCtrl)
//	ON_NOTIFY_REFLECT(NM_CLICK, &CViewList::OnNMClick)
ON_NOTIFY_REFLECT(NM_CLICK, &CViewList::OnNMClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree 消息处理程序

BOOL CViewList::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CListCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != nullptr);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != nullptr)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


//void CViewList::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	AfxMessageBox(_T("Click"));
//	*pResult = 0;
//}


void CViewList::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	CLeagueView* view = (CLeagueView*)(((CMainFrame *)AfxGetMainWnd())->GetActiveView());

	if (-1 == GetSelectionMark()) {
		view->ShowEmpty();
	}

	if (m_uStatus == STATUS_GAME)
		view->ShowGame(GetSelectionMark());
	else
		view->ShowPlayer(GetSelectionMark());

	*pResult = 0;
}
