#ifndef PMTRACER_PERFECTSPECULAR_H
#define PMTRACER_PERFECTSPECULAR_H

#include "BRDF.h"
#include "ShadeRecord.h"

namespace pm {

class PerfectSpecular : public BRDF
{
public:
	PerfectSpecular() : kr_(1.0f), cr_(1.0f, 1.0f, 1.0f) { }

	RGBColor sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi) const override;
	RGBColor sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi, float &pdf) const override;

	inline float kr() const { return kr_; }
	inline void setKr(float kr) { kr_ = kr; }

	inline const RGBColor &cr() const { return cr_; }
	inline void setCr(float r, float g, float b) { cr_.set(r, g, b); }
	inline void setCr(const RGBColor &color) { cr_ = color; }

private:
	float kr_;
	RGBColor cr_;
};

inline RGBColor PerfectSpecular::sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi) const
{
	const float nDotWo = dot(sr.normal, wo);
	wi = -wo + 2.0 * sr.normal * nDotWo;

	return (kr_ * cr_ / dot(sr.normal, wi));
}

inline RGBColor PerfectSpecular::sampleF(const ShadeRecord &sr, const Vector3 &wo, Vector3 &wi, float &pdf) const
{
	const float nDotWo = dot(sr.normal, wo);
	wi = -wo + 2.0 * sr.normal * nDotWo;
	pdf = dot(sr.normal, wi);

	return (kr_ * cr_);
}

}

#endif
