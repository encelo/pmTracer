#include "AmbientOccluder.h"
#include "Sampler.h"
#include "World.h"
#include "Regular.h"
#include "Geometry.h"

namespace pm {

AmbientOccluder::AmbientOccluder()
	: Light(), u_(1.0, 0.0, 0.0), v_(0.0, 1.0, 0.0), w_(0.0, 0.0, 1.0),
	  ls_(1.0f), color_(1.0f, 1.0f, 1.0), minAmount_(1.0f),
	  sampler_(std::make_unique<Regular>(1))
{

}

Vector3 AmbientOccluder::direction(ShadeRecord &sr) const
{
	Vector3 sp = sampler_->sampleHemisphere();
	return Vector3(sp.x * u_ + sp.y * w_ + sp.z * w_);
}

RGBColor AmbientOccluder::L(ShadeRecord &sr) const
{
	w_ = sr.normal;
	// jitter the up vector in case normal is vertical
	v_ = cross(w_, Vector3(0.0072, 1.0, 0.0034));
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
	double t;
	const size_t numObjects = sr.w.objects().size();

	for (int i = 0; i < numObjects; i++)
	{
		if (sr.w.objects()[i]->shadowHit(ray, t))
			return true;
	}

	return false;
}

void AmbientOccluder::setSampler(std::unique_ptr<Sampler> sampler)
{
	sampler_ = std::move(sampler);
	sampler_->mapSamplesToHemisphere(1.0f);
}

}
