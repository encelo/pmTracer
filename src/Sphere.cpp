#include <cmath>
#include "Sphere.h"

namespace pm {

bool Sphere::hit(const Ray &ray, float &tMin, ShadeRecord &sr) const
{
	bool hasHit = false;
	const Vector3 temp = ray.o - center_;
	const float a = dot(ray.d, ray.d);
	const float b = 2.0f * dot(temp, ray.d);
	const float c = dot(temp, temp) - radius_ * radius_;
	const float disc = b * b - 4.0f * a * c;

	if (disc > 0.0f)
	{
		float t = 0.0f;
		float e = sqrtf(disc);
		float denom = 2.0f * a;

		t = (-b - e) / denom; // smaller root
		if (t > Epsilon)
		{
			tMin = t;
			sr.normal = (temp + t * ray.d) / radius_;
			sr.localHitPoint = ray.o + t * ray.d;
			hasHit = true;
		}
		else
		{
			t = (-b + e) / denom; // larger root
			if (t > Epsilon)
			{
				tMin = t;
				sr.normal = (temp + t * ray.d) / radius_;
				sr.localHitPoint = ray.o + t * ray.d;
				hasHit = true;
			}
		}
	}

	return hasHit;
}

bool Sphere::shadowHit(const Ray &ray, float &tMin) const
{
	if (castShadows_ == false)
		return false;

	bool hasHit = false;
	const Vector3 temp = ray.o - center_;
	const float a = dot(ray.d, ray.d);
	const float b = 2.0f * dot(temp, ray.d);
	const float c = dot(temp, temp) - radius_ * radius_;
	const float disc = b * b - 4.0f * a * c;

	if (disc > 0.0f)
	{
		float t = 0.0f;
		const float e = sqrtf(disc);
		const float denom = 2.0f * a;

		t = (-b - e) / denom; // smaller root
		if (t > ShadowEpsilon)
		{
			tMin = t;
			hasHit = true;
		}
		else
		{
			t = (-b + e) / denom; // larger root
			if (t > ShadowEpsilon)
			{
				tMin = t;
				hasHit = true;
			}
		}
	}

	return hasHit;
}

}
