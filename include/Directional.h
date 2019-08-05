#ifndef PMTRACER_DIRECTIONAL_H
#define PMTRACER_DIRECTIONAL_H

#include "Light.h"
#include "ShadeRecord.h"

namespace pm {

class Directional : public Light
{
  public:
	Directional(float x, float y, float z)
	    : Light(), ls_(1.0f), color_(1.0f, 1.0f, 1.0f), direction_(x, y, z) {}

	inline Vector3 direction(ShadeRecord &sr) const override { return direction_; }
	inline RGBColor L(ShadeRecord &sr) const override { return (ls_ * color_); }
	bool inShadow(const Ray &ray, const ShadeRecord &sr) const override;

	inline float radianceScale() const { return ls_; }
	inline void setRadianceScale(float s) { ls_ = s; }

	inline const RGBColor &color() const { return color_; }
	inline void setColor(const RGBColor &color) { color_ = color; }
	inline void setColor(float r, float g, float b) { color_.set(r, g, b); }

	inline void setDirection(const Vector3 &direction) { direction_ = direction.normalized(); }
	void setDirection(float x, float y, float z);

  protected:
	float ls_;
	RGBColor color_;
	Vector3 direction_;
};

inline bool Directional::inShadow(const Ray &ray, const ShadeRecord &sr) const
{
	float t;
	const size_t numObjects = sr.w.objects().size();

	for (int i = 0; i < numObjects; i++)
	{
		if (sr.w.objects()[i]->shadowHit(ray, t))
			return true;
	}

	return false;
}

inline void Directional::setDirection(float x, float y, float z)
{
	direction_.set(x, y, z);
	direction_.normalize();
}

}

#endif
