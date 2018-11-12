#pragma once
#include "OBJManager.h"
#include "afxcmn.h"

// CDesignPlan 窗体视图

class CDesignPlan : public CFormView
{
	DECLARE_DYNCREATE(CDesignPlan)

protected:
	CDesignPlan();           // 动态创建所使用的受保护的构造函数
	virtual ~CDesignPlan();

public:
	enum { IDD = IDD_DESIGN_PLAN };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	int cxClient;
	int cyClient;
//	CMapData* m_pMapData;
	COBJManager* m_pOBJManager;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void init();
	afx_msg void OnClose();
private:
	CTreeCtrl m_TreeCtrl;
	HTREEITEM m_hChild[7];
	FILE* fp;
	std::string fileName;
	int nDat;
	int nOldDat;
	CWinThread *ReadOBJThread;		//读取OBJ文件线程
	CEvent threadStart;//定义全局变量

	//HANDLE		hThread1;
	static UINT ThreadFunc(LPVOID lpParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnClickTreeFileName(NMHDR *pNMHDR, LRESULT *pResult);
};


