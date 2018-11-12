
// ModelMapView.h : CModelMapView ��Ľӿ�
//
#include "ModelMapDoc.h"
#include "MapData.h"
#pragma once


class CModelMapView : public CView
{
protected: // �������л�����
	CModelMapView();
	DECLARE_DYNCREATE(CModelMapView)

// ����
public:
	CModelMapDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CModelMapView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
private:
	int cxClient;
	int cyClient;
	void DrawCoordinate(CDC *);
	int MM;
	int CM;
	bool m_bLButtonDown;		//����Ƿ���
	CPoint m_oldPoint;			//��һ�����λ��
	CPoint m_MousePoint;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
private:
	void draw(CDC *);
	void drawRect(CDC *,CPoint&,CPoint &);
public:
	afx_msg void OnChosePen();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CPtrArray m_ptrArray;
	UINT m_nDrawType;	//�滭����
	float k;		//��һ��ֱ�ߵ�б��
	cvPoint *m_pPoint;	//��һ��ֱ��
public:
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
private:
	//CPoint m_nNowpoint;
	CMapData* m_pMapData;
public:
	afx_msg void OnWall();
	afx_msg void OnEraser();
	afx_msg void OnCursor();
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // ModelMapView.cpp �еĵ��԰汾
inline CModelMapDoc* CModelMapView::GetDocument() const
   { return reinterpret_cast<CModelMapDoc*>(m_pDocument); }
#endif

