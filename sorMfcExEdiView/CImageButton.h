#pragma once


// CImageButton

class CImageButton : public CButton
{
	DECLARE_DYNAMIC(CImageButton)

public:
	CImageButton();
	virtual ~CImageButton();

	BOOL m_bHover;
	BOOL m_bTracking;
	UINT m_uImageID;

protected:
	DECLARE_MESSAGE_MAP()
public:
	void SetBtnImage(UINT uID);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);

	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

};


