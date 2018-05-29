#include "Emissive.h"
#include "ShadeRecord.h"
#include "World.h"

namespace pm {

Emissive::Emissive()
	: Material(), ls_(1.0f), ce_(1.0f, 1.0f, 1.0f)
{

}

RGBColor Emissive::areaLightShade(ShadeRecord &sr) const
{
	if (dot(-sr.normal, sr.ray.d) > 0.0)
		return (ls_ * ce_);
	else
		return RGBColor(0.0f, 0.0f, 0.0f);
}

RGBColor Emissive::pathShade(ShadeRecord &sr) const
{
	if (dot(-sr.normal, sr.ray.d) > 0.0)
		return (ls_ * ce_);
	else
		return RGBColor(0.0f, 0.0f, 0.0f);
}

}
