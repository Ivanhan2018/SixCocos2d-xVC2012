
// Cocos_Action_Editor_MFCDoc.h : CCocos_Action_Editor_MFCDoc ��Ľӿ�
//


#pragma once


class CCocos_Action_Editor_MFCDoc : public CDocument
{
protected: // �������л�����
	CCocos_Action_Editor_MFCDoc();
	DECLARE_DYNCREATE(CCocos_Action_Editor_MFCDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CCocos_Action_Editor_MFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
