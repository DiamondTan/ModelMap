#pragma once

#define DRAW_CURSOR	0
#define DRAW_DOT		1
#define DRAW_LINE		2
#define DRAW_RECT		3
#define DRAW_ELLIPSE	4
#define DRAW_WALL		5
#define ERASER		6

class CGraph
{
public:
	CGraph(UINT m_nDrawType, CPoint m_ptOrigin, CPoint m_ptEnd);
	~CGraph();
	CPoint m_ptOrigin;		//���
	CPoint m_ptEnd;			//�յ�
	UINT m_nDrawType;		//��ͼ����
};

