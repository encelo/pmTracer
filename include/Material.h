#ifndef PMTRACER_MATERIAL_H
#define PMTRACER_MATERIAL_H

#include "RGBColor.h"

namespace pm {

class ShadeRecord;

class Material
{
public:
	virtual ~Material() { }

	virtual RGBColor shade(ShadeRecord &sr) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor areaLightShade(ShadeRecord &sr) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor pathShade(ShadeRecord &sr) const { return RGBColor(0.0f, 0.0f, 0.0f); }
};

}

#endif
