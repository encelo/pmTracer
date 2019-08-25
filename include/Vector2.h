#ifndef PMTRACER_VECTOR2_H
#define PMTRACER_VECTOR2_H

namespace pm {

class Vector2
{
  public:
	float x;
	float y;

	Vector2()
	    : x(0.0), y(0.0) {}
	Vector2(float xx, float yy)
	    : x(xx), y(yy) {}
	explicit Vector2(float *vec)
	    : x(vec[0]), y(vec[1]) {}
	Vector2(const Vector2 &other)
	    : x(other.x), y(other.y) {}
	Vector2 &operator=(const Vector2 &other);

	void set(float xx, float yy);
	void set(float *vec);

	inline float *data() { return &x; }
	const float *data() const { return &x; }

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

inline Vector2 &Vector2::operator=(const Vector2 &other)
{
	x = other.x;
	y = other.y;

	return *this;
}

inline void Vector2::set(float xx, float yy)
{
	x = xx;
	y = yy;
}
inline void Vector2::set(float *vec)
{
	x = vec[0];
	y = vec[1];
}

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
