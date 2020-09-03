
// LeagueDoc.cpp: CLeagueDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "League.h"
#endif

#include "LeagueView.h"
#include "LeagueDoc.h"
#include "MainFrm.h"
#include "EditPlayerDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLeagueDoc

IMPLEMENT_DYNCREATE(CLeagueDoc, CDocument)

BEGIN_MESSAGE_MAP(CLeagueDoc, CDocument)
	ON_COMMAND(ID_INSERT_GAME, &CLeagueDoc::OnInsertGame)
	ON_COMMAND(ID_INSERT_PLAYER, &CLeagueDoc::OnInsertPlayer)
	ON_COMMAND(ID_EDIT_PLAYER, &CLeagueDoc::OnEditPlayer)
	ON_COMMAND(ID_DELETE_PLAYER, &CLeagueDoc::OnDeletePlayer)
	ON_COMMAND(ID_EDIT_GAME, &CLeagueDoc::OnEditGame)
	ON_COMMAND(ID_DELETE_GAME, &CLeagueDoc::OnDeleteGame)
END_MESSAGE_MAP()


// CLeagueDoc 构造/析构

CLeagueDoc::CLeagueDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CLeagueDoc::~CLeagueDoc()
{
}

void CLeagueDoc::Recalculate()
{
	m_mapPlayer.RemoveAll();

	POSITION posGame = m_listGame.GetHeadPosition();
	while (posGame != NULL) {
		CGame* game = &m_listGame.GetAt(posGame);
		POSITION posPlayer = game->m_listPlayer.GetHeadPosition();
		while (posPlayer != NULL) {
			CPlayer* player = &game->m_listPlayer.GetAt(posPlayer);
			CPlayer playerCurrent;
			if (m_mapPlayer.Lookup(player->m_strName, playerCurrent)) {
				playerCurrent.m_uDrunk += player->m_uDrunk;
				playerCurrent.m_uGame += 1;
				playerCurrent.m_uRebound += player->m_uRebound;
				playerCurrent.m_uScore += player->m_uScore;
				playerCurrent.m_uSteal += player->m_uSteal;
				playerCurrent.m_uThreePointer += player->m_uThreePointer;
				m_mapPlayer.SetAt(player->m_strName, playerCurrent);
			}
			else
				m_mapPlayer.SetAt(player->m_strName, *player);
			
			m_listGame.GetNext(posPlayer);
		}
		game->m_listPlayer.GetNext(posGame);
	}
	((CMainFrame*)AfxGetMainWnd())->m_wndPlayerView.UpdateView(m_mapPlayer);
}

BOOL CLeagueDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CLeagueDoc 序列化

