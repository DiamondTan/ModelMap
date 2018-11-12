// OpenGL.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModelMap.h"
#include "OpenGL.h"

// COpenGL

#define KEY_DOWN(vk_code)((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// The OBJ model
//GLMmodel* pModel = NULL;
IMPLEMENT_DYNCREATE(COpenGL, CFormView)

COpenGL::COpenGL()
	: CFormView(COpenGL::IDD)
	, m_rLButtonDown(false)
	, m_bcikOBJ(false)
{

}

COpenGL::~COpenGL()
{
}

void COpenGL::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenGL, CFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// COpenGL ���

#ifdef _DEBUG
void COpenGL::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COpenGL::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COpenGL ��Ϣ��������

bool COpenGL::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
		1,                                                     // version number
		PFD_DRAW_TO_WINDOW |           // support window
		PFD_SUPPORT_OPENGL |               // support OpenGL
		PFD_DOUBLEBUFFER,                     // double buffered
		PFD_TYPE_RGBA,                           // RGBA type
		24,                                                 // 24-bit color depth
		0, 0, 0, 0, 0, 0,                               // color bits ignored
		0,                                                   // no alpha buffer
		0,                                                   // shift bit ignored
		0,                                                   // no accumulation buffer
		0, 0, 0, 0,                                       // accum bits ignored
		32,                                                 // 32-bit z-buffer
		0,                                                   // no stencil buffer
		0,                                                   // no auxiliary buffer
		PFD_MAIN_PLANE,                         // main layer
		0,                                                   // reserved
		0, 0, 0                                            // layer masks ignored
	};
	CClientDC clientDC(this);
	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);
	//int m_nPixelFormat = ChoosePixelFormat(clientDC.m_hDC, &pfd);
	if (m_nPixelFormat == 0)
	{
		MessageBox(L"ChoosePixelFormat failed.");
		return false;
	}
	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		MessageBox(L"SetPixelFormat failed.");
		return false;
	}
	/*if (SetPixelFormat(clientDC.m_hDC, m_nPixelFormat, &pfd)==FALSE)
	{
		MessageBox(L"SetPixelFormat failed.");
		return false;
	}*/
	return true;
}
//��ʼ������
bool COpenGL::InitializeOpenGL()
{
	//Get a DC for the Client Area
	m_pDC = new CClientDC(this);
	//Failure to Get DC
	if (m_pDC == NULL)
	{
		MessageBox(L"Error Obtaining DC");
		return false;
	}
	//Failure to set the pixel format
	if (!SetupPixelFormat())
	{
		return false;
	}
	//Create Rendering Context
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//Failure to Create Rendering Context
	if (m_hRC == 0)
	{
		MessageBox(L"Error Creating RC");
		return false;
	}

	//Make the RC Current
	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == false)
	{
		MessageBox(L"Error making RC Current");
		return false;
	}

	// ������Ӱƽ��
	::glShadeModel(GL_SMOOTH);
	//��ɫ����
	::glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	//������Ȼ���
	::glClearDepth(1.0f);
	//������Ȳ���
	::glEnable(GL_DEPTH_TEST);

	glEnable(GL_POINT_SMOOTH | GL_LINE_SMOOTH | GL_POLYGON_SMOOTH);
	glHint(GL_POINT_SMOOTH | GL_LINE_SMOOTH | GL_POLYGON_SMOOTH, GL_NICEST);

