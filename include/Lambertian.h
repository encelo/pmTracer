#ifndef PMTRACER_LAMBERTIAN_H
#define PMTRACER_LAMBERTIAN_H

#include "BRDF.h"
#include "ShadeRecord.h"

const float invPi = 1.0 / 3.14159265358979323846;

namespace pm {

class Lambertian : public BRDF
{
public:
	Lambertian() : kd_(1.0f), cd_(1.0f, 1.0f, 1.0f) { }

	RGBColor f(const ShadeRecord &sr, const Vector3 &wo, const Vector3 &wi) const override;
	RGBColor sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi, float &pdf) const override;
	RGBColor rho(const ShadeRecord &sr, const Vector3 &wo) const override;

	inline float kd() const { return kd_; }
	inline void setKd(float kd) { kd_ = kd; }

	inline const RGBColor &cd() const { return cd_; }
	inline void setCd(float r, float g, float b) { cd_.set(r, g, b); }
	inline void setCd(const RGBColor &color) { cd_ = color; }

private:
	float kd_;
	RGBColor cd_;
};

inline RGBColor Lambertian::f(const ShadeRecord &sr, const Vector3 &wo, const Vector3 &wi) const
{
	return (kd_ * cd_ * invPi);
}

inline RGBColor Lambertian::sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
	Vector3 w = sr.normal;
	// up vector jittering
	Vector3 v = cross(Vector3(0.0034, 1, 0.0071), w);
	v.normalize();
	Vector3 u = cross(v, w);

	Vector3 sp = samplerState_.sampleHemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();

	pdf = dot(sr.normal, wi) * invPi;

	return (kd_ * cd_ * invPi);
}

inline RGBColor Lambertian::rho(const ShadeRecord &sr, const Vector3 &wo) const
{
	return (kd_ * cd_);
}

}

#endif
