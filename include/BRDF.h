#ifndef PMTRACER_BRDF_H
#define PMTRACER_BRDF_H

#include <memory>
#include "RGBColor.h"
#include "Sampler.h"

namespace pm {

class ShadeRecord;
class Vector3;

class BRDF
{
public:
	virtual ~BRDF() { }

	virtual RGBColor f(const ShadeRecord &sr, const Vector3 &wo, const Vector3 &wi) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor sampleF(const ShadeRecord &sr, const Vector3& wo, Vector3& wi, float& pdf) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor rho(const ShadeRecord &sr, const Vector3 &wo) const { return RGBColor(0.0f, 0.0f, 0.0f); }

	inline Sampler &sampler() const { return *sampler_; }
	inline void setSampler(std::unique_ptr<Sampler> sampler) { sampler_ = std::move(sampler); }

protected:
	std::unique_ptr<Sampler> sampler_;
};

}

#endif