/*	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH, GL_NICEST);

	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);*/

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);//ָ����ȱȽ���ʹ�õ���ֵ

	//������Ȳ��Ե�����
	::glDepthFunc(GL_LEQUAL);
	//	::glEnable(GL_CULL_FACE);
	//����ϵͳ��͸�ӽ�������
	::glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines  
	glEnable(GL_NORMALIZE);	//�����������й淶��
	glEnable(GL_RESCALE_NORMAL);


	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat specularLight[] = { 0.7f ,0.7f, 0.7f, 1.0f };

	GLfloat lightPos[] = { 0.0f, 1200.0f, 0.0f, 1.0f };//���λ��
  
	GLfloat spotDir[] = { 0.0f, -1.0f, 0.0f };            //��Ʒ���  
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);		//���û�����Դ  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);		//�����������Դ 
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);		//���þ����Դ  
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);			//���õƹ�λ��  
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);

	glEnable(GL_COLOR_MATERIAL);							//���ò��ʵ���ɫ����  
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);		//ָ��������ɫ����  
//	glMaterialfv(GL_FRONT, GL_SPECULAR, specularLight);		//ָ�����϶Ծ����ķ�Ӧ  
	glMateriali(GL_FRONT, GL_SHININESS, 80);				//ָ������ϵ��  
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);					//�򿪰�ɫ����Դ  

	return true;

}
bool COpenGL::loadTexture()
{
	char* filename = { "data/wall.bmp"};
//	CTexture *m_texture = new CTexture();
	if (!m_texture.Loadbitmap(filename))  /*����λͼ*/
	{
		/*���ʧ���򵯳��Ի���*/
		MessageBox(_T("װ��λͼʧ��"), _T("����"), MB_OK);
		return false;
		//exit(0);
	}
	/*������������*/	
	glGenTextures(1, &m_texture.ID);

	/*����������*/
	glBindTexture(GL_TEXTURE_2D, m_texture.ID);
	
	/*��������*/
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_texture.imageWidth,
		m_texture.imageHeight, GL_RGB, GL_UNSIGNED_BYTE, m_texture.image);

	/*�����˲�*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true;
}
bool COpenGL::Init()
{
	
	if (!InitializeOpenGL())
	{
		return false;
	}

	/** ��������� */
	this->m_Camera.setCamera(0.0, 20.0, 250.0, 0.0, 20.0, 248.0, 0, 1, 0);

	this->loadTexture();
	InitList();

	return true;
}
void COpenGL::InitList()
{

	InitAxis();
	InitGround();
	InitData();

}

int COpenGL::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ�������ר�õĴ�������

	

	m_pMapData = CMapData::GetInstance();
	m_pOBJManager = COBJManager::GetInstance();
	
	if (!Init())
	{
		return -1;
	}
	m_OBJdraw = false;

	return 0;
}


void COpenGL::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO:  �ڴ˴�������Ϣ�����������

	//Delete the RC
	if (m_hRC)
	{
		//Make the RC non-current
		if (::wglMakeCurrent(NULL, NULL) == FALSE)
		{
			::MessageBox(NULL, L"�ͷ�DC��RCʧ�ܡ�", L"�رմ���", MB_OK | MB_ICONINFORMATION);
		}
		//Delete the rendering context
		if (::wglDeleteContext(m_hRC) == FALSE)
		{
			::MessageBox(NULL, L"�ͷ�RCʧ�ܡ�", L"�رմ���", MB_OK | MB_ICONINFORMATION);
		}
		m_hRC = NULL;
	}

	//Delete the DC
	if (m_pDC)
	{
		delete m_pDC;
	}
	//Set it to NULL
	m_pDC = NULL;

	//for (std::vector<CTexture>::iterator iter = TextureList.begin(); iter != TextureList.end(); iter++)
	//{
	//	(*iter).FreeImage();
	//}

	m_texture.FreeImage();

	if (glIsList(list))
	{
		glDeleteLists(list, 1);
	}
	if (glIsList(AxisList))
	{
		glDeleteLists(AxisList, 1);
	}
	if (glIsList(GroundList))
	{
		glDeleteLists(GroundList, 1);
	}

}


