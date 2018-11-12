#include "stdafx.h"
#include "MapData.h"
#include<stdexcept>
#include <exception>

CMapData* CMapData::m_pMapData = NULL;

cvPoint::cvPoint()
	:cx(0)
	,cy(0)
{

}
cvPoint::cvPoint(const int cx, const  int cy)
	: cx(cx)
	, cy(cy)
{

}
cvPoint::cvPoint(const CPoint& pt)
{
	this->cx = pt.x;
	this->cy = pt.y;
}
cvPoint::cvPoint(const cvPoint& m_pPoint)
{
	this->cx = m_pPoint.cx;
	this->cy = m_pPoint.cy;
}
cvPoint cvPoint::operator=(const cvPoint& m_pPoint)
{
	this->cx = m_pPoint.cx;
	this->cy = m_pPoint.cy;

	return *this;
}
cvPoint cvPoint::operator=(const CPoint& m_pPoint)
{
	this->cx = m_pPoint.x;
	this->cy = m_pPoint.y;

	return *this;
}
Line::Line()
{

}
Line::Line(const cvPoint BeginPoint, const cvPoint EndPoint)
	:BeginPoint(BeginPoint)
	, EndPoint(EndPoint)
{

}
Line::Line(const Line& line)
	:BeginPoint(line.BeginPoint)
	, EndPoint(line.EndPoint)
{

}
CMapData::CMapData()
{

}
CMapData::~CMapData()
{
	/*if (CMapData::m_pMapData)
		delete m_pMapData;*/
}
Line* CMapData::getAt(const int i)
{
	try{
		return this->data.at(i);
	}
	catch (std::out_of_range err)
	{
		//MessageBox(NULL,L"ERROR",(LPCWSTR)err.what(),MB_OK|MB_ICONERROR);
		MessageBox(NULL, L"ERROR", L"µØÖ·Ô½½ç", MB_OK | MB_ICONERROR);
	}
	return this->data.at(this->getSize() -1);
}
void CMapData::addPoint(const Line &data)
{
	
	this->data.Add(data);
}

int CMapData::getSize()
{
	return this->data.getSize();
}

CMapData* CMapData::GetInstance()
{
	if (CMapData::m_pMapData == NULL)
	{
		m_pMapData = new CMapData;
	}

	return m_pMapData;
}

void CMapData::DestoryInstance()
{
	if (CMapData::m_pMapData != NULL)
	{
		delete m_pMapData ;
	}

}