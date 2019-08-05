#include "AreaLight.h"
#include "Rectangle.h"
#include "Emissive.h"
#include "ShadeRecord.h"
#include "World.h"

namespace pm {

AreaLight::AreaLight(Geometry *object)
    : object_(object), material_(static_cast<const Emissive *>(object->material()))
{
}

Vector3 AreaLight::direction(ShadeRecord &sr) const
{
	samplePoint_ = object_->sample();
	normal_ = object_->normal(samplePoint_);
	wi_ = samplePoint_ - sr.hitPoint;
	wi_.normalize();

	return wi_;
}

RGBColor AreaLight::L(ShadeRecord &sr) const
{
	const float nDotD = dot(-normal_, wi_);

	if (nDotD > 0.0f)
		return material_->le(sr);
	else
		return RGBColor(0.0f, 0.0f, 0.0f);
}

bool AreaLight::inShadow(const Ray &ray, const ShadeRecord &sr) const
{
	float t = 0.0;
	const size_t numObjects = sr.w.objects().size();
	float ts = dot((samplePoint_ - ray.o), ray.d);

	for (unsigned int i = 0; i < numObjects; i++)
	{
		if (sr.w.objects()[i]->shadowHit(ray, t) && t < ts)
			return true;
	}

	return false;
}

float AreaLight::G(const ShadeRecord &sr) const
{
	const float nDotD = dot(-normal_, wi_);
	const float d2 = (samplePoint_ - sr.hitPoint).sqrLength();

	return nDotD / d2;
}

float AreaLight::pdf(ShadeRecord &sr) const
{
	return object_->pdf(sr);
}

}
