// DesignPlan.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModelMap.h"
#include "DesignPlan.h"
#include <ctype.h>

// CDesignPlan

IMPLEMENT_DYNCREATE(CDesignPlan, CFormView)

CDesignPlan::CDesignPlan()
: CFormView(CDesignPlan::IDD)
, fileName("data/obj.conf")
, nDat(-1)
, nOldDat(-1)
{

}

CDesignPlan::~CDesignPlan()
{
}

void CDesignPlan::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_FILE_NAME, m_TreeCtrl);

	init();

}

void CDesignPlan::init()
{

	char Buf[][10] = { "SOFA", "BED", "TABLE", "CHAIR", "CABINET", "LIGHT" };
	int eno = fopen_s(&fp, this->fileName.c_str(), "r");
	if (eno)
	{
		CString str;
		str = this->fileName.c_str();
		MessageBox(L"���ļ�ʧ��\n�Ҳ����ļ�" + str + "\n", L"ERROR", MB_OK | MB_ICONERROR);
		return;
	}


	char readBuf[1024] = { 0 };
	//	std::string readBuf;
	char typeBuf[10];// = { 0 };
	char Name[1024];// = { 0 };
	memset(typeBuf, '0', /*10 **/ sizeof(typeBuf));
	memset(Name, '0', /*1024 **/ sizeof(Name));
	int type = -1;
	while (!feof(fp))
	{

		fgets(readBuf, 1024, fp);

		if (readBuf[0] == '#' || readBuf[0] == '\n')
			continue;
		char *p = readBuf;
		int i = 0;
		while (*p != '\0' && *p != ' ' && *p != '\t')
		{
			Name[i] = *p;
			i++; p++;
		}
		Name[i] = '\0';
		while (!isalpha(*p))
		{
			p++;
		}
		i = 0;
		do
		{
			typeBuf[i] = *p;
			i++; p++;
		} while (isalpha(*p));

		typeBuf[i] = '\0';

		for (int i = 0; i < 6; i++)
		{
			if (!_stricmp(typeBuf, Buf[i]))
			{
				type = i;
				break;
			}
		}

		if (type == -1)
		{
			type = OTHER;
		}

//		m_pOBJManager->addOBJ(COBJ(Name, type));

		m_pOBJManager->addfile(COBJManager::file(Name, type));

	}


	fclose(fp);
}

BEGIN_MESSAGE_MAP(CDesignPlan, CFormView)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CDesignPlan::OnBnClickedButtonRefresh)
	ON_NOTIFY(NM_CLICK, IDC_TREE_FILE_NAME, &CDesignPlan::OnClickTreeFileName)
END_MESSAGE_MAP()


// CDesignPlan ���

#ifdef _DEBUG
void CDesignPlan::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDesignPlan::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDesignPlan ��Ϣ��������


void CDesignPlan::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴�������Ϣ�����������


	cxClient = cx;
	cyClient = cy;


	Invalidate();
}


void CDesignPlan::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴�������Ϣ�����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()

	CRect rect;

	GetDlgItem(IDC_BUTTON_REFRESH)->GetWindowRect(&rect);//��ȡ�ؼ�����Ļ����
	ScreenToClient(&rect);//ת��Ϊ�Ի����ϵĿͻ�����
	GetDlgItem(IDC_STATIC)->MoveWindow(0, rect.bottom, cxClient, 3);

	m_TreeCtrl.MoveWindow(0, rect.bottom, cxClient, cyClient, TRUE);


	COBJ *obj;
	CString str;
	m_TreeCtrl.DeleteAllItems();

	HTREEITEM hRoot;

	hRoot = m_TreeCtrl.InsertItem(L"3Dģ��", TVI_ROOT); //��������

	m_hChild[0] = m_TreeCtrl.InsertItem(L"ɳ��", hRoot);
	m_hChild[1] = m_TreeCtrl.InsertItem(L"��", hRoot);
	m_hChild[2] = m_TreeCtrl.InsertItem(L"̨��", hRoot);
	m_hChild[3] = m_TreeCtrl.InsertItem(L"����", hRoot);
	m_hChild[4] = m_TreeCtrl.InsertItem(L"����", hRoot);
	m_hChild[5] = m_TreeCtrl.InsertItem(L"�ƾ�", hRoot);
	m_hChild[6] = m_TreeCtrl.InsertItem(L"����", hRoot);
	HTREEITEM hItem;
	COBJManager::file *temp;
	for (int i = 0; i < m_pOBJManager->getfileSize(); i++)
	{

		temp = m_pOBJManager->gatfileAt(i);
		int type = temp->getType();
		str = temp->name.c_str();
		hItem = m_TreeCtrl.InsertItem(str, m_hChild[type]);
		m_TreeCtrl.SetItemData(hItem, i);
	}


}


int CDesignPlan::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ�������ר�õĴ�������

	m_pOBJManager = COBJManager::GetInstance();

	ReadOBJThread = AfxBeginThread(ThreadFunc, &threadStart);


	return 0;
}


void CDesignPlan::OnClose()
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	CFormView::OnClose();
}


void CDesignPlan::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	CFormView::OnTimer(nIDEvent);
}


void CDesignPlan::OnBnClickedButtonRefresh()
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	//init();
	Invalidate();
}

static bool b_thread = false;;
void CDesignPlan::OnClickTreeFileName(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ����ӿؼ�֪ͨ�����������

	CPoint pt = GetCurrentMessage()->pt;   //��ȡ��ǰ�������Ϣ�������

	m_TreeCtrl.ScreenToClient(&pt);   //��������Ļ���꣬ת�������οؼ��Ŀͻ�������

	UINT uFlags = 0;
	DWORD lpExitCode;
	HTREEITEM hItem = m_TreeCtrl.HitTest(pt, &uFlags);//Ȼ�����������

	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))//��������λ�����ڽڵ�λ������
	{
		m_TreeCtrl.SelectItem(hItem);
		//��ȡ��ʼ�������õ����ݣ�ע���������Ϊʲô��ʼҪÿ���ڵ����ò�ͬ�����ݵ�ԭ�򡣵�Ȼ�����������ݽڵ�Ƚ��٣���Ҳ����ͨ����ȡ�ڵ�����֣����������õ�"������"��Ȼ��ͨ���ַ����Ƚ����жϵ�����ĸ��ڵ�
		nDat = m_TreeCtrl.GetItemData(hItem);

		if (!b_thread)
		{
			//COBJManager::setShow(nDat);
			m_pOBJManager->setShowObj(m_pOBJManager->gatfileAt(nDat)->fileName);
			threadStart.SetEvent();//����һ���߳̽���ʱ���ã�����ȡ����һ�̵߳�����
		}

		

		*pResult = 0;
	}
}
UINT CDesignPlan::ThreadFunc(LPVOID lpParam)
{
	CEvent *threadStart = (CEvent *)lpParam;

	while (true){
		b_thread = true;
		/*threadStart->ResetEvent();
		COBJManager* m_pOBJManager = COBJManager::GetInstance();
		int show = COBJManager::getShow();
		if (show != -1)
		{
			COBJ * OBJ = m_pOBJManager->getAt(COBJManager::getShow());
			OBJ->LoadOBJ();
		}*/

		COBJ * OBJ = COBJManager::getShowOBJ();
		if (OBJ != NULL)
		{
			OBJ->LoadOBJ();
		}

		b_thread = false;
		::WaitForSingleObject(threadStart->m_hObject, INFINITE);//����ʱ��������ǰ�߳�
	}

	//threadStart->SetEvent();//����һ���߳̽���ʱ���ã�����ȡ����һ�̵߳�����

	return 0;
}