#include "Plane.h"

namespace pm {

bool Plane::hit(const Ray &ray, float &tMin, ShadeRecord &sr) const
{
	bool hasHit = false;
	const float t = dot((point_ - ray.o), normal_) / dot(ray.d, normal_);

	if (t > Epsilon)
	{
		tMin = t;
		sr.normal = normal_;
		sr.localHitPoint = ray.o + t * ray.d;

		hasHit = true;
	}

	return hasHit;
}

bool Plane::shadowHit(const Ray &ray, float &tMin) const
{
	if (castShadows_ == false)
		return false;

	bool hasHit = false;
	const float t = dot((point_ - ray.o), normal_) / dot(ray.d, normal_);

	if (t > ShadowEpsilon)
	{
		tMin = t;
		hasHit = true;
	}

	return hasHit;
}

}
