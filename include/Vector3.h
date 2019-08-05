#ifndef PMTRACER_VECTOR3_H
#define PMTRACER_VECTOR3_H

#include <cmath>

namespace pm {

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3() : x(0.0), y(0.0), z(0.0) { }
	Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) { }
	Vector3(float *vec) : x(vec[0]), y(vec[1]), z(vec[2]) { }

	inline void set(float xx, float yy, float zz) { x = xx; y = yy; z = zz; }
	inline void set(float *vec) { x = vec[0]; y = vec[1]; z = vec[2]; }

	Vector3 operator-() const;

	Vector3 operator+(const Vector3 &v) const;
	Vector3 operator-(const Vector3 &v) const;
	Vector3 operator*(const Vector3 &v) const;
	Vector3 operator/(const Vector3 &v) const;

	Vector3 operator*(float s) const;
	Vector3 operator/(float s) const;

	friend Vector3 operator*(float s, const Vector3 &v);
	friend Vector3 operator/(float s, const Vector3 &v);

	float length() const;
	float sqrLength() const;
	Vector3 normalized() const;
	Vector3 &normalize();

	friend float dot(const Vector3 &v1, const Vector3 &v2);
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

inline Vector3 Vector3::operator*(float s) const
{
	return Vector3(x * s, y * s, z * s);
}

inline Vector3 Vector3::operator/(float s) const
{
	return Vector3(x / s, y / s, z / s);
}

inline Vector3 operator*(float s, const Vector3 &v)
{
	return Vector3(s * v.x, s * v.y, s * v.z);
}

inline Vector3 operator/(float s, const Vector3 &v)
{
	return Vector3(s / v.x, s / v.y, s / v.z);
}

inline float Vector3::length() const
{
	return sqrtf(x * x + y * y + z * z);
}

inline float Vector3::sqrLength() const
{
	return x * x + y * y + z * z;
}

inline Vector3 Vector3::normalized() const
{
	const float len = length();
	return Vector3(x / len, y / len, z / len);
}

inline Vector3 &Vector3::normalize()
{
	const float len = length();

	x /= len;
	y /= len;
	z /= len;

	return *this;
}

inline float dot(const Vector3 &v1, const Vector3 &v2)
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
