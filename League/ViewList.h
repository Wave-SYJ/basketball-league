
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree 窗口

class CViewList : public CListCtrl
{
// 构造
public:
	CViewList() noexcept;

// 重写
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// 实现
public:
	virtual ~CViewList();

protected:
	DECLARE_MESSAGE_MAP()
};
