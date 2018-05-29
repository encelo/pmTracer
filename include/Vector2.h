#ifndef PMTRACER_VECTOR2_H
#define PMTRACER_VECTOR2_H

namespace pm {

class Vector2
{
public:
	double x;
	double y;

	Vector2() : x(0.0), y(0.0) { }
	Vector2(double xx, double yy) : x(xx), y(yy) { }

	inline void set(double xx, double yy) { x = xx; y = yy; }

	Vector2 operator-() const;

	Vector2 operator+(const Vector2 &v) const;
	Vector2 operator-(const Vector2 &v) const;
	Vector2 operator*(const Vector2 &v) const;
	Vector2 operator/(const Vector2 &v) const;

	Vector2 operator*(double s) const;
	Vector2 operator/(double s) const;

	friend Vector2 operator*(double s, const Vector2 &v);
	friend Vector2 operator/(double s, const Vector2 &v);
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

inline Vector2 Vector2::operator*(double s) const
{
	return Vector2(x * s, y * s);
}

inline Vector2 Vector2::operator/(double s) const
{
	return Vector2(x / s, y / s);
}

inline Vector2 operator*(double s, const Vector2 &v)
{
	return Vector2(s * v.x, s * v.y);
}

inline Vector2 operator/(double s, const Vector2 &v)
{
	return Vector2(s / v.x, s / v.y);
}

}

#endif
