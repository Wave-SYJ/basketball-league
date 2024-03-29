﻿
// LeagueView.cpp: CLeagueView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "League.h"
#endif

#include "LeagueDoc.h"
#include "LeagueView.h"
#include "MainFrm.h"
#include "FindDlg.h"
#include "TeamDlg.h"

#include <vector>
#include <algorithm>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLeagueView

IMPLEMENT_DYNCREATE(CLeagueView, CListView)

BEGIN_MESSAGE_MAP(CLeagueView, CListView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CLeagueView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_UPDATE_COMMAND_UI(ID_INSERT_PLAYER, &CLeagueView::OnUpdateInsertPlayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PLAYER, &CLeagueView::OnUpdateEditPlayer)
	ON_UPDATE_COMMAND_UI(ID_DELETE_PLAYER, &CLeagueView::OnUpdateDeletePlayer)
	ON_UPDATE_COMMAND_UI(ID_EDIT_GAME, &CLeagueView::OnUpdateEditGame)
	ON_UPDATE_COMMAND_UI(ID_DELETE_GAME, &CLeagueView::OnUpdateDeleteGame)
	ON_COMMAND(ID_FIND, &CLeagueView::OnFind)
	ON_COMMAND(ID_TEAM, &CLeagueView::OnTeam)
	ON_UPDATE_COMMAND_UI(ID_INSERT_GAME, &CLeagueView::OnUpdateInsertGame)
END_MESSAGE_MAP()

// CLeagueView 构造/析构

CLeagueView::CLeagueView() noexcept
	: m_uStatus(STATUS_EMPTY)
{
	// TODO: 在此处添加构造代码

}

CLeagueView::~CLeagueView()
{
}

BOOL CLeagueView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CListView::PreCreateWindow(cs);
}


void CLeagueView::ShowGame(int index)
{
	if (index == -1)
		return;

	m_uStatus = STATUS_GAME;
	POSITION pos = GetDocument()->m_listGame.GetHeadPosition();
	for (UINT i = 0; i != index; i++)
		GetDocument()->m_listGame.GetNext(pos);
	m_pCurrentGame = &GetDocument()->m_listGame.GetAt(pos);
	GetDocument()->UpdateAllViews(NULL);
}

void CLeagueView::ShowPlayer(const CString& strName)
{
	if (strName == "")
		return;

	m_uStatus = STATUS_PLAYER;

	POSITION pos = GetDocument()->m_mapPlayer.GetStartPosition();

	while (pos)
	{
		CString str;
		CPlayer player;
		GetDocument()->m_mapPlayer.GetNextAssoc(pos, str, player);
		if (str == strName) {
			m_currentPlayer = player;
			break;
		}
	}

	GetDocument()->UpdateAllViews(NULL);
}

void CLeagueView::ShowEmpty()
{
	if (this == nullptr)
		return;
	m_uStatus = STATUS_EMPTY;
	GetDocument()->UpdateAllViews(NULL);
}

void CLeagueView::SetTitle(const CString strTitle)
{
	((CMainFrame *)AfxGetMainWnd())->m_wndCaptionBar.SetText(strTitle, CMFCCaptionBar::ALIGN_CENTER);
}

void CLeagueView::OnDraw(CDC* /*pDC*/)
{
	CLeagueDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
}


void CLeagueView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: 调用 GetListCtrl() 直接访问 ListView 的列表控件，
	//  从而可以用项填充 ListView。
	CListCtrl* lsCtrl = &GetListCtrl();
	lsCtrl->ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	lsCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}


// CLeagueView 打印


void CLeagueView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CLeagueView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CLeagueView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CLeagueView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CLeagueView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CLeagueView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
//#ifndef shared_handlers
//	theapp.getcontextmenumanager()->showpopupmenu(idr_popup_edit, point.x, point.y, this, true);
//#endif
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_PLAYER, point.x, point.y, this, TRUE);
}


// CLeagueView 诊断

#ifdef _DEBUG
void CLeagueView::AssertValid() const
{
	CListView::AssertValid();
}

void CLeagueView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CLeagueDoc* CLeagueView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLeagueDoc)));
	return (CLeagueDoc*)m_pDocument;
}
#endif //_DEBUG


// CLeagueView 消息处理程序


