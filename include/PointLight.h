#ifndef PMTRACER_POINTLIGHT_H
#define PMTRACER_POINTLIGHT_H

#include "Light.h"
#include "ShadeRecord.h"
#include "World.h"

namespace pm {

class PointLight : public Light
{
  public:
	PointLight()
	    : PointLight(0.0f, 0.0f, 0.0f) {}
	PointLight(float x, float y, float z)
	    : Light(Type::POINT), ls_(1.0f), color_(1.0f, 1.0f, 1.0f), location_(x, y, z) {}

	inline Vector3 direction(ShadeRecord &sr) const override { return (location_ - sr.hitPoint).normalize(); }
	inline RGBColor L(ShadeRecord &sr) const override { return (ls_ * color_); }
	bool inShadow(const Ray &ray, const ShadeRecord &sr) const override;

	inline float radianceScale() const { return ls_; }
	inline float &editRadianceScale() { return ls_; }
	inline void setRadianceScale(float s) { ls_ = s; }

	inline const RGBColor &color() const { return color_; }
	inline RGBColor &editColor() { return color_; }
	inline void setColor(const RGBColor &color) { color_ = color; }
	inline void setColor(float r, float g, float b) { color_.set(r, g, b); }

	inline const Vector3 &location() const { return location_; }
	inline Vector3 &editLocation() { return location_; }
	inline void setLocation(const Vector3 &location) { location_ = location; }
	inline void setLocation(float x, float y, float z) { location_.set(x, y, z); }

  private:
	float ls_;
	RGBColor color_;
	Vector3 location_;
};

inline bool PointLight::inShadow(const Ray &ray, const ShadeRecord &sr) const
{
	float t;
	const size_t numObjects = sr.world.objects().size();
	float d = (location_ - ray.o).length();

	for (unsigned int i = 0; i < numObjects; i++)
	{
		if (sr.world.objects()[i]->shadowHit(ray, t) && t < d)
			return true;
	}

	return false;
}

}

#endif
