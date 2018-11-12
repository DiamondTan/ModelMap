#include "stdafx.h"
#include <math.h>
#include "Vector3.h"


Vector3::Vector3() :x(0.0), y(0.0), z(0.0)
{
}

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z)
{
}

Vector3::Vector3(const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

Vector3::~Vector3()
{
}

/*计算向量的长度*/
inline double Vector3::length()
{
	return static_cast<double>(sqrt(x*x + y*y + z*z));
}

/*单位化向量*/
Vector3 Vector3::normalize()
{
	double len = this->length();     /*计算长度*/
	if (len == 0.0)
		len = 1.0;
	x = x / len;
	y = y / len;
	z = z / len;

	return *this;
}

/*点积*/
double Vector3::dotProduct(const Vector3& v)
{
	return (x*v.x + y*v.y + z*v.z);
}

/*叉积*/
Vector3 Vector3::crossProduct(const Vector3& v)
{
	Vector3 vec;

	vec.x = y*v.z - z*v.y;
	vec.y = z*v.x - x*v.z;
	vec.z = x*v.y - y*v.x;

	return vec;
}

/*操作符 +*/
Vector3 Vector3::operator + (const Vector3& v)
{
	Vector3 Vec;

	Vec.x = x + v.x;
	Vec.y = y + v.y;
	Vec.z = z + v.z;

	return Vec;
}

/*操作符 -*/
Vector3 Vector3::operator -(const Vector3 &v)
{
	Vector3 Vec;

	Vec.x = x - v.x;
	Vec.y = y - v.y;
	Vec.z = z - v.z;

	return Vec;
}

/*操作符 * */
Vector3 Vector3::operator * (double scale)
{
	x *= scale;
	y *= scale;
	z *= scale;

	return *this;
}

/*操作符 / */
Vector3 Vector3::operator / (double scale)
{
	if (scale != 0.0)
	{
		x /= scale;
		y /= scale;
		z /= scale;
	}
	return *this;
}

/*负号*/
Vector3 Vector3::operator-()
{
	Vector3 Vec(-x, -y, -z);
	return Vec;
}