void CLeagueDoc::Serialize(CArchive& ar)
{
	m_listGame.Serialize(ar);
	m_mapPlayer.Serialize(ar);
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CLeagueDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CLeagueDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CLeagueDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CLeagueDoc 诊断

#ifdef _DEBUG
void CLeagueDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLeagueDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CLeagueDoc 命令


void CLeagueDoc::OnInsertGame()
{
	CEditGameDlg dlgEdit;
	dlgEdit.SetInitialValue(DIALOG_INSERT, m_listGame.GetSize(), COleDateTime::GetCurrentTime());
	if (dlgEdit.DoModal() == IDOK) {
		m_listGame.AddTail(CGame(dlgEdit.m_time));
	}

	Recalculate();
	((CMainFrame*)AfxGetMainWnd())->m_wndGameView.UpdateView(&m_listGame);
}


void CLeagueDoc::OnInsertPlayer()
{
	CLeagueView* view = (CLeagueView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
	CGame* gameCurrent = view->m_pCurrentGame;

	CEditPlayerDlg dlgEdit;
	dlgEdit.SetInitialValue(DIALOG_INSERT, gameCurrent->m_listPlayer.GetSize(), nullptr);
	if (dlgEdit.DoModal() == IDOK) {
		gameCurrent->m_listPlayer.AddTail(CPlayer(dlgEdit.m_strName, dlgEdit.m_strTeam, dlgEdit.m_uThreePointer, dlgEdit.m_uRebound, dlgEdit.m_uDrunk, dlgEdit.m_uSteal, dlgEdit.m_uScore, 0));
	}

	Recalculate();
	UpdateAllViews(NULL);
}


void CLeagueDoc::OnEditPlayer()
{
	CLeagueView* view = (CLeagueView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
	CGame* gameCurrent = view->m_pCurrentGame;
	CPlayer* playerCurrent = nullptr;

	UINT id = view->GetListCtrl().GetSelectionMark();
	POSITION pos = gameCurrent->m_listPlayer.GetHeadPosition();
	for (UINT i = 0; i != id; i++) {
		if (i == id)
			break;
		gameCurrent->m_listPlayer.GetNext(pos);
	}
	playerCurrent = &gameCurrent->m_listPlayer.GetAt(pos);

	CEditPlayerDlg dlgEdit;
	dlgEdit.SetInitialValue(DIALOG_EDIT, gameCurrent->m_listPlayer.GetSize(), playerCurrent);
	if (dlgEdit.DoModal() == IDOK) {
		playerCurrent->m_strName = dlgEdit.m_strName;
		playerCurrent->m_strTeam = dlgEdit.m_strTeam;
		playerCurrent->m_uDrunk = dlgEdit.m_uDrunk;
		playerCurrent->m_uRebound = dlgEdit.m_uRebound;
		playerCurrent->m_uScore = dlgEdit.m_uScore;
		playerCurrent->m_uSteal = dlgEdit.m_uSteal;
		playerCurrent->m_uScore = dlgEdit.m_uScore;
		playerCurrent->m_uThreePointer = dlgEdit.m_uThreePointer;
	}

	Recalculate();
	UpdateAllViews(NULL);
}


void CLeagueDoc::OnDeletePlayer()
{
	CLeagueView* view = (CLeagueView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
	CGame* gameCurrent = view->m_pCurrentGame;

	UINT id = view->GetListCtrl().GetSelectionMark();
	POSITION pos = gameCurrent->m_listPlayer.GetHeadPosition();
	for (int i = 0; i < gameCurrent->m_listPlayer.GetSize(); i++) {
		if (i == id)
			break;
		gameCurrent->m_listPlayer.GetNext(pos);
	}
	gameCurrent->m_listPlayer.RemoveAt(pos);

	Recalculate();
	UpdateAllViews(NULL);
}


void CLeagueDoc::OnEditGame()
{
	CLeagueView* view = (CLeagueView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
	CList<CGame>* listGame = &view->GetDocument()->m_listGame;
	POSITION pos = listGame->GetHeadPosition();
	UINT i;
	for (i = 0; i != listGame->GetSize(); i++) {
		if (i == ((CMainFrame*)AfxGetMainWnd())->m_wndGameView.GetSelectedIndex())
			break;
		listGame->GetNext(pos);
	}
	CGame* currentGame = &listGame->GetAt(pos);

	CEditGameDlg dlgEdit;
	dlgEdit.SetInitialValue(DIALOG_EDIT, i + 1, currentGame->m_time);
	if (dlgEdit.DoModal() == IDOK) {
		currentGame->m_time = dlgEdit.m_time;
	}

	Recalculate();
	((CMainFrame*)AfxGetMainWnd())->m_wndGameView.UpdateView(&m_listGame);
	UpdateAllViews(NULL);
}


void CLeagueDoc::OnDeleteGame()
{
	CLeagueView* view = (CLeagueView *)(((CMainFrame*)AfxGetMainWnd())->GetActiveView());
	CList<CGame>* listGame = &view->GetDocument()->m_listGame;
	POSITION pos = listGame->GetHeadPosition();
	for (UINT i = 0; i != listGame->GetSize(); i++) {
		if (i == ((CMainFrame*)AfxGetMainWnd())->m_wndGameView.GetSelectedIndex())
			break;
		listGame->GetNext(pos);
	}
	listGame->RemoveAt(pos);

	Recalculate();
	((CMainFrame*)AfxGetMainWnd())->m_wndGameView.UpdateView(&m_listGame);
	view->ShowEmpty();
	UpdateAllViews(NULL);
}
