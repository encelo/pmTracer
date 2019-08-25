#ifndef PMTRACER_MATERIAL_H
#define PMTRACER_MATERIAL_H

#include "RGBColor.h"

namespace pm {

class ShadeRecord;

class Material
{
  public:
	enum class Type
	{
		MATTE,
		PHONG,
		EMISSIVE
	};

	explicit Material(Type type)
	    : type_(type) {}
	virtual ~Material() {}

	inline Type type() const { return type_; }

	virtual RGBColor shade(ShadeRecord &sr) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor areaLightShade(ShadeRecord &sr) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor pathShade(ShadeRecord &sr) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor globalShade(ShadeRecord &sr) const { return RGBColor(0.0f, 0.0f, 0.0f); }

  private:
	Type type_;
};

}

#endif
