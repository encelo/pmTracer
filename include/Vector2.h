#ifndef PMTRACER_VECTOR2_H
#define PMTRACER_VECTOR2_H

namespace pm {

class Vector2
{
public:
	float x;
	float y;

	Vector2() : x(0.0), y(0.0) { }
	Vector2(float xx, float yy) : x(xx), y(yy) { }
	Vector2(float *vec) : x(vec[0]), y(vec[1]) { }

	inline void set(float xx, float yy) { x = xx; y = yy; }
	inline void set(float *vec) { x = vec[0]; y = vec[1]; }

	Vector2 operator-() const;

	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator*(const Vector2 &v) const;
	Vector2 operator/(const Vector2 &v) const;

	Vector2 operator*(float s) const;
	Vector2 operator/(float s) const;

	friend Vector2 operator*(float s, const Vector2 &v);
	friend Vector2 operator/(float s, const Vector2 &v);
};

inline Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

inline Vector2 Vector2::operator+(const Vector2 &v) const
{
	return Vector2(x + v.x, y + v.y);
}

inline Vector2 Vector2::operator-(const Vector2 &v) const
{
	return Vector2(x - v.x, y - v.y);
}

inline Vector2 Vector2::operator*(const Vector2 &v) const
{
	return Vector2(x * v.x, y * v.y);
}

inline Vector2 Vector2::operator/(const Vector2 &v) const
{
	return Vector2(x / v.x, y / v.y);
}

inline Vector2 Vector2::operator*(float s) const
{
	return Vector2(x * s, y * s);
}

inline Vector2 Vector2::operator/(float s) const
{
	return Vector2(x / s, y / s);
}

inline Vector2 operator*(float s, const Vector2 &v)
{
	return Vector2(s * v.x, s * v.y);
}

inline Vector2 operator/(float s, const Vector2 &v)
{
	return Vector2(s / v.x, s / v.y);
}

}

#endif