void COpenGL::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴�������Ϣ�����������
	if (cx <= 0)
		cx = 1;
	if (cy <= 0)
		cy = 1;

	CxClient = cx;
	CyClient = cy;
	//ѡ��ͶӰ����
	::glMatrixMode(GL_PROJECTION);
	//����ͶӰ����
	::glLoadIdentity();
	//���㴰�ڵ���۱���
	::gluPerspective(45.0f, (GLfloat)cx / (GLfloat)cy, 5.0f, 3000.0f);
	//����ģ�͹۲����
	::glMatrixMode(GL_MODELVIEW);
	//����ģ�͹۲����
	::glLoadIdentity();
	//���õ�ǰ���ӿ�
	::glViewport(0, 0, cx, cy);

	Invalidate();
}


void COpenGL::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴�������Ϣ�����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()

	this->DrawScene();

}

void COpenGL::DrawTargets()
{

	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess = 0.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //������ϵ�ǰ����� "��η���"  
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //���ϵ�ǰ��Ϊ ������  
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //������ϵ�ǰ��Ϊ ���淴��  
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission); //������ϵ�ǰ��Ϊ ����ָ��  
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess); //���ϵ�ǰ�� ���� ����ɫ  


	glPushMatrix();
	/*glColor3f(1.0,0.8,0.8);
	glTranslatef(0.0,20.0,0.0);*/
	
	COBJ *obj;
	int value;

	for (int i = 0; i < m_pOBJManager->getSize(); i++)
	{
		
		//value = m_pOBJManager->getAt(i);
		obj=m_pOBJManager->getAt(i);
		glLoadName(i + 1);
		obj->draw();
	}

	glPopMatrix();
}
void COpenGL::DrawShow()
{
	COBJ *temp = COBJManager::getShowOBJ();
	if (temp == NULL)
	{
		m_OBJdraw = false;
		return;
	}
	m_OBJdraw = true;
	temp->draw();
}
void COpenGL::DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	/** ��������� */
	this->m_Camera.setLook();

	

//	this->DrawAxis();

	this->DrawGround();
	this->drawData();
	this->DrawTargets();
	this->DrawShow();
	
	this->UpdateCamera();

	SwapBuffers(wglGetCurrentDC());
}
void COpenGL::UpdateCamera()
{
	/** ���̰�����Ӧ */
	if (KEY_DOWN(VK_SHIFT))                      /**< ����SHIFT��ʱ���� */
	{
		m_Camera.setSpeed(5.0f);
		m_Camera.setAngle(0.04f);
	}
	if (!KEY_DOWN(VK_SHIFT))
	{
		m_Camera.setSpeed(2.0f);
		m_Camera.setAngle(0.02f);
	}
	if (KEY_DOWN(VK_UP) || KEY_DOWN('W'))   /**< ���Ϸ������'W'������ */
		m_Camera.moveCamera(m_Camera.getSpeed());          /**< �ƶ������ */

	if (KEY_DOWN(VK_DOWN) || KEY_DOWN('S')) /**< ���·������'S'������ */
		m_Camera.moveCamera(-m_Camera.getSpeed());         /**< �ƶ������ */

	if (KEY_DOWN(VK_LEFT) || KEY_DOWN('A')) /**< ���������'A'������ */
		m_Camera.spinCamera(m_Camera.getAngle());          /**< �ƶ������ */

	if (KEY_DOWN(VK_RIGHT) || KEY_DOWN('D')) /**< ���ҷ������'D'������ */
		m_Camera.spinCamera(-m_Camera.getAngle());            /**< �ƶ������ */

	/** ���ݵ��θ߶ȸ�������� */
	Vector3 vNewPos = m_Camera.getPosition();    /**< �õ���ǰ�����λ�� */


	/** ������������� */
	Vector3 vView = m_Camera.getView();

	/** ��������� */
	m_Camera.setCamera(vNewPos.x, vNewPos.y, vNewPos.z,
		vView.x, vView.y, vView.z,
		0, 1, 0);
}
void COpenGL::InitData()
{
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	//if (TextureList.GetSize() > 0){
		/*������*/
	//	glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_texture.ID);
	
//	}

		GLfloat mat_ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
		GLfloat mat_specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
		GLfloat mat_emission[] = { 0.2f, 0.2f, 0.2f, 1.0f };
		GLfloat mat_shininess = 0.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //������ϵ�ǰ����� "��η���"  
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //���ϵ�ǰ��Ϊ ������  
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //������ϵ�ǰ��Ϊ ���淴��  
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission); //������ϵ�ǰ��Ϊ ����ָ��  
		glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess); //���ϵ�ǰ�� ���� ����ɫ  

	

	glEnable(GL_LINE_SMOOTH | GL_POLYGON_SMOOTH);
	glHint( GL_LINE_SMOOTH | GL_POLYGON_SMOOTH, GL_NICEST);
	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	for (int i = 0; i < m_pMapData->getSize(); i++)
	{
		Line* p_line = m_pMapData->getAt(i);
		
		this->drawRect(p_line->BeginPoint, p_line->EndPoint);
	}
	
	/*�ر�������Ԫ0*/
