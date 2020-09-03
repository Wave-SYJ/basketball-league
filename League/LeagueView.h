
// LeagueView.h: CLeagueView 类的接口
//

#pragma once
#include "Player.h"

class CLeagueDoc;
class CGame;
class CLeagueView : public CListView
{
protected: // 仅从序列化创建
	CLeagueView() noexcept;
	DECLARE_DYNCREATE(CLeagueView)

// 特性
public:
	CLeagueDoc* GetDocument() const;

private:
	UINT m_uStatus;
public:
	CGame* m_pCurrentGame;
	CPlayer m_currentPlayer;

// 操作
public:
	void ShowGame(int index);
	void ShowPlayer(const CString& strName);
	void ShowEmpty();

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CLeagueView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	afx_msg void OnUpdateInsertPlayer(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditPlayer(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeletePlayer(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditGame(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDeleteGame(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // LeagueView.cpp 中的调试版本
inline CLeagueDoc* CLeagueView::GetDocument() const
   { return reinterpret_cast<CLeagueDoc*>(m_pDocument); }
#endif

