#pragma once
class Vector3
{
public:
//	Vector3();
	virtual ~Vector3();
	/*构造函数*/
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const Vector3&);

	/*成员函数*/
	inline double length();    /*计算向量长度*/
	Vector3 normalize();   /*单位化向量*/
	double dotProduct(const Vector3 &);  /*计算点积*/
	Vector3 crossProduct(const Vector3&);  /*计算叉积*/

	/*运算符重载*/
	Vector3 operator + (const Vector3&);
	Vector3 operator - (const Vector3&);
	Vector3 operator * (double);
	Vector3 operator / (double);
	Vector3 operator -();
public:
	double x;
	double y;
	double z;
};

