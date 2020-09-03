
#include "pch.h"
#include "framework.h"
#include "mainfrm.h"
#include "GameView.h"
#include "Resource.h"
#include "League.h"
#include "LeagueView.h"
#include "Game.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CGameView::CGameView() noexcept
{
}

CGameView::~CGameView()
{
}

BEGIN_MESSAGE_MAP(CGameView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar 消息处理程序

int CGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT;

	if (!m_wndGameView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("未能创建文件视图\n");
		return -1;      // 未能创建
	}

	m_wndGameView.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_wndGameView.InsertColumn(0, _T("序号"));
	m_wndGameView.InsertColumn(1, _T("比赛日期"));
	m_wndGameView.SetColumnWidth(0, 50);
	m_wndGameView.SetColumnWidth(1, 180);

	// 加载视图图像: 
	m_GameViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndGameView.SetImageList(&m_GameViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 填入一些静态树视图数据(此处只需填入虚拟代码，而不是复杂的数据)
	AdjustLayout();

	return 0;
}

void CGameView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CGameView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndGameView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项: 
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != nullptr)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
}

void CGameView::AdjustLayout()
{
	if (GetSafeHwnd() == nullptr)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndGameView.SetWindowPos(nullptr, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CGameView::OnProperties()
{
	AfxMessageBox(_T("属性...."));

}

void CGameView::OnFileOpen()
{
	// TODO: 在此处添加命令处理程序代码
}

void CGameView::OnFileOpenWith()
{
	// TODO: 在此处添加命令处理程序代码
}

void CGameView::OnDummyCompile()
{
	// TODO: 在此处添加命令处理程序代码
}

void CGameView::OnEditCut()
{
	// TODO: 在此处添加命令处理程序代码
}

void CGameView::OnEditCopy()
{
	// TODO: 在此处添加命令处理程序代码
}

void CGameView::OnEditClear()
{
	// TODO: 在此处添加命令处理程序代码
}

void CGameView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndGameView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CGameView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndGameView.SetFocus();
}

void CGameView::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* 锁定*/);

	m_GameViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_GameViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_GameViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndGameView.SetImageList(&m_GameViewImages, TVSIL_NORMAL);
}

void CGameView::UpdateView(CList<CGame>* pList)
{
	POSITION pos = pList->GetHeadPosition();
	for (int i = 0; pos != NULL; i++) {
		CGame* pTmp = &pList->GetNext(pos);
		//CString strTmp;
		//strTmp.Format(_T("%d %s"), i + 1, pTmp->m_time.Format(VAR_DATEVALUEONLY));
		//m_wndGameView.InsertItem(i, strTmp);

		CString strTmp;
		strTmp.Format(_T("%d"), i + 1);
		m_wndGameView.InsertItem(i, strTmp);
		m_wndGameView.SetItemText(i, 1, pTmp->m_time.Format(VAR_DATEVALUEONLY));
	}
}

void CGameView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CLeagueView* view = (CLeagueView *)(((CFrameWnd *)AfxGetMainWnd())->GetActiveView());

	if (view != nullptr)
		view->ShowGame(m_wndGameView.GetSelectionMark());

	CDockablePane::OnLButtonDblClk(nFlags, point);
}