void CLeagueView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CListCtrl* lsCtrl = &GetListCtrl();
	lsCtrl->DeleteAllItems();
	while (lsCtrl->DeleteColumn(0));
	CString strTmp;

	if (m_uStatus == STATUS_EMPTY) {
		SetTitle(_T("空白页"));
		return;
	}
		

	if (m_uStatus == STATUS_GAME) {
		strTmp.Format(_T("比赛信息 - %s"), m_pCurrentGame->m_time.Format(VAR_DATEVALUEONLY));
		SetTitle(strTmp);

		lsCtrl->InsertColumn(0, _T("#"), 0, 50);
		lsCtrl->InsertColumn(1, _T("姓名"), 0, 150);
		lsCtrl->InsertColumn(2, _T("所属队名"), 0, 150);
		lsCtrl->InsertColumn(3, _T("三分球个数"), 0, 150);
		lsCtrl->InsertColumn(4, _T("篮板球个数"), 0, 150);
		lsCtrl->InsertColumn(5, _T("扣篮成功次数"), 0, 150);
		lsCtrl->InsertColumn(6, _T("抢断次数"), 0, 150);
		lsCtrl->InsertColumn(7, _T("得分"), 0, 150);

		CList<CPlayer>* listPlayers = &m_pCurrentGame->m_listPlayer;
		POSITION pos = listPlayers->GetHeadPosition();
		for (int i = 0; pos != NULL; i++) {
			CPlayer* playerTmp = &listPlayers->GetNext(pos);

			strTmp.Format(_T("%d"), i + 1);
			lsCtrl->InsertItem(i, strTmp);
			lsCtrl->SetItemText(i, 1, playerTmp->m_strName);
			lsCtrl->SetItemText(i, 2, playerTmp->m_strTeam);
			strTmp.Format(_T("%d"), playerTmp->m_uThreePointer);
			lsCtrl->SetItemText(i, 3, strTmp);
			strTmp.Format(_T("%d"), playerTmp->m_uRebound);
			lsCtrl->SetItemText(i, 4, strTmp);
			strTmp.Format(_T("%d"), playerTmp->m_uDrunk);
			lsCtrl->SetItemText(i, 5, strTmp);
			strTmp.Format(_T("%d"), playerTmp->m_uSteal);
			lsCtrl->SetItemText(i, 6, strTmp);
			strTmp.Format(_T("%d"), playerTmp->m_uScore);
			lsCtrl->SetItemText(i, 7, strTmp);
		}
	}

	if (m_uStatus == STATUS_PLAYER) {
		SetTitle(CString("个人汇总 - ") + m_currentPlayer.m_strName);

		lsCtrl->InsertColumn(0, _T("属性"), 0, 200);
		lsCtrl->InsertColumn(1, _T("汇总值"), 0, 450);

		lsCtrl->InsertItem(0, _T("姓名"));
		lsCtrl->SetItemText(0, 1, m_currentPlayer.m_strName);

		lsCtrl->InsertItem(1, _T("所属队名"));
		lsCtrl->SetItemText(1, 1, m_currentPlayer.m_strTeam);

		strTmp.Format(_T("%d"), m_currentPlayer.m_uThreePointer);
		lsCtrl->InsertItem(2, _T("三分球个数"));
		lsCtrl->SetItemText(2, 1, strTmp);

		strTmp.Format(_T("%d"), m_currentPlayer.m_uRebound);
		lsCtrl->InsertItem(3, _T("篮板球个数"));
		lsCtrl->SetItemText(3, 1, strTmp);

		strTmp.Format(_T("%d"), m_currentPlayer.m_uDrunk);
		lsCtrl->InsertItem(4, _T("扣篮成功个数"));
		lsCtrl->SetItemText(4, 1, strTmp);

		strTmp.Format(_T("%d"), m_currentPlayer.m_uSteal);
		lsCtrl->InsertItem(5, _T("抢断次数"));
		lsCtrl->SetItemText(5, 1, strTmp);

		strTmp.Format(_T("%d"), m_currentPlayer.m_uScore);
		lsCtrl->InsertItem(6, _T("得分"));
		lsCtrl->SetItemText(6, 1, strTmp);

		strTmp.Format(_T("%d"), m_currentPlayer.m_uGame);
		lsCtrl->InsertItem(7, _T("比赛场数"));
		lsCtrl->SetItemText(7, 1, strTmp);
	}
}


void CLeagueView::OnUpdateInsertPlayer(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_uStatus == STATUS_GAME);
}


void CLeagueView::OnUpdateEditPlayer(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_uStatus == STATUS_GAME && GetListCtrl().GetSelectionMark() != -1);
}


void CLeagueView::OnUpdateDeletePlayer(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_uStatus == STATUS_GAME && GetListCtrl().GetSelectionMark() != -1);
}


void CLeagueView::OnUpdateEditGame(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_uStatus == STATUS_GAME);
}


void CLeagueView::OnUpdateDeleteGame(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_uStatus == STATUS_GAME);
}

bool pairSortFun(pair<CPlayer, double> elem1, pair<CPlayer, double> elem2)
{
	return elem1.second > elem2.second;
}


