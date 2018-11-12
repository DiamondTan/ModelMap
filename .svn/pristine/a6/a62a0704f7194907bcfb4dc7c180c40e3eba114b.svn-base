
// ModelMapView.h : CModelMapView 类的接口
//
#include "ModelMapDoc.h"
#include "MapData.h"
#pragma once


class CModelMapView : public CView
{
protected: // 仅从序列化创建
	CModelMapView();
	DECLARE_DYNCREATE(CModelMapView)

// 特性
public:
	CModelMapDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
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
	bool m_bLButtonDown;		//左键是否按下
	CPoint m_oldPoint;			//上一次鼠标位置
	CPoint m_MousePoint;
// 生成的消息映射函数
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
	UINT m_nDrawType;	//绘画类型
	float k;		//上一条直线的斜率
	cvPoint *m_pPoint;	//上一条直线
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

#ifndef _DEBUG  // ModelMapView.cpp 中的调试版本
inline CModelMapDoc* CModelMapView::GetDocument() const
   { return reinterpret_cast<CModelMapDoc*>(m_pDocument); }
#endif

