#pragma once
#include "stdafx.h"
#include "MyList.h"

struct cvPoint
{
	cvPoint();
	cvPoint(const int, const  int);
	cvPoint(const cvPoint &);
	cvPoint(const CPoint&);
	cvPoint operator = (const cvPoint &);
	cvPoint operator = (const CPoint &);
	int cx;
	int cy;
};

struct Line
{
	Line();
	Line(const cvPoint, const cvPoint);
	Line(const Line &);

	cvPoint BeginPoint;
	cvPoint EndPoint;
};



class CMapData
{
public:
	static CMapData*GetInstance();
	static void DestoryInstance();
	virtual ~CMapData();
	Line* getAt(const int i);
//	mdPoint* at(const int i);
	void addPoint(const Line&);
//	void addPoint(const mdPoint&);
//	void addPoint(const CPoint&);
	int getSize();
private:
	CMapData();
	static CMapData* m_pMapData;
	MyList<Line> data;
//	MyList<mdPoint> mdata;
};



