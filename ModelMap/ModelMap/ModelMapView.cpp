// ModelMapView.cpp : CModelMapView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ModelMap.h"
#endif

#include "ModelMapDoc.h"
#include "ModelMapView.h"
#include <cmath>
#include "Graph.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define SCREEN_REDRAW 1



// CModelMapView

IMPLEMENT_DYNCREATE(CModelMapView, CView)

BEGIN_MESSAGE_MAP(CModelMapView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_32772, &CModelMapView::OnChosePen)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(IDM_LINE, &CModelMapView::OnLine)
	ON_COMMAND(IDM_RECTANGLE, &CModelMapView::OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, &CModelMapView::OnEllipse)
	ON_COMMAND(IDM_WALL, &CModelMapView::OnWall)
	ON_COMMAND(IDM_ERASER, &CModelMapView::OnEraser)
	ON_COMMAND(IDM_CURSOR, &CModelMapView::OnCursor)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CModelMapView ����/����

CModelMapView::CModelMapView()
	:MM(5)
	, CM(MM*10)
	, m_bLButtonDown(false)
{
	// TODO:  �ڴ˴����ӹ������

	m_nDrawType = DRAW_CURSOR;
}

CModelMapView::~CModelMapView()
{
}

BOOL CModelMapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CModelMapView ����

