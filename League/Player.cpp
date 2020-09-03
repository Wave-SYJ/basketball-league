#include "pch.h"
#include "Player.h"

IMPLEMENT_SERIAL(CPlayer, CObject, 0)


CPlayer::CPlayer() : m_strName(_T("")), m_strTeam(_T("")), m_uThreePointer(0),
	m_uRebound(0), m_uDrunk(0), m_uSteal(0), m_uScore(0), m_uGame(0)
{
}

CPlayer::CPlayer(const CPlayer & other)
	: m_strName(other.m_strName), m_strTeam(other.m_strTeam), m_uThreePointer(other.m_uThreePointer),
	m_uRebound(other.m_uRebound), m_uDrunk(other.m_uDrunk), m_uSteal(other.m_uSteal), m_uScore(other.m_uScore), m_uGame(other.m_uGame)
{
}

CPlayer::CPlayer(const CString & strName, const CString strTeam,
	UINT uThreePointer, UINT uRebound, UINT uDrunk, UINT uSteal, UINT uScore, UINT uGame)
	: m_strName(strName), m_strTeam(strTeam), m_uThreePointer(uThreePointer),
	m_uRebound(uRebound), m_uDrunk(uDrunk), m_uSteal(uSteal), m_uScore(uScore), m_uGame(uGame)
{
}

const CPlayer & CPlayer::operator=(const CPlayer & other)
{
	if (&other == this)
		return *this;

	m_uThreePointer = other.m_uThreePointer;
	m_uRebound = other.m_uRebound;
	m_uDrunk = other.m_uDrunk;
	m_uSteal = other.m_uSteal;
	m_uScore = other.m_uScore;
	m_uGame = other.m_uGame;
	m_strName = other.m_strName;
	m_strTeam = other.m_strTeam;

	return *this;
}


void CPlayer::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{	
		ar << m_strName << m_strTeam
			<< m_uThreePointer << m_uRebound
			<< m_uDrunk << m_uSteal
			<< m_uScore << m_uGame;
	}
	else
	{	
		ar >> m_strName >> m_strTeam
			>> m_uThreePointer >> m_uRebound
			>> m_uDrunk >> m_uSteal
			>> m_uScore >> m_uGame;
	}
	
}
