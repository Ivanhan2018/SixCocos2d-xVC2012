
#pragma once

/////////////////////////////////////////////////////////////////////////////
// CViewTree ����

class CViewTree : public CTreeCtrl
{
// ����
public:
	CViewTree();

// ��д
protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// ʵ��
public:
	virtual ~CViewTree();

protected:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	DECLARE_MESSAGE_MAP()
};
