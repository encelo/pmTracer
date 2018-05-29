#include <cmath>
#include "Sphere.h"

namespace pm {

bool Sphere::hit(const Ray &ray, double &tMin, ShadeRecord &sr) const
{
	bool hasHit = false;
	double t = 0.0;
	Vector3 temp = ray.o - center_;
	double a = dot(ray.d, ray.d);
	double b = 2.0 * dot(temp, ray.d);
	double c = dot(temp, temp) - radius_ * radius_;
	double disc = b * b - 4.0 * a * c;

	if (disc > 0.0)
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;

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

bool Sphere::shadowHit(const Ray &ray, double &tMin) const
{
	if (castShadows_ == false)
		return false;

	bool hasHit = false;
	double t = 0.0;
	Vector3 temp = ray.o - center_;
	double a = dot(ray.d, ray.d);
	double b = 2.0 * dot(temp, ray.d);
	double c = dot(temp, temp) - radius_ * radius_;
	double disc = b * b - 4.0 * a * c;

	if (disc > 0.0)
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;

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
