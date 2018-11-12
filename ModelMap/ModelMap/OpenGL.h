#pragma once
#include <GL\glut.h>
#include "Texture.h"
#include "Camera.h"
#include "afxwin.h"
#include "MapData.h"
#include "OBJManager.h"
#include <vector>
// COpenGL 窗体视图

class COpenGL : public CFormView
{
	DECLARE_DYNCREATE(COpenGL)

protected:
	COpenGL();           // 动态创建所使用的受保护的构造函数
	virtual ~COpenGL();

public:
	enum { IDD = IDD_FORMVIEW_OPENGL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

private:
	void pick(int, int);
	void processHits(GLint hits, GLuint buffer[]);
	Vector3 screenToWorld(int x, int y);
	bool  SetupPixelFormat();
	bool Init();
	bool loadTexture();
	bool InitializeOpenGL();
	void DrawScene();
	void DrawShow();
	void DrawTargets();
	void UpdateCamera();
	void DrawColorBox(void);
	HGLRC m_hRC;   //Rendering Context着色描述表
	CClientDC* m_pDC;    //Device Context设备描述表
private:
	bool m_rLButtonDown;		//右键是否按下
	int CxClient;
	int CyClient;
	int list;
	void InitList();
	int AxisList;
	int GroundList;
	void InitAxis();
	void DrawAxis();
	void InitGround();
	void DrawGround();
	void InitData();
	void drawData();
	void drawRect(cvPoint&, cvPoint&);
	CCamera      m_Camera;
	CMapData* m_pMapData;
	COBJManager* m_pOBJManager;
	CTexture m_texture ;
	bool m_OBJdraw;//添加的OBJ
	bool m_bcikOBJ;	//点击的OBJ
	int value;	//点击OBJ的索引值
	
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};


