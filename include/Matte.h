#ifndef PMTRACER_MATTE_H
#define PMTRACER_MATTE_H

#include "Material.h"
#include "Lambertian.h"

namespace pm {

class Matte : public Material
{
  public:
	Matte();

	void setKa(float ka);
	void setKd(float kd);
	void setCd(const RGBColor &c);
	void setCd(float r, float g, float b);

	RGBColor shade(ShadeRecord &sr) const override;
	RGBColor areaLightShade(ShadeRecord &sr) const override;
	RGBColor pathShade(ShadeRecord &sr) const override;
	RGBColor globalShade(ShadeRecord &sr) const override;

	inline const Lambertian &ambient() const { return ambientBrdf_; }
	inline Lambertian &ambient() { return ambientBrdf_; }
	inline const Lambertian &diffuse() const { return diffuseBrdf_; }
	inline Lambertian &diffuse() { return diffuseBrdf_; }

  private:
	Lambertian ambientBrdf_;
	Lambertian diffuseBrdf_;
};

}

#endif
