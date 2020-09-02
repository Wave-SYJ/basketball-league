#pragma once
#include <afx.h>
#include "Player.h"

class CGame : public CObject
{
	DECLARE_SERIAL(CGame)

public:
	CTime m_time;
	CList<CPlayer> m_listPlayer;

public:
	const CGame& operator=(const CGame& other);
};

