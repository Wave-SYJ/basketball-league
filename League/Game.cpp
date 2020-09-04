#include "pch.h"
#include "Game.h"

IMPLEMENT_SERIAL(CGame, CObject, 0)

CGame::CGame()
{
}

CGame::CGame(const COleDateTime time) : m_time(time)
{
}

CGame::CGame(const CGame & other)
	: m_time(other.m_time)
{
	POSITION pos = other.m_listPlayer.GetHeadPosition();
	while (pos != NULL) {
		m_listPlayer.AddTail(other.m_listPlayer.GetNext(pos));
	}
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


void CGame::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);

	if (ar.IsStoring())
	{
		ar << m_time.Format(VAR_DATEVALUEONLY);

		ar << m_listPlayer.GetSize();
		POSITION pos = m_listPlayer.GetHeadPosition();
		while (pos) {
			CPlayer* player = &m_listPlayer.GetNext(pos);
			player->Serialize(ar);
		}
	}
	else
	{
		CString strTime;
		ar >> strTime;
		m_time.ParseDateTime(strTime);

		UINT uListSize;
		ar >> uListSize;
		for (UINT i = 0; i < uListSize; i++) {
			CPlayer player;
			player.Serialize(ar);
			m_listPlayer.AddTail(player);
		}
	}
}
