#ifndef PMTRACER_VECTOR3_H
#define PMTRACER_VECTOR3_H

#include <cmath>

namespace pm {

class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3() : x(0.0), y(0.0), z(0.0) { }
	Vector3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) { }

	inline void set(double xx, double yy, double zz) { x = xx; y = yy; z = zz; }

	Vector3 operator-() const;

	Vector3 operator+(const Vector3 &v) const;
	Vector3 operator-(const Vector3 &v) const;
	Vector3 operator*(const Vector3 &v) const;
	Vector3 operator/(const Vector3 &v) const;

	Vector3 operator*(double s) const;
	Vector3 operator/(double s) const;

	friend Vector3 operator*(double s, const Vector3 &v);
	friend Vector3 operator/(double s, const Vector3 &v);

	double length() const;
	double sqrLength() const;
	Vector3 normalized() const;
	Vector3 &normalize();

	friend double dot(const Vector3 &v1, const Vector3 &v2);
	friend Vector3 cross(const Vector3 &v1, const Vector3 &v2);
};

inline Vector3 Vector3::operator-() const
{
	return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator+(const Vector3 &v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

inline Vector3 Vector3::operator-(const Vector3 &v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

inline Vector3 Vector3::operator*(const Vector3 &v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

inline Vector3 Vector3::operator/(const Vector3 &v) const
{
	return Vector3(x / v.x, y / v.y, z / v.z);
}

inline Vector3 Vector3::operator*(double s) const
{
	return Vector3(x * s, y * s, z * s);
}

inline Vector3 Vector3::operator/(double s) const
{
	return Vector3(x / s, y / s, z / s);
}

inline Vector3 operator*(double s, const Vector3 &v)
{
	return Vector3(s * v.x, s * v.y, s * v.z);
}

inline Vector3 operator/(double s, const Vector3 &v)
{
	return Vector3(s / v.x, s / v.y, s / v.z);
}

inline double Vector3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

inline double Vector3::sqrLength() const
{
	return x * x + y * y + z * z;
}

inline Vector3 Vector3::normalized() const
{
	const double len = length();
	return Vector3(x / len, y / len, z / len);
}

inline Vector3 &Vector3::normalize()
{
	const double len = length();

	x /= len;
	y /= len;
	z /= len;

	return *this;
}

inline double dot(const Vector3 &v1, const Vector3 &v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline Vector3 cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y,
	               v1.z * v2.x - v1.x * v2.z,
	               v1.x * v2.y - v1.y * v2.x);
}

}

#endif
