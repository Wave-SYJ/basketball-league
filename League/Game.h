#pragma once
#include <afx.h>
#include "Player.h"

class CGame : public CObject
{
	DECLARE_SERIAL(CGame)

public:
	CGame();
	CGame(const COleDateTime time);
	CGame(const CGame& other);

	COleDateTime m_time;
	CList<CPlayer> m_listPlayer;

public:
	const CGame& operator=(const CGame& other);
	virtual void Serialize(CArchive& ar);
};

