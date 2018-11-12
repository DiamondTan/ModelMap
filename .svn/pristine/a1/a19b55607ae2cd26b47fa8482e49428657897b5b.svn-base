
// MainFrm.h : CMainFrame 类的接口
//
#include "ModelMapView.h"
#include "OpenGL.h"
#include "DesignPlan.h"
#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CToolBar			m_viewToolBar;
	CReBar          m_ReBar;
private:
	CSplitterWnd* m_pWndSplitter;
//	CWinThread *ReadOBJThread;		//读取OBJ文件线程
//	CEvent threadStart;//定义全局变量
// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnLayout();
private:
	COpenGL* m_pOpenGL;
	CModelMapView* m_pMainView;
	CDesignPlan* m_pDesignPlan;
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateDrawtool(CCmdUI *pCmdUI);
	afx_msg void OnDrawtool();
};
//static UINT ThreadFunc(LPVOID lpParam);

