
// LeagueDoc.cpp: CLeagueDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "League.h"
#endif

#include "LeagueDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLeagueDoc

IMPLEMENT_DYNCREATE(CLeagueDoc, CDocument)

BEGIN_MESSAGE_MAP(CLeagueDoc, CDocument)
	ON_COMMAND(ID_32771, &CLeagueDoc::OnInsertGame)
END_MESSAGE_MAP()


// CLeagueDoc 构造/析构

CLeagueDoc::CLeagueDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CLeagueDoc::~CLeagueDoc()
{
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
	/*if (ar.IsStoring())
	{
		m_listPlayer.Serialize(ar);
		m_listGame.Serialize(ar);
	}
	else
	{
		m_listPlayer.Serialize(ar);
		m_listGame.Serialize(ar);
	}*/

	m_listGame.Serialize(ar);
	m_listPlayer.Serialize(ar);
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
	CEditDlg dlgEdit;
	dlgEdit.SetInitialValue(DIALOG_INSERT, m_listGame.GetSize() + 1, COleDateTime::GetCurrentTime());
	if (dlgEdit.DoModal() == IDOK) {
		m_listGame.AddTail(CGame(dlgEdit.m_time));
	}
}
