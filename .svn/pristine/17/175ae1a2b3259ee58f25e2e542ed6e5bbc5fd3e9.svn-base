
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "ModelMap.h"

#include "MainFrm.h"
#include "OpenGL.h"
#include "MapData.h"
#include "OBJManager.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame


IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_LAYOUT, &CMainFrame::OnLayout)
	ON_WM_SHOWWINDOW()
	ON_UPDATE_COMMAND_UI(IDM_DRAWTOOL, &CMainFrame::OnUpdateDrawtool)
	ON_COMMAND(IDM_DRAWTOOL, &CMainFrame::OnDrawtool)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CLOCK,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
//:ReadOBJThread(NULL)
{
	// TODO:  在此添加成员初始化代码
	CMapData::GetInstance();
	COBJManager::GetInstance();
}

CMainFrame::~CMainFrame()
{
	CMapData::DestoryInstance();
	COBJManager::DestoryInstance();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	SetTimer(1, 1000, NULL);

	if (!m_viewToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_viewToolBar.LoadToolBar(IDR_VIEW_TOOLBAR1))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}
	m_viewToolBar.EnableDocking(CBRS_ALIGN_ANY);//可以停靠在任何位置
	DockControlBar(&m_viewToolBar);
	

	this->m_pWndSplitter = NULL;

//	ReadOBJThread = AfxBeginThread(ThreadFunc, &threadStart);
	

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}
 
// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类

	//创建一个静态分栏窗口，分为一行两列

	if (m_pMainView == NULL)
	{
		m_pMainView = (CModelMapView *)CreateView(pContext, AFX_IDW_PANE_FIRST + 1);
	}

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CTime time;

	time = CTime::GetCurrentTime();

	CString s = time.Format("%H:%M:%S");
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_CLOCK), s);



	CFrameWnd::OnTimer(nIDEvent);
}


void CMainFrame::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	KillTimer(1);
	if (m_pWndSplitter != NULL)
	{
		delete m_pWndSplitter;
	}
	CFrameWnd::OnClose();
}


void CMainFrame::OnLayout()
{
	// TODO:  在此添加命令处理程序代码
	CRect rt;
	GetClientRect(&rt);

	if (m_pWndSplitter != NULL && ::IsWindow(m_pWndSplitter->m_hWnd))
	{
		
		m_pMainView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
		RecalcLayout();
		m_pMainView->MoveWindow(rt);
		m_pMainView->ShowWindow(SW_SHOW );

		if (m_pWndSplitter != NULL)
		{
			m_pWndSplitter->DestroyWindow();
			delete m_pWndSplitter;
			m_pWndSplitter = NULL;
		}
		ShowControlBar(&m_viewToolBar, !m_viewToolBar.IsWindowVisible(), TRUE);
	//	
	}
	else {
		if (m_pWndSplitter != NULL)
		{
			delete m_pWndSplitter;
		}

		m_pWndSplitter = new CSplitterWnd;
		CCreateContext Context;
		ZeroMemory(&Context, sizeof(Context));
		Context.m_pCurrentFrame = this;
		// set doc
		CDocument *pDoc = m_pMainView->GetDocument();
		Context.m_pCurrentDoc = pDoc;
		Context.m_pNewDocTemplate = pDoc->GetDocTemplate();

		m_pMainView->SetDlgCtrlID(AFX_IDW_PANE_FIRST + 1);
		m_pMainView->ShowWindow(SW_HIDE);

		if (::IsWindow(m_pWndSplitter->m_hWnd))
			m_pWndSplitter->DestroyWindow();
	
		if (m_pWndSplitter->CreateStatic(this, 1, 2) == NULL)
		{
			AfxMessageBox(L"CreateStatic failed!");
			return;
		}


		
		int nWidth = rt.Width();

		if (!m_pWndSplitter->CreateView(0, 0, RUNTIME_CLASS(CDesignPlan), CSize(0, 0), &Context))
		{
			m_pWndSplitter->DestroyWindow();
			return;
		}

		if (m_pWndSplitter->CreateView(0, 1, RUNTIME_CLASS(COpenGL), CSize(0, 0), &Context) == 0)
		{
			m_pWndSplitter->DestroyWindow();
			return;
		}

		m_pDesignPlan = static_cast<CDesignPlan*>(m_pWndSplitter->GetPane(0, 1));
		m_pOpenGL = static_cast<COpenGL*>(m_pWndSplitter->GetPane(0, 1));

		m_pWndSplitter->SetColumnInfo(0, nWidth *0.2, 0);
		m_pWndSplitter->SetColumnInfo(1, nWidth *0.8, 1);

		SetActiveView((CView*)m_pOpenGL);

		

		ShowControlBar(&m_viewToolBar, !m_viewToolBar.IsWindowVisible(), FALSE);

	//	RecalcLayout();
	}

	RecalcLayout();

	InitialUpdateFrame(NULL, TRUE);

}


void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFrameWnd::OnShowWindow(bShow, nStatus);

	// TODO:  在此处添加消息处理程序代码
	m_pMainView = (CModelMapView *)GetActiveView();
}


void CMainFrame::OnUpdateDrawtool(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(m_viewToolBar.IsWindowVisible());
}


void CMainFrame::OnDrawtool()
{
	// TODO:  在此添加命令处理程序代码
	ShowControlBar(&m_viewToolBar, !m_viewToolBar.IsWindowVisible(), FALSE);
}
//static UINT ThreadFunc(LPVOID lpParam)
//{
//	CEvent *threadStart = (CEvent *)lpParam;
//
//	COBJManager* m_pOBJManager = COBJManager::GetInstance();
//
//	char filename[1024];
//	for (int i = 0; i < 6; i++)
//	{
//		sprintf(filename, "data/obj/sofa/sofa%d.obj",i+1);
//		m_pOBJManager->addOBJ(COBJ(filename, 0));
//	}
//	
//
//
//	//while (true){
//
//		//::WaitForSingleObject(threadStart->m_hObject, INFINITE);//无限时间阻塞当前线程
//	//}
//	
////	threadStart->SetEvent();//在另一个线程结束时调用，即可取消上一线程的阻塞
//
//	return true;
//}