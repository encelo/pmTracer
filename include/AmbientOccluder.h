#ifndef PMTRACER_AMBIENTOCCLUDER_H
#define PMTRACER_AMBIENTOCCLUDER_H

#include <memory>
#include "Light.h"
#include "ShadeRecord.h"

namespace pm {

class Sampler;

class AmbientOccluder: public Light
{
public:
	AmbientOccluder();

	Vector3 direction(ShadeRecord &sr) const override;
	RGBColor L(ShadeRecord &sr) const override;
	bool inShadow(const Ray &ray, const ShadeRecord &sr) const override;

	inline float radianceScale() const { return ls_; }
	inline void setRadianceScale(float s) { ls_ = s; }

	inline const RGBColor &color() const { return color_; }
	inline void setColor(const RGBColor &color) { color_ = color; }
	inline void setColor(float r, float g, float b) { color_.set(r, g, b); }

	inline const float &minAmount() const { return minAmount_; }
	inline void setMinAmount(float minAmount) { minAmount_ = minAmount; }

	inline Sampler &sampler() const { return *sampler_; }
	void setSampler(std::unique_ptr<Sampler> sampler);

private:
	mutable Vector3 u_;
	mutable Vector3 v_;
	mutable Vector3 w_;

	float ls_;
	RGBColor color_;
	float minAmount_;

	std::unique_ptr<Sampler> sampler_;
};

}

#endif
