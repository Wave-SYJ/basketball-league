#pragma once


// CEditPlayerDlg 对话框

class CPlayer;
class CEditPlayerDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEditPlayerDlg)

public:
	CEditPlayerDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEditPlayerDlg();

	void SetInitialValue(UINT uDlgType, UINT uIndex, const CPlayer* player = nullptr);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDIT_PLAYER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_uId;
	CString m_strName;
	CString m_strTeam;
	UINT m_uThreePointer;
	UINT m_uRebound;
	UINT m_uDrunk;
	UINT m_uSteal;
	UINT m_uScore;

private:
	UINT m_uDlgType;
};
