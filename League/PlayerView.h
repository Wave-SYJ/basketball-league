﻿
#pragma once

#include "ViewList.h"

class CPlayer;

class CPlayerToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPlayerView : public CDockablePane
{
public:
	CPlayerView() noexcept;
	virtual ~CPlayerView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	void UpdateView(const CMap<CString, LPCTSTR, CPlayer, CPlayer&>& map);

protected:
	CPlayerToolBar m_wndToolBar;
	CViewList m_wndPlayerView;
	CImageList m_PlayerViewImages;
	UINT m_nCurrSort;

// 重写
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

