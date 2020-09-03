
#pragma once

#include "ViewList.h"


class CGameViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CGame;
class CGameView : public CDockablePane
{
// 构造
public:
	CGameView() noexcept;

	void AdjustLayout();
	void OnChangeVisualStyle();

public:
	void UpdateView(CList<CGame> * pList);
	UINT GetSelectedIndex();

// 特性
protected:

	CViewList m_wndGameView;
	CImageList m_GameViewImages;
	CGameViewToolBar m_wndToolBar;

// 实现
public:
	virtual ~CGameView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

