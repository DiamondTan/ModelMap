#include "stdafx.h"
#include "Camera.h"

CCamera* CCamera::m_pCamera = NULL;

CCamera::CCamera()
{
	/*初始化向量*/
	Vector3 zero = Vector3(0.0, 0.0, 0.0);
	Vector3 view = Vector3(0.0, 1.0, 0.0);
	Vector3 up = Vector3(0.0, 0.0, 1.0);

	/*初始化摄像机*/
	m_Position = zero;
	m_View = view;
	m_UpVector = up;
	m_Speed = 10.0f;
	angle = 0.01f;

	m_pCamera = this;
}

CCamera::~CCamera()
{
}

Vector3 CCamera::getPosition()
{
	return m_Position;
}

Vector3 CCamera::getView()
{
	return m_View;
}

Vector3 CCamera::getUpVector()
{
	return m_UpVector;
}

double CCamera::getSpeed()
{
	return m_Speed;
}

void CCamera::setSpeed(double speed)
{
	this->m_Speed = speed;
}

/*设置摄像机的位置，朝向和向上向量*/
void CCamera::setCamera(double positionX,	double positionY,	double positionZ,
						double viewX,		double viewY,		double viewZ,
						double upVectorX,	double upVectorY,	double upVectorZ)
{
	/*构造向量*/
	Vector3 Position = Vector3(positionX,positionY,positionZ);
	Vector3 View = Vector3(viewX,viewY,viewZ);
	Vector3 UpVector = Vector3(upVectorX,upVectorY,upVectorZ);

	/*设置摄像机*/
	m_Position = Position;
	m_View = View;
	m_UpVector = UpVector;
}

/*旋转摄像机方向*/
void CCamera::rotateView(double angle, double x, double y, double z)
{
	Vector3 newView;

	/*计算方向向量*/
	Vector3 view = m_View - m_Position;

	/*计算sin和cos值*/
	double cosTheta = (double)cos(angle);
	double sinTheta = (double)sin(angle);

	/*计算旋转向量的x值*/
	newView.x = (cosTheta + (1 - cosTheta)*x*x)*view.x;
	newView.x += ((1 - cosTheta)*x*y - z*sinTheta)*view.y;
	newView.x += ((1 - cosTheta)*x*z + y*sinTheta)*view.z;

	/*计算旋转向量的y值*/
	newView.y = ((1 - cosTheta)*x*y + z*sinTheta)*view.x;
	newView.y += (cosTheta + (1 - cosTheta)*y*y)*view.y;
	newView.y += ((1 - cosTheta)*y*z - x*sinTheta)*view.z;

	/*计算旋转向量的z值*/
	newView.z = ((1 - cosTheta)*x*z - y*sinTheta)*view.x;
	newView.z += ((1 - cosTheta*y*z) + x*sinTheta)*view.y;
	newView.z += (cosTheta + (1 - cosTheta)*z*z)*view.z;

	/*更新摄像机方向*/
	m_View = m_Position + newView;
}

/*用鼠标旋转摄像机*/
void CCamera::setViewByMouse()
{
	POINT mousePos;   /*保存当前鼠标位置*/

	int middleX = GetSystemMetrics(SM_CXSCREEN) >> 1;  /*得到屏幕宽度的一半*/
	int middleY = GetSystemMetrics(SM_CYSCREEN) >> 1;  /*得到屏幕高度的一半*/

	double angleY = 0.0f;  /*摄像机左右旋转角度*/
	double angleZ = 0.0f;/*摄像机上下旋转角度*/

	static double currentRotX=0.0f;

	/*得到当前鼠标位置*/
	GetCursorPos(&mousePos);
//	ShowCursor(TRUE);

	/*如果鼠标没有移动，则不更新*/
	if ((mousePos.x == middleX) && (mousePos.y == middleY))
		return;

	/*设置鼠标位置在屏幕中心*/
	SetCursorPos(middleX,middleY);

	/*得到鼠标移动方向*/
	angleY = (double)(middleX - mousePos.x) / 2000.0f;
	angleZ = (double)(middleY - mousePos.y) / 2000.0f;

	static double lastRotX = 0.0f;/*用于保存旋转角度*/
	lastRotX = currentRotX;

	/*跟踪摄像机上下旋转角度*/
	currentRotX += angleZ;

	/*如果上下旋转弧度大于1.0，我们截取到1.0并旋转*/
	if (currentRotX > 1.0f)
	{
		currentRotX = 1.0f;
		/*根据保存的角度旋转方向*/
		if (lastRotX != 1.0f)
		{
			/*通过叉积找到与旋转方向垂直的向量*/
			Vector3 vAxis = m_View - m_Position;
			vAxis = vAxis.crossProduct(m_UpVector);
			vAxis = vAxis.normalize();

			/*旋转*/
			rotateView(1.0f-lastRotX,vAxis.x,vAxis.y,vAxis.z);
		}
	}/*如果旋转弧度小于-1.0，则也截取到-1.0并旋转*/
	else if (currentRotX < -1.0f)
	{
		currentRotX = -1.0f;

		if (lastRotX != -1.0f)
		{
			/*通过叉积找到与旋转方向垂直的向量*/
			Vector3 vAxis = m_View - m_Position;
			vAxis = vAxis.crossProduct(m_UpVector);
			vAxis = vAxis.normalize();

			/*旋转*/
			rotateView(-1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);

		}
	}/*否则就旋转angleZ度*/
	else
	{
		/*通过叉积找到与旋转方向垂直的向量*/
		Vector3 vAxis = m_View - m_Position;
		vAxis = vAxis.crossProduct(m_UpVector);
		vAxis = vAxis.normalize();

		/*旋转*/
		rotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	/*总是左右旋转摄像机*/
	rotateView(angleY, 0, 1, 0);
}

/*左右移动摄像机*/
void CCamera::yawCamera(double speed)
{
	Vector3 yaw;
	Vector3 cross = m_View - m_Position;
	cross = cross.crossProduct(m_UpVector);

	/*归一化向量*/
	yaw = cross.normalize();

	m_Position.x += yaw.x*speed;
	m_Position.z += yaw.z*speed;

	m_View.x += yaw.x*speed;
	m_View.z += yaw.z*speed;


	//this->rotateView(0.05f,0.0,1.0,0.0);


}

double CCamera::getAngle()
{
	return this->angle;
}

void CCamera::setAngle(double angle)
{
	this->angle = angle;
}

/*旋转摄像机*/
void CCamera::spinCamera(double angle)
{
	this->rotateView(angle, m_UpVector.x, m_UpVector.y, m_UpVector.z);
}

/*前后移动摄像机*/
void CCamera::moveCamera(double speed)
{
	/*计算方向向量*/
	Vector3 vector = m_View - m_Position;
	vector = vector.normalize();  /*单位化*/

	/*更新摄像机*/
	m_Position.x += vector.x*speed;   /*根据速度更新位置*/
	m_Position.y += vector.y*speed;
	m_Position.z += vector.z*speed;

	m_View.x += vector.x*speed;
	m_View.y += vector.y*speed;
	m_View.z += vector.z*speed;
}

/*设置视点*/
void CCamera::setLook()
{
	/*设置视口*/
	gluLookAt(m_Position.x,m_Position.y,m_Position.z,
	m_View.x,m_View.y,m_View.z,
	m_UpVector.x,m_UpVector.y,m_UpVector.z);
}

