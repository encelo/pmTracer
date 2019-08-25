#ifndef PMTRACER_SPHERE_H
#define PMTRACER_SPHERE_H

#include "Geometry.h"

namespace pm {

class Sphere : public Geometry
{
  public:
	Sphere()
	    : Sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f) {}
	Sphere(const Vector3 &center, float radius)
	    : Geometry(Type::SPHERE), center_(center), radius_(radius) {}

	bool hit(const Ray &ray, float &tMin, ShadeRecord &sr) const override;
	bool shadowHit(const Ray &ray, float &tMin) const override;

	inline Vector3 normal(const Vector3 &point) const override { return (point - center_).normalize(); }

	inline const Vector3 &center() const { return center_; }
	inline Vector3 &editCenter() { return center_; }
	inline void setCenter(float x, float y, float z) { center_.set(x, y, z); }
	inline float radius() const { return radius_; }
	inline float &editRadius() { return radius_; }
	inline void setRadius(float radius) { radius_ = radius; }

  private:
	static constexpr float Epsilon = 0.000000001f;
	static constexpr float ShadowEpsilon = 0.000000001f;

	Vector3 center_;
	float radius_;
};

}

#endif
