#ifndef PMTRACER_ENVIRONMENTLIGHT_H
#define PMTRACER_ENVIRONMENTLIGHT_H

#include <memory>
#include "Light.h"
#include "SamplerState.h"

namespace pm {

class ShadeRecord;
class Sampler;
class Emissive;

class EnvironmentLight: public Light
{
public:
	EnvironmentLight();

	Vector3 direction(ShadeRecord &sr) const override;
	RGBColor L(ShadeRecord &sr) const override;
	bool inShadow(const Ray &ray, const ShadeRecord &sr) const override;

	inline const SamplerState &sampler() const { return samplerState_; }
	inline void setSampler(Sampler *sampler);

	inline Emissive &material() const { return *material_; }
	inline void setMaterial(std::unique_ptr<Emissive> material) { material_ = std::move(material); }

private:
	SamplerState samplerState_;
	/// An emissive material
	std::unique_ptr<Emissive> material_;
	mutable Vector3 u_;
	mutable Vector3 v_;
	mutable Vector3 w_;
	/// Unit vector from hit point to sampler point
	mutable Vector3 wi_;
};

}

#endif
