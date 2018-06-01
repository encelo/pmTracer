#include "Matte.h"
#include "ShadeRecord.h"
#include "World.h"

namespace pm {

Matte::Matte()
	: Material(), ambientBrdf_(std::make_unique<Lambertian>()),
	  diffuseBrdf_(std::make_unique<Lambertian>())
{

}

void Matte::setKa(float ka)
{
	ambientBrdf_->setKd(ka);
}

void Matte::setKd(float kd)
{
	diffuseBrdf_->setKd(kd);
}

void Matte::setCd(const RGBColor &c)
{
	ambientBrdf_->setCd(c);
	diffuseBrdf_->setCd(c);
}

void Matte::setCd(float r, float g, float b)
{
	ambientBrdf_->setCd(r, g, b);
	diffuseBrdf_->setCd(r, g, b);
}

RGBColor Matte::shade(ShadeRecord &sr) const
{
	const Vector3 wo = -sr.ray.d;
	RGBColor L = ambientBrdf_->rho(sr, wo) * sr.w.ambientLight().L(sr);
	const size_t numLights = sr.w.lights().size();

	for (unsigned int i = 0; i < numLights; i++)
	{
		const Light &light = *sr.w.lights()[i];
		const Vector3 wi = light.direction(sr);
		const float nDotWi = dot(sr.normal, wi);

		if (nDotWi > 0.0f)
		{
			bool inShadow = false;

			if (light.castShadows())
			{
				Ray shadowRay(sr.hitPoint, wi);
				inShadow = light.inShadow(shadowRay, sr);
			}

			if (inShadow == false)
				L += diffuseBrdf_->f(sr, wo, wi) * light.L(sr) * nDotWi;
		}
	}

	return L;
}

RGBColor Matte::areaLightShade(ShadeRecord &sr) const
{
	const Vector3 wo = -sr.ray.d;
	RGBColor L = ambientBrdf_->rho(sr, wo) * sr.w.ambientLight().L(sr);
	const size_t numLights = sr.w.lights().size();

	for (unsigned int i = 0; i < numLights; i++)
	{
		const Light &light = *sr.w.lights()[i];
		const Vector3 wi = light.direction(sr);
		const float nDotWi = dot(sr.normal, wi);

		if (nDotWi > 0.0f)
		{
			bool inShadow = false;

			if (light.castShadows())
			{
				Ray shadowRay(sr.hitPoint, wi);
				inShadow = light.inShadow(shadowRay, sr);
			}

			if (inShadow == false)
				L += diffuseBrdf_->f(sr, wo, wi) * light.L(sr) * light.G(sr) * nDotWi / light.pdf(sr);
		}
	}

	return L;
}

RGBColor Matte::pathShade(ShadeRecord &sr) const
{
	Vector3 wi;
	const Vector3 wo = -sr.ray.d;
	float pdf = 0.0f;
	const RGBColor f = diffuseBrdf_->sampleF(sr, wo, wi, pdf);
	const float nDotWi = dot(sr.normal, wi);
	Ray reflectedRay(sr.hitPoint, wi);

	return (f * sr.w.tracer().traceRay(reflectedRay, sr.depth + 1) * nDotWi / pdf);
}

RGBColor Matte::globalShade(ShadeRecord &sr) const
{
	RGBColor L;

	if (sr.depth == 0)
		L = areaLightShade(sr);

	Vector3 wi;
	const Vector3 wo = -sr.ray.d;
	float pdf = 0.0f;
	RGBColor f = diffuseBrdf_->sampleF(sr, wo, wi, pdf);
	const float nDotWi = dot(sr.normal, wi);
	Ray reflectedRay(sr.hitPoint, wi);

	L += f * sr.w.tracer().traceRay(reflectedRay, sr.depth + 1) * nDotWi / pdf;

	return L;
}

}
