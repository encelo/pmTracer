#ifndef PMTRACER_RGBCOLOR_H
#define PMTRACER_RGBCOLOR_H

#include <cmath>

namespace pm {

class RGBColor
{
public:
	float r;
	float g;
	float b;

	RGBColor() : r(0.0f), g(0.0f), b(0.0f) { }
	RGBColor(float rr, float gg, float bb) : r(rr), g(gg), b(bb) { }

	void set(float rr, float gg, float bb) { r = rr; g = gg; b = bb;}

	RGBColor &operator+=(const RGBColor &c);
	RGBColor &operator-=(const RGBColor &c);

	RGBColor &operator*=(float s);
	RGBColor &operator/=(float s);

	RGBColor operator*(float s) const;
	RGBColor operator/(float s) const;

	friend RGBColor operator*(float s, const RGBColor &c);
	friend RGBColor operator/(float s, const RGBColor &c);

	RGBColor operator+(const RGBColor &c) const;
	RGBColor operator-(const RGBColor &c) const;
	RGBColor operator*(const RGBColor &c) const;
	RGBColor operator/(const RGBColor &c) const;

	RGBColor &pow(float exp);
};

inline RGBColor &RGBColor::operator+=(const RGBColor &c)
{
	r += c.r;
	g += c.g;
	b += c.b;

	return *this;
}

inline RGBColor &RGBColor::operator-=(const RGBColor &c)
{
	r -= c.r;
	g -= c.g;
	b -= c.b;

	return *this;
}

inline RGBColor &RGBColor::operator*=(float s)
{
	r *= s;
	g *= s;
	b *= s;

	return *this;
}

inline RGBColor &RGBColor::operator/=(float s)
{
	r /= s;
	g /= s;
	b /= s;

	return *this;
}

inline RGBColor RGBColor::operator*(float s) const
{
	return RGBColor(r * s, g * s, b * s);
}

inline RGBColor RGBColor::operator/(float s) const
{
	return RGBColor(r / s, g / s, b / s);
}

inline RGBColor operator*(float s, const RGBColor &c)
{
	return RGBColor(s * c.r, s * c.g, s * c.b);
}

inline RGBColor operator/(float s, const RGBColor &c)
{
	return RGBColor(s / c.r, s / c.g, s / c.b);
}

inline RGBColor RGBColor::operator+(const RGBColor &c) const
{
	return RGBColor(r + c.r, g + c.g, b + c.b);
}

inline RGBColor RGBColor::operator-(const RGBColor &c) const
{
	return RGBColor(r - c.r, g - c.g, b - c.b);
}

inline RGBColor RGBColor::operator*(const RGBColor &c) const
{
	return RGBColor(r * c.r, g * c.g, b * c.b);
}

inline RGBColor RGBColor::operator/(const RGBColor &c) const
{
	return RGBColor(r / c.r, g / c.g, b / c.b);
}

inline RGBColor &RGBColor::pow(float exp)
{
	r = powf(r, exp);
	g = powf(g, exp);
	b = powf(b, exp);

	return *this;
}

}

#endif
