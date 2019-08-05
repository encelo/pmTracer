#include "Reflective.h"
#include "ShadeRecord.h"
#include "World.h"

namespace pm {

Reflective::Reflective()
    : Phong(), reflectiveBrdf_(std::make_unique<PerfectSpecular>())
{
}

RGBColor Reflective::shade(ShadeRecord &sr) const
{
	// direct illumination
	RGBColor L(Phong::shade(sr));

	const Vector3 wo = -sr.ray.d;
	Vector3 wi;
	RGBColor fr = reflectiveBrdf_->sampleF(sr, wo, wi);
	const float nDotWi = dot(sr.normal, wi);
	Ray reflectedRay(sr.hitPoint, wi);

	L += fr * sr.w.tracer().traceRay(reflectedRay, sr.depth + 1) * nDotWi;

	return L;
}

RGBColor Reflective::areaLightShade(ShadeRecord &sr) const
{
	// direct illumination
	RGBColor L(Phong::shade(sr));

	const Vector3 wo = -sr.ray.d;
	Vector3 wi;
	float pdf = 0.0f;
	const RGBColor fr = reflectiveBrdf_->sampleF(sr, wo, wi, pdf);
	const float nDotWi = dot(sr.normal, wi);
	Ray reflectedRay(sr.hitPoint, wi);

	L += fr * sr.w.tracer().traceRay(reflectedRay, sr.depth + 1) * nDotWi / pdf;

	return L;
}

RGBColor Reflective::pathShade(ShadeRecord &sr) const
{
	Vector3 wi;
	const Vector3 wo = -sr.ray.d;
	float pdf = 0.0f;
	const RGBColor fr = reflectiveBrdf_->sampleF(sr, wo, wi, pdf);
	const float nDotWi = dot(sr.normal, wi);
	Ray reflectedRay(sr.hitPoint, wi);

	return fr * sr.w.tracer().traceRay(reflectedRay, sr.depth + 1) * nDotWi / pdf;
}

RGBColor Reflective::globalShade(ShadeRecord &sr) const
{
	Vector3 wi;
	const Vector3 wo = -sr.ray.d;
	float pdf = 0.0f;
	const RGBColor fr = reflectiveBrdf_->sampleF(sr, wo, wi, pdf);
	const float nDotWi = dot(sr.normal, wi);
	Ray reflectedRay(sr.hitPoint, wi);

	if (sr.depth == 0)
		return fr * sr.w.tracer().traceRay(reflectedRay, sr.depth + 2) * nDotWi / pdf;
	else
		return fr * sr.w.tracer().traceRay(reflectedRay, sr.depth + 1) * nDotWi / pdf;
}

}