//	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);

	glEndList();
}

void COpenGL::drawData()
{
	glCallList(list);

	
}
void COpenGL::drawRect(cvPoint& BeginPoint, cvPoint& EndPoint)
{
	int num = 2;
	int bx = BeginPoint.cx *num, by = BeginPoint.cy * num;
	int zx = EndPoint.cx *num, zy = EndPoint.cy * num;
	int step = 10;
	int height = 300;
	glBegin(GL_QUADS);

	if (abs(static_cast<double>(zy - by) / (zx - bx)) < 1){
	
		glTexCoord2d(0, 0);
		glNormal3f(0.0,1.0,0.0); glVertex3f(zx , height, zy + step);
		glTexCoord2d(1, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx , height, by + step);
		glTexCoord2d(1, 1);	
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(bx, 0.0, by + step);
		glTexCoord2d(0, 1);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(zx, 0.0, zy + step);

		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx , height, by - step);
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx , height, zy - step);
		glTexCoord2d(1, 1);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(zx, 0.0, zy - step);
		glTexCoord2d(1, 0);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(bx, 0.0, by - step);

		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx , height, by - step);
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx , height, by + step);
		glTexCoord2d(1, 1);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(bx, 0.0, by + step);
		glTexCoord2d(1, 0);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(bx, 0.0, by - step);

		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx , height, zy - step);
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx , height, zy + step);
		glTexCoord2d(1, 1);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(zx, 0.0, zy + step);
		glTexCoord2d(1, 0);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(zx, 0.0, zy - step);


		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx , height, by + step);
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx , height, zy + step);
		glTexCoord2d(1, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx , height, zy - step);
		glTexCoord2d(1, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx , height, by - step);
	}
	else
	{

		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx - step, height, by);	
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx - step, height, zy);
		glTexCoord2d(1, 1);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(zx - step, 0.0, zy);	
		glTexCoord2d(1, 0);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(bx - step, 0.0, by);

		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx + step, height, by );
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx + step, height, zy );
		glTexCoord2d(1, 1);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(zx + step, 0.0, zy);
		glTexCoord2d(1, 0);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(bx + step, 0.0, by);

		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx + step, height, by );
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx - step, height, by );
		glTexCoord2d(1, 1);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(bx + step, 0.0, by);
		glTexCoord2d(1, 0);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(bx - step, 0.0, by);
	
		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx + step, height, zy );
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx - step, height, zy );
		glTexCoord2d(1, 1);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(zx - step, 0.0, zy);
		glTexCoord2d(1, 0);
		glNormal3f(0.0, -1.0, 0.0);
		glVertex3f(zx + step, 0.0, zy);


		glTexCoord2d(0, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx - step, height, by );
		glTexCoord2d(0, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx - step, height, zy );
		glTexCoord2d(1, 1);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(zx + step, height, zy );
		glTexCoord2d(1, 0);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(bx + step, height, by );
	}

	glEnd();
	
}

