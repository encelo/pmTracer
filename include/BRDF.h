#ifndef PMTRACER_BRDF_H
#define PMTRACER_BRDF_H

#include "RGBColor.h"
#include "SamplerState.h"
#include "Sampler.h"

namespace pm {

class ShadeRecord;
class Vector3;
class Sampler;

class BRDF
{
  public:
	virtual ~BRDF() {}

	virtual RGBColor f(const ShadeRecord &sr, const Vector3 &wo, const Vector3 &wi) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi, float &pdf) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor rho(const ShadeRecord &sr, const Vector3 &wo) const { return RGBColor(0.0f, 0.0f, 0.0f); }

	inline SamplerState &samplerState() { return samplerState_; }

	const Sampler *sampler() const { return samplerState_.sampler(); }
	Sampler *sampler() { return samplerState_.sampler(); }
	void setSampler(Sampler *sampler);

  protected:
	SamplerState samplerState_;
};

}

#endif
