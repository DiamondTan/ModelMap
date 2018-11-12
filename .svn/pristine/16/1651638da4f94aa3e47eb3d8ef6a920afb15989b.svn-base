#pragma once


#include "Vector3.h"

class CCamera
{
private:
	/*摄像机属性*/
	static CCamera* m_pCamera; /*当前全局摄像机指针*/
	Vector3 m_Position;  /*位置*/
	Vector3 m_View; /*朝向*/
	Vector3 m_UpVector; /*向上向量*/
	double m_Speed;   /*速度*/
	double angle; /*旋转速度*/
public:
	CCamera();
	~CCamera();
	
	/*获得摄像机状态*/
	Vector3 getPosition();
	Vector3 getView();
	Vector3 getUpVector();
	double getSpeed();

	/*设置速度*/
	void setSpeed(double);

	/*设置摄像机的位置，观察点和向上向量*/
	void setCamera(double ,double ,double ,
		double ,double ,double ,
		double,double,double);

	/*旋转速度*/
	double getAngle();
	void setAngle(double);

	/*旋转摄像机方向*/
	void rotateView(double,double,double,double);

	/*根据鼠标设置摄像机观察方向*/
	void setViewByMouse();

	/*左右摄像机移动*/
	void yawCamera(double);

	/*旋转摄像机*/
	void spinCamera(double);

	/*前后摄像机移动*/
	void moveCamera(double);

	/*放置摄像机*/
	void setLook();

	/*得到摄像机指针*/
	static  CCamera* GetCamera(void) { return m_pCamera; }



};

