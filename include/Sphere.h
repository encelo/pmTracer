#ifndef PMTRACER_SPHERE_H
#define PMTRACER_SPHERE_H

#include "Geometry.h"

namespace pm {

class Sphere : public Geometry
{
public:
	Sphere() : Geometry(), center_(0.0, 0.0, 0.0), radius_(1.0) { }
	Sphere(const Vector3 &center, double radius) : Geometry(), center_(center), radius_(radius) { }

	bool hit(const Ray &ray, double &tMin, ShadeRecord &sr) const override;
	bool shadowHit(const Ray &ray, double &tMin) const override;

	inline Vector3 normal(const Vector3 &point) const override { return (point - center_).normalize(); }

	inline void setCenter(double x, double y, double z) { center_.set(x, y, z); }
	inline void setRadius(double radius) { radius_ = radius; }

private:
	static constexpr double Epsilon = 0.000000001;
	static constexpr double ShadowEpsilon = 0.000000001;

	Vector3 center_;
	double radius_;
};

}

#endif