void CModelMapView::OnDraw(CDC* pDC)
{
	CModelMapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ�����������ӻ��ƴ���
	DrawCoordinate(pDC);

		if (m_bLButtonDown)
		{
			
			CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
			CBrush *pOldBrushdc=pDC->SelectObject(pBrush);
			switch (m_nDrawType)
			{
			case ERASER:
				//pDC->SetPixel(m_oldPoint, RGB(255, 0, 0));
				break;
			case DRAW_LINE:
				pDC->MoveTo(m_oldPoint);
				pDC->LineTo(m_MousePoint);
				break;
			case DRAW_RECT:
				pDC->Rectangle(CRect(m_oldPoint, m_MousePoint));
				break;
			case DRAW_ELLIPSE:
				pDC->Ellipse(CRect(m_oldPoint, m_MousePoint));
				break;
			case DRAW_WALL:
				this->drawRect(pDC, this->m_oldPoint, this->m_MousePoint);
				break;
			default:
				break;
			}
			pDC->SelectObject(pOldBrushdc);
		}
	
	draw(pDC);
	/*****************************************************************************/
	

}
void CModelMapView::drawRect(CDC *pDC, CPoint& BeginPoint, CPoint &EndPoint)
{
	int bx = BeginPoint.x, by = BeginPoint.y;
	int zx = EndPoint.x, zy = EndPoint.y;
	int step = 4;	//��������
	
	if (abs(static_cast<double>(zy - by) / (zx - bx)) < 1){		/*��tan a<1������*/
				pDC->MoveTo(bx , by + step);
				pDC->LineTo(zx , by + step);
				pDC->MoveTo(bx , by - step);
				pDC->LineTo(zx , by - step);

				pDC->MoveTo(bx , by + step);
				pDC->LineTo(bx , by - step);
				pDC->MoveTo(zx , by + step);
				pDC->LineTo(zx , by - step);
	}
	else
	{
				pDC->MoveTo(bx - step, by );
				pDC->LineTo(bx - step, zy );
				pDC->MoveTo(bx + step, by );
				pDC->LineTo(bx + step, zy );

				pDC->MoveTo(bx - step, by );
				pDC->LineTo(bx + step, by );
				pDC->MoveTo(bx - step, zy );
				pDC->LineTo(bx + step, zy );
	}
	
}
void CModelMapView::draw(CDC* pDC)
{
	
	for (int i = 0; i < m_pMapData->getSize(); i++)
	{
		Line *p_line = m_pMapData->getAt(i);
			/*pDC->Rectangle(p_line.BeginPoint.cx, p_line.BeginPoint.cy,
				p_line.EndPoint.cx, p_line.EndPoint.cy);*/

		this->drawRect(pDC, CPoint(p_line->BeginPoint.cx, p_line->BeginPoint.cy),
			CPoint(p_line->EndPoint.cx, p_line->EndPoint.cy));
	}

	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	pDC->SelectObject(pBrush);
	for (int i = 0; i < m_ptrArray.GetSize(); i++)
	{
		switch (((CGraph*)m_ptrArray.GetAt(i))->m_nDrawType)
		{
		case DRAW_LINE:
			pDC->MoveTo(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrigin);
			pDC->LineTo(((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd);
			break;
		case DRAW_RECT:
			pDC->Rectangle(CRect(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrigin,
				((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		case DRAW_ELLIPSE:
			pDC->Ellipse(CRect(((CGraph*)m_ptrArray.GetAt(i))->m_ptOrigin,
				((CGraph*)m_ptrArray.GetAt(i))->m_ptEnd));
			break;
		default:
			break;
		}
	}
}

void CModelMapView::DrawCoordinate(CDC *pDC)
{

	int cx = static_cast<int> (this->cxClient / 2);	//����һ�볤
	int cy = static_cast<int> (this->cyClient / 2);	//����һ���
	pDC->SetViewportOrg(cx, cy);		//������ԭ������Ϊ����
	/*ʮ������*/
	pDC->MoveTo(-cx, 0);			
	pDC->LineTo(cx, 0);
	pDC->MoveTo(0, -cy);
	pDC->LineTo(0, cy);

	for (int x = 0; x <= static_cast<int>(cx*0.9); x += MM)
	{
		if (x % CM == 0)				//ģ50����0
		{
			pDC->MoveTo(x, 0);
			pDC->LineTo(x, -10);		//10����λ��һ������
			continue;
		}
		pDC->MoveTo(x, 0);
		pDC->LineTo(x, -5);			//1����λ��һ������
	}

	

	for (int x = 0; x >= static_cast<int>(-cx*0.9); x -= MM)		//static_cast<int>(-cx*0.9);�������߽���
	{
		if (x % CM == 0)
		{
			pDC->MoveTo(x, 0);
			pDC->LineTo(x, -10);
			continue;
		}
		pDC->MoveTo(x, 0);
		pDC->LineTo(x, -5);
	}
	/*x���ͷ*/
	pDC->MoveTo(cx - 10, -5);
	pDC->LineTo(cx, 0);
	pDC->MoveTo(cx - 10, 5);
	pDC->LineTo(cx, 0);

	for (int x = 0; x <= static_cast<int>(cy*0.9); x += MM)
	{
		if (x % CM == 0)
		{
			pDC->MoveTo(0, x);
			pDC->LineTo(10, x);
			continue;
		}
		pDC->MoveTo(0, x);
		pDC->LineTo(5, x);
	}
	for (int x = 0; x >= static_cast<int>(-cy*0.9); x -= MM)
	{
		if (x % CM == 0)
		{
			pDC->MoveTo(0, x);
			pDC->LineTo(10, x);
			continue;
		}
		pDC->MoveTo(0, x);
		pDC->LineTo(5, x);
	}
	/*y���ͷ*/
	pDC->MoveTo(5, -cy + 10);
	pDC->LineTo(0, -cy);
	pDC->MoveTo(-5, -cy + 10);
	pDC->LineTo(0, -cy);
}

// CModelMapView ��ӡ

BOOL CModelMapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CModelMapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ���Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CModelMapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ���Ӵ�ӡ����е���������
}


// CModelMapView ���

#ifdef _DEBUG
void CModelMapView::AssertValid() const
{
	CView::AssertValid();
}

void CModelMapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CModelMapDoc* CModelMapView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModelMapDoc)));
	return (CModelMapDoc*)m_pDocument;
}
#endif //_DEBUG


// CModelMapView ��Ϣ��������


void CModelMapView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴�������Ϣ�����������

	this->cxClient = cx;			//���ڵĳ�
	this->cyClient = cy;			//���ڵĿ�

}


void CModelMapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	point.x -= this->cxClient / 2;
	point.y -= this->cyClient / 2;

	m_oldPoint = point;
	//m_MousePoint = point;

	//this->m_pPoint = NULL;
	//for (int i = 0; i < m_pMapData->getSize(); i++)
	//{
	//	Line *p_line = m_pMapData->getAt(i);
	//	cvPoint  BeginPoint = p_line->BeginPoint;
	//	cvPoint	 EndPoint = p_line->EndPoint;
	//	int bx = BeginPoint.cx, by = BeginPoint.cy;			/*�Ѿ��洢����������*/
	//	int zx = EndPoint.cx, zy = EndPoint.cy;			/*�Ѿ��洢����յ�����*/
	//	int m_movex = bx - m_oldPoint.x;				/*�Ƿ��ཻ*/
	//	int m_movey = by - m_oldPoint.y; 
	//	/*��������㲿���ཻ*/
	//	if (m_movex < 5 && m_movex>-5 && m_movey < 5 && m_oldPoint.y>by && m_oldPoint.y<zy && m_oldPoint.x<m_MousePoint.x && m_MousePoint.y==m_oldPoint.y){
	//		m_oldPoint.x = bx+5;
	//		k = zy - by;
	//	}
	//	/*�������յ��ཻ*/
	//	if (m_movex < 5 && m_movex>-5 && m_movey < 5 && m_oldPoint.y>by && m_oldPoint.y<zy && m_oldPoint.x>m_MousePoint.x && m_MousePoint.y == m_oldPoint.y)
	//	{
	//		m_oldPoint.x = bx - 5;
	//		k = zy - by;
	//	}
	//	/*���ϵ�����㲿���ཻ*/
	//	if (m_movey<5 && m_movey>-5 && m_oldPoint.x>bx && m_oldPoint.x < zx && m_MousePoint.x == m_oldPoint.x){
	//		m_oldPoint.y = by + 5;
	//		k = zy - by;
	//	}
	//	
	//	//if (m_oldPoint.x < bx + 5 && m_oldPoint.x >bx - 5 && m_oldPoint.y < by + 5 && m_oldPoint.y > by + 5)
	//	//{
	//	//	this->m_pPoint = &(p_line->BeginPoint);
	//	//	k = zy - by;
	//	//	/*k = abs(static_cast<double>(zy - by) / (zx - bx));*/
	//	//}
	//	//else if (m_oldPoint.x < zx + 5 && m_oldPoint.x >zx - 5 && m_oldPoint.y < zy + 5 && m_oldPoint.y > zy + 5)
	//	//{
	//	//	this->m_pPoint = &(p_line->EndPoint);
	//	//	k = zy - by;
	//	//}
	//}
	m_bLButtonDown = true;

	CView::OnLButtonDown(nFlags, point);
}


void CModelMapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	

	//m_MousePoint.x -= this->cxClient / 2;
	//m_MousePoint.y -= this->cyClient / 2;
	
	m_bLButtonDown = false;


	if (this->m_nDrawType == DRAW_WALL)
	{
		Line temp;
		temp.BeginPoint.cx = m_oldPoint.x ;
		temp.BeginPoint.cy = m_oldPoint.y ;
		temp.EndPoint.cx = m_MousePoint.x;
		temp.EndPoint.cy = m_MousePoint.y;
		m_pMapData->addPoint(temp);
	}
	else
	{
		CGraph * pGraph = new CGraph(m_nDrawType, m_oldPoint, m_MousePoint);
		m_ptrArray.Add(pGraph);
	}
	
	CView::OnLButtonUp(nFlags, point);
}


