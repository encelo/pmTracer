#ifndef PMTRACER_AREALIGHT_H
#define PMTRACER_AREALIGHT_H

#include "Light.h"

namespace pm {

class ShadeRecord;
class Geometry;
class Emissive;

class AreaLight : public Light
{
  public:
	AreaLight(Geometry *object);

	Vector3 direction(ShadeRecord &sr) const override;
	RGBColor L(ShadeRecord &sr) const override;
	bool inShadow(const Ray &ray, const ShadeRecord &sr) const override;

	float G(const ShadeRecord &sr) const override;
	float pdf(ShadeRecord &sr) const override;

	inline Geometry &object() const { return *object_; }

  private:
	Geometry *object_;
	/// An emissive material
	const Emissive *material_;
	/// Sample point on the surface
	mutable Vector3 samplePoint_;
	/// Normal at sample point
	mutable Vector3 normal_;
	/// Unit vector from hit point to sampler point
	mutable Vector3 wi_;
};

}

#endif
