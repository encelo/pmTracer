#include "EnvironmentLight.h"
#include "Emissive.h"
#include "ShadeRecord.h"
#include "World.h"
#include "Geometry.h"
#include "MultiJittered.h"

namespace pm {

EnvironmentLight::EnvironmentLight(Emissive *material)
    : material_(material),
      u_(1.0f, 0.0f, 0.0f), v_(0.0f, 1.0f, 0.0f), w_(0.0f, 0.0f, 1.0f)
{
}

Vector3 EnvironmentLight::direction(ShadeRecord &sr) const
{
	w_ = sr.normal;
	v_ = cross(Vector3(0.0034f, 1.0f, 0.0071f), w_);
	v_.normalize();
	u_ = cross(v_, w_);
	Vector3 sp = samplerState_.sampleHemisphere();
	wi_ = sp.x * u_ + sp.y * v_ + sp.z * w_;

	return wi_;
}

RGBColor EnvironmentLight::L(ShadeRecord &sr) const
{
	return material_->le(sr);
}

bool EnvironmentLight::inShadow(const Ray &ray, const ShadeRecord &sr) const
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

void EnvironmentLight::setSampler(Sampler *sampler)
{
	samplerState_.setSampler(sampler);
	sampler->mapSamplesToHemisphere(1.0f);
}

}