void CModelMapView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ
	point.x -= this->cxClient / 2;
	point.y -= this->cyClient / 2;
	
	m_MousePoint = point;

	this->m_pPoint = NULL;
	for (int i = 0; i < m_pMapData->getSize(); i++)
	{
		Line *p_line = m_pMapData->getAt(i);
		cvPoint  BeginPoint = p_line->BeginPoint;
		cvPoint	 EndPoint = p_line->EndPoint;
		int bx = BeginPoint.cx, by = BeginPoint.cy;			/*�Ѿ��洢����������*/
		int zx = EndPoint.cx, zy = EndPoint.cy;			/*�Ѿ��洢����յ�����*/
		int m_bmovex = abs(bx) - abs(m_oldPoint.x);				/*�Ƿ��ཻ*/
		int m_bmovey = abs(by) - abs(m_oldPoint.y);
		int m_emovex = abs(zx) - abs(m_oldPoint.x);
		int m_emovey = abs(zy) - abs(m_oldPoint.y);
		/*��㲿���ཻ*/
		if (m_bmovex < 5 && m_bmovex>-5 && ((m_oldPoint.y>by && m_oldPoint.y<zy )|| (m_oldPoint.y<by && m_oldPoint.y>zy)) && m_MousePoint.y == m_oldPoint.y){
			if (m_oldPoint.x<m_MousePoint.x)
				m_oldPoint.x = bx + 5;
			else
				m_oldPoint.x = bx - 5;
			k = zy - by;
		}
		/*���ϵ�����㲿���ཻ*/
		if (m_bmovey<5 && m_bmovey>-5 &&( (m_oldPoint.x>bx && m_oldPoint.x < zx) || (m_oldPoint.x<bx && m_oldPoint.x > zx) )&& m_MousePoint.x == m_oldPoint.x){
			if (m_oldPoint.y<m_MousePoint.y)
				m_oldPoint.y = by + 5;
			else
				m_oldPoint.y = by - 5;
			k = zy - by;
		}

		//if (m_oldPoint.x < bx + 5 && m_oldPoint.x >bx - 5 && m_oldPoint.y < by + 5 && m_oldPoint.y > by + 5)
		//{
		//	this->m_pPoint = &(p_line->BeginPoint);
		//	k = zy - by;
		//	/*k = abs(static_cast<double>(zy - by) / (zx - bx));*/
		//}
		//else if (m_oldPoint.x < zx + 5 && m_oldPoint.x >zx - 5 && m_oldPoint.y < zy + 5 && m_oldPoint.y > zy + 5)
		//{
		//	this->m_pPoint = &(p_line->EndPoint);
		//	k = zy - by;
		//}
	}

	if (m_bLButtonDown)
	{
		m_MousePoint = point;
		if (m_nDrawType == DRAW_WALL){
			int bx = m_oldPoint.x, by = m_oldPoint.y;
			int zx = point.x, zy = point.y;
			float k = abs(static_cast<double>(zy - by) / (zx - bx));
			if (k < 1){		/*��tan a<1������*/
				m_MousePoint.y = m_oldPoint.y;
				if (this->m_pPoint)
				{
					if (k != this->k)
					{
						if (zy>by)
						{
							m_oldPoint.y = m_pPoint->cy;
							m_oldPoint.x = m_pPoint->cx+5;
						}
						else
						{
							m_oldPoint.y = m_pPoint->cy;
							m_oldPoint.x = m_pPoint->cx - 5;
						}
					}
				}
			}
			else
			{
				m_MousePoint.x = m_oldPoint.x;
				if (this->m_pPoint)
				{
					if (k != this->k)
					{
						if (zx>bx)
						{
							m_oldPoint.y = m_pPoint->cy+5;
							m_oldPoint.x = m_pPoint->cx ;
						}
						else
						{
							m_oldPoint.y = m_pPoint->cy-5;
							m_oldPoint.x = m_pPoint->cx;
						}
					}
				}
			}
		}
	
	}

	CView::OnMouseMove(nFlags, point);
}


BOOL CModelMapView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CModelMapView::OnChosePen()
{
	// TODO:  �ڴ�����������������
}


void CModelMapView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (m_bLButtonDown){
		Invalidate();
	}

	CView::OnTimer(nIDEvent);
}


int CModelMapView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ�������ר�õĴ�������

	SetTimer(SCREEN_REDRAW, 10, NULL);

	m_pMapData = CMapData::GetInstance();

	return 0;
}

void CModelMapView::OnLine()
{
	// TODO:  �ڴ�����������������
	m_nDrawType = DRAW_LINE;
	
}


void CModelMapView::OnRectangle()
{
	// TODO:  �ڴ�����������������
	m_nDrawType = DRAW_RECT;
	
}


void CModelMapView::OnEllipse()
{
	// TODO:  �ڴ�����������������
	m_nDrawType = DRAW_ELLIPSE;
	
}



void CModelMapView::OnWall()
{
	// TODO:  �ڴ�����������������
	this->m_nDrawType = DRAW_WALL;
}


void CModelMapView::OnEraser()
{
	// TODO:  �ڴ�����������������
	this->m_nDrawType = ERASER;
}


void CModelMapView::OnCursor()
{
	// TODO:  �ڴ�����������������
	this->m_nDrawType = DRAW_CURSOR;
}


void CModelMapView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  �ڴ˴�������Ϣ�����������

	KillTimer(SCREEN_REDRAW);
}