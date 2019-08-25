#include "Phong.h"
#include "ShadeRecord.h"
#include "World.h"
#include "Tracer.h"

namespace pm {

Phong::Phong()
    : Material(Type::PHONG)
{
}

void Phong::setKa(float ka)
{
	ambientBrdf_.setKd(ka);
}

void Phong::setKd(float kd)
{
	diffuseBrdf_.setKd(kd);
}

void Phong::setKs(float ks)
{
	specularBrdf_.setKs(ks);
}

void Phong::setSpecularExp(float exp)
{
	specularBrdf_.setExp(exp);
}

void Phong::setCd(const RGBColor &c)
{
	ambientBrdf_.setCd(c);
	diffuseBrdf_.setCd(c);
}

void Phong::setCd(float r, float g, float b)
{
	ambientBrdf_.setCd(r, g, b);
	diffuseBrdf_.setCd(r, g, b);
}

void Phong::setCs(const RGBColor &c)
{
	specularBrdf_.setCs(c);
}

void Phong::setCs(float r, float g, float b)
{
	specularBrdf_.setCs(r, g, b);
}

RGBColor Phong::shade(ShadeRecord &sr) const
{
	const Vector3 wo = -sr.ray.d;
	RGBColor L = ambientBrdf_.rho(sr, wo) * sr.world.ambientLight().L(sr);
	const size_t numLights = sr.world.lights().size();

	for (unsigned int i = 0; i < numLights; i++)
	{
		const Light &light = *sr.world.lights()[i];
		Vector3 wi = light.direction(sr);
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
				L += (diffuseBrdf_.f(sr, wo, wi) + specularBrdf_.f(sr, wo, wi)) * light.L(sr) * nDotWi;
		}
	}

	return L;
}

RGBColor Phong::areaLightShade(ShadeRecord &sr) const
{
	const Vector3 wo = -sr.ray.d;
	RGBColor L = ambientBrdf_.rho(sr, wo) * sr.world.ambientLight().L(sr);
	const size_t numLights = sr.world.lights().size();

	for (unsigned int i = 0; i < numLights; i++)
	{
		const Light &light = *sr.world.lights()[i];
		Vector3 wi = light.direction(sr);
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
				L += (diffuseBrdf_.f(sr, wo, wi) + specularBrdf_.f(sr, wo, wi)) * light.L(sr) * light.G(sr) * nDotWi / light.pdf(sr);
		}
	}

	return L;
}

RGBColor Phong::pathShade(ShadeRecord &sr) const
{
	Vector3 wi;
	const Vector3 wo = -sr.ray.d;
	float pdf = 0.0f;
	const RGBColor f = diffuseBrdf_.sampleF(sr, wo, wi, pdf);
	float nDotWi = dot(sr.normal, wi);
	Ray reflectedRay(sr.hitPoint, wi);

	return (f * sr.tracer.traceRay(sr.world, reflectedRay, sr.depth + 1) * nDotWi / pdf);
}

}