void COpenGL::InitAxis()
{
	AxisList = glGenLists(1);
	float length=45.0f;
	glNewList(AxisList, GL_COMPILE);
	glBegin(GL_LINES);
	//x�� ��ɫ
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-length, 0.0f, 0.0f);
	glVertex3f(length, 0.0f, 0.0f);


	//glutSolidCone(1,3,5,5);//��Բ׶

	//y�� ��ɫ
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -length, 0.0f);
	glVertex3f(0.0f, length, 0.0f);


	//z�� ��ɫ
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -length);
	glVertex3f(0.0f, 0.0f, length);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(length-10, 0.0, 0.0);
	glRotatef(90.0f, 0.0, 1.0, 0.0);

	glutSolidCone(4, 20, 20, 20);//��Բ׶

	glPopMatrix();

	glColor3f(0.0, 1.0, 0.0);

	glPushMatrix();
	glTranslatef(0.0, length-10, 0.0);
	glRotatef(-90.0f, 1.0, 0.0, 0.0);

	glutSolidCone(4, 20, 20, 20);//��Բ׶

	glPopMatrix();


	glColor3f(0.0, 0.0, 1.0);

	glPushMatrix();
	glTranslatef(0.0, 0.0, length-10);


	glutSolidCone(4, 20, 20, 20);//��Բ׶

	glPopMatrix();

	glEndList();
}
void COpenGL::DrawAxis()
{
	glCallList(AxisList);
}
void COpenGL::InitGround()
{
	GroundList = glGenLists(1);
	glNewList(GroundList, GL_COMPILE);

	GLfloat mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_diffuse[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess = 0.0f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); //������ϵ�ǰ����� "��η���"  
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); //���ϵ�ǰ��Ϊ ������  
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); //������ϵ�ǰ��Ϊ ���淴��  
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission); //������ϵ�ǰ��Ϊ ����ָ��  
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess); //���ϵ�ǰ�� ���� ����ɫ  


	bool black = false;
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	const int  width = 1200;
	int add = 10;
	float height = 4;
	for (int i = -width; i <= width; i += add)
	{

		for (int j = -width; j <= width; j += add)
		{
			if (black)
				glColor3f(1.0, 1.0, 1.0);
			else
				glColor3f(0.0, 0.0, 0.0);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(i, 0, j);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(i + add, 0, j);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(i + add, 0, j + add);

			glNormal3f(0.0, 1.0, 0.0);
			glVertex3f(i, 0, j + add);


			black = !black;
		}
	}
	glEnd();

	glEndList();

}
void COpenGL::DrawGround()
{
	glCallList(this->GroundList);
}

void COpenGL::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ
	
	
	CFormView::OnTimer(nIDEvent);
}

void COpenGL::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	CFormView::OnChar(nChar, nRepCnt, nFlags);
}

#define SIZE 512
#define N 5.0f

void COpenGL::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ
	//SetActiveView(this);

	int cx = point.x;
	int cy = point.y;

	if (m_OBJdraw)
	{
		m_pOBJManager->addOBJ(*COBJManager::getShowOBJ());
		m_OBJdraw = false;
		COBJManager::delShowObj();
	}
	else
	{
		pick(cx, cy);
	}
	
	CFormView::OnLButtonDown(nFlags, point);
}

