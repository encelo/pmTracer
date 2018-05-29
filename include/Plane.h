#ifndef PMTRACER_PLANE_H
#define PMTRACER_PLANE_H

#include "Geometry.h"
#include "Vector3.h"
#include "Ray.h"

namespace pm {

class Plane : public Geometry
{
public:
	Plane() : Geometry(), point_(0.0, 0.0, 0.0), normal_(0.0, 1.0, 0.0) { }
	Plane(const Vector3 &point, const Vector3 &normal) : Geometry(), point_(point), normal_(normal) { }

	bool hit(const Ray &ray, double &tMin, ShadeRecord &sr) const override;
	bool shadowHit(const Ray &ray, double &tMin) const override;

	inline Vector3 normal(const Vector3 &point) const override { return normal_; }

private:
	static constexpr double Epsilon = 0.000000001;
	static constexpr double ShadowEpsilon = 0.000000001;

	Vector3 point_;
	Vector3 normal_;
};

}

#endif
