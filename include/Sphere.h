#ifndef PMTRACER_SPHERE_H
#define PMTRACER_SPHERE_H

#include "Geometry.h"

namespace pm {

class Sphere : public Geometry
{
public:
	Sphere() : Geometry(), center_(0.0f, 0.0f, 0.0f), radius_(1.0f) { }
	Sphere(const Vector3 &center, float radius) : Geometry(), center_(center), radius_(radius) { }

	bool hit(const Ray &ray, float &tMin, ShadeRecord &sr) const override;
	bool shadowHit(const Ray &ray, float &tMin) const override;

	inline Vector3 normal(const Vector3 &point) const override { return (point - center_).normalize(); }

	inline void setCenter(float x, float y, float z) { center_.set(x, y, z); }
	inline void setRadius(float radius) { radius_ = radius; }

private:
	static constexpr float Epsilon = 0.000000001f;
	static constexpr float ShadowEpsilon = 0.000000001f;

	Vector3 center_;
	float radius_;
};

}

#endif
