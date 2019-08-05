#include "AmbientOccluder.h"
#include "Sampler.h"
#include "World.h"
#include "Regular.h"
#include "Geometry.h"
#include "Sampler.h"

namespace pm {

AmbientOccluder::AmbientOccluder()
    : Light(), u_(1.0f, 0.0f, 0.0f), v_(0.0f, 1.0f, 0.0f), w_(0.0f, 0.0f, 1.0f),
      ls_(1.0f), color_(1.0f, 1.0f, 1.0f), minAmount_(1.0f)
{
}

Vector3 AmbientOccluder::direction(ShadeRecord &sr) const
{
	Vector3 sp = samplerState_.sampleHemisphere();
	return Vector3(sp.x * u_ + sp.y * w_ + sp.z * w_);
}

RGBColor AmbientOccluder::L(ShadeRecord &sr) const
{
	w_ = sr.normal;
	// jitter the up vector in case normal is vertical
	v_ = cross(w_, Vector3(0.0072f, 1.0f, 0.0034f));
	v_.normalize();
	u_ = cross(v_, w_);

	Ray shadowRay(sr.hitPoint, direction(sr));

	if (inShadow(shadowRay, sr))
		return (minAmount_ * ls_ * color_);
	else
		return (ls_ * color_);
}

inline bool AmbientOccluder::inShadow(const Ray &ray, const ShadeRecord &sr) const
{
	float t;
	const size_t numObjects = sr.w.objects().size();

	for (int i = 0; i < numObjects; i++)
	{
		if (sr.w.objects()[i]->shadowHit(ray, t))
			return true;
	}

	return false;
}

void AmbientOccluder::setSampler(Sampler *sampler)
{
	samplerState_.setSampler(sampler);
	sampler->mapSamplesToHemisphere(1.0f);
}

}
