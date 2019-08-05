#ifndef PMTRACER_EMISSIVE_H
#define PMTRACER_EMISSIVE_H

#include "Material.h"

namespace pm {

class Emissive : public Material
{
  public:
	Emissive();

	inline float radianceScale() const { return ls_; }
	inline void setRadianceScale(float s) { ls_ = s; }

	inline void setCe(const RGBColor &color) { ce_ = color; }
	inline void setCe(float r, float g, float b) { ce_.set(r, g, b); }

	inline RGBColor le(ShadeRecord &sr) const { return (ls_ * ce_); }

	RGBColor areaLightShade(ShadeRecord &sr) const override;
	RGBColor pathShade(ShadeRecord &sr) const override;
	RGBColor globalShade(ShadeRecord &sr) const override;

	bool isEmissive() const override { return true; }

  private:
	float ls_;
	RGBColor ce_;
};

}

#endif
