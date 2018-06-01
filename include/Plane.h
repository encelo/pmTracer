#ifndef PMTRACER_PLANE_H
#define PMTRACER_PLANE_H

#include "Geometry.h"
#include "Vector3.h"
#include "Ray.h"

namespace pm {

class Plane : public Geometry
{
public:
	Plane() : Geometry(), point_(0.0f, 0.0f, 0.0f), normal_(0.0f, 1.0f, 0.0f) { }
	Plane(const Vector3 &point, const Vector3 &normal) : Geometry(), point_(point), normal_(normal) { }

	bool hit(const Ray &ray, float &tMin, ShadeRecord &sr) const override;
	bool shadowHit(const Ray &ray, float &tMin) const override;

	inline Vector3 normal(const Vector3 &point) const override { return normal_; }

private:
	static constexpr float Epsilon = 0.000000001f;
	static constexpr float ShadowEpsilon = 0.000000001f;

	Vector3 point_;
	Vector3 normal_;
};

}

#endif
