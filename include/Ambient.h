#ifndef PMTRACER_AMBIENT_H
#define PMTRACER_AMBIENT_H

#include "Light.h"

namespace pm {

class ShadeRecord;

class Ambient : public Light
{
  public:
	Ambient()
	    : Light(), ls_(1.0f), color_(1.0f, 1.0f, 1.0f) {}
	Ambient(float ls)
	    : Light(), ls_(ls), color_(1.0f, 1.0f, 1.0f) {}
	Ambient(const RGBColor &color)
	    : Light(), ls_(1.0f), color_(color) {}
	Ambient(float r, float g, float b)
	    : Light(), ls_(1.0f), color_(r, g, b) {}

	inline Vector3 direction(ShadeRecord &sr) const override { return Vector3(0.0f, 0.0f, -1.0f); }
	inline RGBColor L(ShadeRecord &sr) const override { return (ls_ * color_); }
	inline bool inShadow(const Ray &ray, const ShadeRecord &sr) const override { return false; }

	inline float radianceScale() const { return ls_; }
	inline void setRadianceScale(float s) { ls_ = s; }

	inline const RGBColor &color() const { return color_; }
	inline void setColor(const RGBColor &color) { color_ = color; }
	inline void setColor(float r, float g, float b) { color_.set(r, g, b); }

  private:
	float ls_;
	RGBColor color_;
};

}

#endif
