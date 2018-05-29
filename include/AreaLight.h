#ifndef PMTRACER_AREALIGHT_H
#define PMTRACER_AREALIGHT_H

#include <memory>
#include "Light.h"

namespace pm {

class ShadeRecord;
class Geometry;
class Emissive;

class AreaLight: public Light
{
public:
	AreaLight();

	Vector3 direction(ShadeRecord &sr) const override;
	RGBColor L(ShadeRecord &sr) const override;
	bool inShadow(const Ray &ray, const ShadeRecord &sr) const override;

	float G(const ShadeRecord &sr) const override;
	float pdf(ShadeRecord &sr) const override;

	inline Geometry &object() const { return *object_; }
	inline void setObject(std::unique_ptr<Geometry> object) { object_ = std::move(object); }

	inline Emissive &material() const { return *material_; }
	inline void setMaterial(std::unique_ptr<Emissive> material) { material_ = std::move(material); }

private:
	std::unique_ptr<Geometry> object_;
	/// An emissive material
	std::unique_ptr<Emissive> material_;
	/// Sample point on the surface
	mutable Vector3 samplePoint_;
	/// Normal at sample point
	mutable Vector3 normal_;
	/// Unit vector from hit point to sampler point
	mutable Vector3 wi_;
};

}

#endif
