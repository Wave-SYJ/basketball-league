
// LeagueDoc.h: CLeagueDoc 类的接口
//


#pragma once
#include "Game.h"
#include "EditGameDlg.h"

class CLeagueDoc : public CDocument
{
protected: // 仅从序列化创建
	CLeagueDoc() noexcept;
	DECLARE_DYNCREATE(CLeagueDoc)

// 特性
public:
	// 存储每场球赛
	CList<CGame> m_listGame;
	// 存储个人汇总
	CMap<CString, LPCTSTR, CPlayer, CPlayer&> m_mapPlayer;

public:
	void Recalculate();

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CLeagueDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnInsertGame();
	afx_msg void OnInsertPlayer();
	afx_msg void OnEditPlayer();
	afx_msg void OnDeletePlayer();
	afx_msg void OnEditGame();
	afx_msg void OnDeleteGame();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
