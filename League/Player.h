#pragma once
#include <afx.h>
class CPlayer : public CObject
{
	DECLARE_SERIAL(CPlayer)
	
public:
	CPlayer();
	CPlayer(const CString& strName, const CString strTeam, UINT uThreePointer,
		UINT uRebound, UINT uDrunk, UINT uSteal, UINT uScore, UINT uGame);

public:
	const CPlayer& operator=(const CPlayer& other);

public:
	CString m_strName;			// 姓名
	CString m_strTeam;			// 所属队名
	UINT  m_uThreePointer;		// 三分球个数
	UINT m_uRebound;			// 篮板球个数
	UINT m_uDrunk;				// 扣篮成功个数
	UINT m_uSteal;				// 抢断次数
	UINT m_uScore;				// 得分
	UINT m_uGame;				// 比赛场数
};

