
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
END_MESSAGE_MAP()

// CLeagueView 构造/析构

CLeagueView::CLeagueView() noexcept
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
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
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
