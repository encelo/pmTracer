#ifndef PMTRACER_AMBIENTOCCLUDER_H
#define PMTRACER_AMBIENTOCCLUDER_H

#include "Light.h"
#include "ShadeRecord.h"
#include "SamplerState.h"

namespace pm {

class Sampler;

class AmbientOccluder : public Light
{
  public:
	AmbientOccluder();

	Vector3 direction(ShadeRecord &sr) const override;
	RGBColor L(ShadeRecord &sr) const override;
	bool inShadow(const Ray &ray, const ShadeRecord &sr) const override;

	inline float radianceScale() const { return ls_; }
	inline float &editRadianceScale() { return ls_; }
	inline void setRadianceScale(float s) { ls_ = s; }

	inline const RGBColor &color() const { return color_; }
	inline RGBColor &editColor() { return color_; }
	inline void setColor(const RGBColor &color) { color_ = color; }
	inline void setColor(float r, float g, float b) { color_.set(r, g, b); }

	inline const RGBColor &minAmount() const { return minAmount_; }
	inline RGBColor &editMinAmount() { return minAmount_; }
	inline void setMinAmount(const RGBColor &minAmount) { minAmount_ = minAmount; }
	inline void setMinAmount(float r, float g, float b) { minAmount_.set(r, g, b); }

	inline const SamplerState &samplerState() const { return samplerState_; }

	const Sampler *sampler() const { return samplerState_.sampler(); }
	void setSampler(Sampler *sampler);

  private:
	mutable Vector3 u_;
	mutable Vector3 v_;
	mutable Vector3 w_;

	float ls_;
	RGBColor color_;
	RGBColor minAmount_;

	SamplerState samplerState_;
};

}

#endif
