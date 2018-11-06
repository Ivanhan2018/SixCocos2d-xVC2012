#pragma once


// CNumbericEdit

class CNumbericEdit : public CEdit
{
	DECLARE_DYNAMIC(CNumbericEdit)

public:
	CNumbericEdit();
	virtual ~CNumbericEdit();

private:
	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	DECLARE_MESSAGE_MAP()
};


