#ifndef PMTRACER_GLOSSYSPECULAR_H
#define PMTRACER_GLOSSYSPECULAR_H

#include "BRDF.h"
#include "ShadeRecord.h"

namespace pm {

class GlossySpecular : public BRDF
{
public:
	GlossySpecular() : ks_(1.0f), cs_(1.0f, 1.0f, 1.0f), exp_(1.0f) { }

	RGBColor f(const ShadeRecord &sr, const Vector3 &wi, const Vector3 &wo) const override;

	inline float ks() const { return ks_; }
	inline void setKs(float ks) { ks_ = ks; }

	inline const RGBColor &cs() const { return cs_; }
	inline void setCs(float r, float g, float b) { cs_.set(r, g, b); }
	inline void setCs(const RGBColor &color) { cs_ = color; }

	inline float exp() const { return exp_; }
	inline void setExp(float exp) { exp_ = exp; }

private:
	float ks_;
	/// Specular color
	RGBColor cs_;
	/// Specular exponent
	float exp_;
};

inline RGBColor GlossySpecular::f(const ShadeRecord &sr, const Vector3 &wi, const Vector3 &wo) const
{
	RGBColor L;
	const float nDotWi = dot(sr.normal, wi);
	Vector3 r(-wi + 2.0 * sr.normal * nDotWi);
	const float rDotWo = dot(r, wo);

	if (rDotWo > 0.0)
		L = ks_ * cs_ * pow(rDotWo, exp_);

	return L;
}

}

#endif
