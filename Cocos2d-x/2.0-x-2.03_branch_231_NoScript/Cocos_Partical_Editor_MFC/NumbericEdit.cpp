// NumbericEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "Cocos_Partical_Editor_MFC.h"
#include "NumbericEdit.h"


// CNumbericEdit

IMPLEMENT_DYNAMIC(CNumbericEdit, CEdit)

CNumbericEdit::CNumbericEdit()
{

}

CNumbericEdit::~CNumbericEdit()
{
}

void CNumbericEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar>=_T('0')&&nChar<=_T('9')||nChar==VK_BACK)
	{
		CEdit::OnChar(nChar,nRepCnt,nFlags);
	}
	else if(nChar=='.')
	{
		CString str;
		GetWindowText(str);
		if (!str.GetLength())
		{
			return;
		}
		if(str.Find(_T('.'),0)==-1)
			CEdit::OnChar(nChar,nRepCnt,nFlags);
	}
	else if(nChar=='-')
	{
		CString str;
		GetWindowText(str);
		if (str.GetLength())
		{
			return;
		}
		if(str.Find(_T('-'),0)==-1)
			CEdit::OnChar(nChar,nRepCnt,nFlags);
	}
}


BEGIN_MESSAGE_MAP(CNumbericEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()



// CNumbericEdit 消息处理程序


