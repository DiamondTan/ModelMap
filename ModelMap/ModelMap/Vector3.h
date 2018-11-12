#pragma once
class Vector3
{
public:
//	Vector3();
	virtual ~Vector3();
	/*���캯��*/
	Vector3();
	Vector3(double x, double y, double z);
	Vector3(const Vector3&);

	/*��Ա����*/
	inline double length();    /*������������*/
	Vector3 normalize();   /*��λ������*/
	double dotProduct(const Vector3 &);  /*������*/
	Vector3 crossProduct(const Vector3&);  /*������*/

	/*���������*/
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