void COpenGL::pick(int cx, int cy)
{
	GLuint	buffer[SIZE];										// Set Up A Selection Buffer
	GLint	hits;												// The Number Of Objects That We Selected

	// The Size Of The Viewport. [0] Is <x>, [1] Is <y>, [2] Is <length>, [3] Is <width>
	GLint	viewport[4];

	// This Sets The Array <viewport> To The Size And Location Of The Screen Relative To The Window
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(SIZE, buffer);								// Tell OpenGL To Use Our Array For Selection

	// Puts OpenGL In Selection Mode. Nothing Will Be Drawn.  Object ID's and Extents Are Stored In The Buffer.
	(void)glRenderMode(GL_SELECT);

	glInitNames();												// Initializes The Name Stack
	glPushName(0);												// Push 0 (At Least One Entry) Onto The Stack

	glMatrixMode(GL_PROJECTION);								// Selects The Projection Matrix
	glPushMatrix();												// Push The Projection Matrix
	glLoadIdentity();											// Resets The Matrix

	// This Creates A Matrix That Will Zoom Up To A Small Portion Of The Screen, Where The Mouse Is.
	/*gluPickMatrix((GLdouble)cx, (GLdouble)(viewport[3] - cy), 1.0f, 1.0f, viewport);*/
	gluPickMatrix((GLdouble)cx, (GLdouble)(viewport[3] - cy), N, N, viewport);

	// Apply The Perspective Matrix
	gluPerspective(45.0f, (GLfloat)(viewport[2] - viewport[0]) / (GLfloat)(viewport[3] - viewport[1]), 5.0f, 3000.0f);
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	DrawTargets();												// Render The Targets To The Selection Buffer
	glMatrixMode(GL_PROJECTION);								// Select The Projection Matrix
	glPopMatrix();												// Pop The Projection Matrix
	glMatrixMode(GL_MODELVIEW);									// Select The Modelview Matrix
	hits = glRenderMode(GL_RENDER);								// Switch To Render Mode, Find Out How Many
	// Objects Were Drawn Where The Mouse Was

	if (hits != 0)
		processHits(hits, buffer);
}
void COpenGL::processHits(GLint hits, GLuint buffer[])
{
	unsigned int i, j;
	m_bcikOBJ = true;	//�����OBJ

	GLuint names, *ptr;
	ptr = (GLuint*)buffer;
	names = *ptr;
	ptr += 3;   // ���������������

	value = (*ptr)-1;
	//value = (*ptr) ;
	//for (i = 0; i<hits; i++) {
	//	names = *ptr;
	//	ptr += 3;   // ���������������
	//	for (j = 0; j<names; j++) {
	//		/*if (*ptr == 1)
	//			MessageBox(L"FLOOR",L"Floor",MB_OK);
	//		else
	//			MessageBox(L"WALL", L"Wall", MB_OK);*/
	//		ptr++;
	//	}
	//}
}

void COpenGL::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ
	
	if (m_bcikOBJ)
	{
		m_bcikOBJ = false;
	}

	CFormView::OnLButtonUp(nFlags, point);
}

void COpenGL::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	int cx = point.x;
	int cy = point.y;

	if (this->m_rLButtonDown)
	{
		//this->m_Camera.setViewByMouse();   /*�����⣬*/
	}

	if (m_bcikOBJ)
	{
		Vector3 vt;
		vt = screenToWorld(cx, cy);
		m_pOBJManager->getAt(value)->setLocation(vt.x, vt.z);
	}

	if (m_OBJdraw)
	{
		Vector3 vt;
		vt = screenToWorld(cx, cy);
		COBJManager::getShowOBJ()->setLocation(vt.x, vt.z);
	}

	CFormView::OnMouseMove(nFlags, point);
}

Vector3 COpenGL::screenToWorld(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posX, posY, posZ;
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	Vector3 vt(posX, posY, posZ);
	return vt;
}

void COpenGL::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	this->m_rLButtonDown = false;
	ShowCursor(TRUE);

	CFormView::OnRButtonUp(nFlags, point);
}


void COpenGL::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	ShowCursor(FALSE);
	this->m_rLButtonDown = true;

	if (m_OBJdraw)
	{
		m_OBJdraw = false;
		COBJManager::delShowObj();
	}

	CFormView::OnRButtonDown(nFlags, point);
}


BOOL COpenGL::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ�����ר�ô����/����û���

	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);//openGL��MDI�б���

	return CFormView::PreCreateWindow(cs);
}


BOOL COpenGL::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ�������Ϣ������������/�����Ĭ��ֵ

	return TRUE;

	//return CFormView::OnEraseBkgnd(pDC);
}


void COpenGL::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CFormView::OnShowWindow(bShow, nStatus);

	// TODO:  �ڴ˴�������Ϣ�����������


}
