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
	CString m_strName;			// ����
	CString m_strTeam;			// ��������
	UINT  m_uThreePointer;		// ���������
	UINT m_uRebound;			// ���������
	UINT m_uDrunk;				// �����ɹ�����
	UINT m_uSteal;				// ���ϴ���
	UINT m_uScore;				// �÷�
	UINT m_uGame;				// ��������
};

