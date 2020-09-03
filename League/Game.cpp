#include "pch.h"
#include "Game.h"

IMPLEMENT_SERIAL(CGame, CObject, 0)

CGame::CGame()
{
}

CGame::CGame(const COleDateTime time) : m_time(time)
{
}

const CGame & CGame::operator=(const CGame & other)
{
	if (this != &other) {
		m_time = other.m_time;

		POSITION pos = other.m_listPlayer.GetHeadPosition();
		while (pos != NULL) {
			m_listPlayer.AddTail(other.m_listPlayer.GetNext(pos));
		}
	}

	return *this;
}