void CLeagueView::OnFind()
{
	CFindDlg dlg;
	CString strTmp;

	if (dlg.DoModal() != IDOK)
		return;

	CListCtrl* lsCtrl = &GetListCtrl();
	lsCtrl->DeleteAllItems();
	while (lsCtrl->DeleteColumn(0));

	strTmp.Format(_T("查询 - 根据%s"), dlg.m_strSubject);
	SetTitle(strTmp);

	lsCtrl->InsertColumn(0, _T(""), 0, 50);
	lsCtrl->InsertColumn(1, _T("姓名"), 0, 100);
	lsCtrl->InsertColumn(2, _T("所在队名"), 0, 200);
	strTmp.Format(_T("平均%s"), dlg.m_strSubject);
	lsCtrl->InsertColumn(3, strTmp, 0, 150);

	vector<pair<CPlayer, double> > vec;
	POSITION pos = GetDocument()->m_mapPlayer.GetStartPosition();

	while (pos)
	{
		CString str;
		CPlayer player;
		GetDocument()->m_mapPlayer.GetNextAssoc(pos, str, player);

		if (dlg.m_strSubject == _T("三分球个数"))
			vec.push_back(make_pair(player, player.m_uThreePointer / (player.m_uGame * 1.0)));
		if (dlg.m_strSubject == _T("篮板球个数"))
			vec.push_back(make_pair(player, player.m_uRebound / (player.m_uGame * 1.0)));
		if (dlg.m_strSubject == _T("扣篮成功次数"))
			vec.push_back(make_pair(player, player.m_uDrunk / (player.m_uGame * 1.0)));
		if (dlg.m_strSubject == _T("抢断次数"))
			vec.push_back(make_pair(player, player.m_uSteal / (player.m_uGame * 1.0)));
		if (dlg.m_strSubject == _T("得分"))
			vec.push_back(make_pair(player, player.m_uScore / (player.m_uGame * 1.0)));
	}
	sort(vec.begin(), vec.end(), pairSortFun);

	for (UINT i = 0; i < min(vec.size(), dlg.m_uCount); i++) {
		strTmp.Format(_T("%d"), i + 1);
		lsCtrl->InsertItem(i, strTmp);
		lsCtrl->SetItemText(i, 1, vec[i].first.m_strName);
		lsCtrl->SetItemText(i, 2, vec[i].first.m_strTeam);
		strTmp.Format(_T("%lf"), vec[i].second);
		lsCtrl->SetItemText(i, 3, strTmp);
	}
}


void CLeagueView::OnTeam()
{
	CTeamDlg dlg;
	CString strTmp;

	if (dlg.DoModal() != IDOK)
		return;

	CListCtrl* lsCtrl = &GetListCtrl();
	lsCtrl->DeleteAllItems();
	while (lsCtrl->DeleteColumn(0));

	strTmp.Format(_T("查询 - 球队：%s"), dlg.m_strTeam);
	SetTitle(strTmp);

	lsCtrl->InsertColumn(0, _T(""), 0, 50);
	lsCtrl->InsertColumn(1, _T("姓名"), 0, 150);
	lsCtrl->InsertColumn(2, _T("所属队名"), 0, 150);
	lsCtrl->InsertColumn(3, _T("三分球个数"), 0, 150);
	lsCtrl->InsertColumn(4, _T("篮板球个数"), 0, 150);
	lsCtrl->InsertColumn(5, _T("扣篮成功次数"), 0, 150);
	lsCtrl->InsertColumn(6, _T("抢断次数"), 0, 150);
	lsCtrl->InsertColumn(7, _T("得分"), 0, 150);

	POSITION pos = GetDocument()->m_mapPlayer.GetStartPosition();

	for (int i = 0; pos; i++)
	{
		CString str;
		CPlayer player;
		GetDocument()->m_mapPlayer.GetNextAssoc(pos, str, player);

		if (player.m_strTeam != dlg.m_strTeam) {
			i--;
			continue;
		}

		strTmp.Format(_T("%d"), i + 1);
		lsCtrl->InsertItem(i, strTmp);
		lsCtrl->SetItemText(i, 1, player.m_strName);
		lsCtrl->SetItemText(i, 2, player.m_strTeam);
		strTmp.Format(_T("%d"), player.m_uThreePointer);
		lsCtrl->SetItemText(i, 3, strTmp);
		strTmp.Format(_T("%d"), player.m_uRebound);
		lsCtrl->SetItemText(i, 4, strTmp);
		strTmp.Format(_T("%d"), player.m_uDrunk);
		lsCtrl->SetItemText(i, 5, strTmp);
		strTmp.Format(_T("%d"), player.m_uSteal);
		lsCtrl->SetItemText(i, 6, strTmp);
		strTmp.Format(_T("%d"), player.m_uScore);
		lsCtrl->SetItemText(i, 7, strTmp);
	}
}


void CLeagueView::OnUpdateInsertGame(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
