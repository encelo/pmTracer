#include "EnvironmentLight.h"
#include "Emissive.h"
#include "ShadeRecord.h"
#include "World.h"
#include "MultiJittered.h"

namespace pm {

EnvironmentLight::EnvironmentLight()
	: sampler_(std::make_unique<MultiJittered>(16)), material_(std::make_unique<Emissive>()),
	  u_(1.0, 0.0, 0.0), v_(0.0, 1.0, 0.0), w_(0.0, 0.0, 1.0)
{
	sampler_->mapSamplesToHemisphere(1.0f);
}

Vector3 EnvironmentLight::direction(ShadeRecord &sr) const
{
	w_ = sr.normal;
	v_ = cross(Vector3(0.0034, 1, 0.0071), w_);
	v_.normalize();
	u_ = cross(v_, w_);
	Vector3 sp = sampler_->sampleHemisphere();
	wi_ = sp.x * u_ + sp.y * v_ + sp.z * w_;

	return wi_;
}

RGBColor EnvironmentLight::L(ShadeRecord &sr) const
{
	return material_->le(sr);
}


bool EnvironmentLight::inShadow(const Ray &ray, const ShadeRecord &sr) const
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

}
