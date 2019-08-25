#ifndef PMTRACER_PHONG_H
#define PMTRACER_PHONG_H

#include <memory>
#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

namespace pm {

class Phong : public Material
{
  public:
	Phong();

	void setKa(float ka);
	void setKd(float kd);
	void setKs(float ks);
	void setSpecularExp(float exp);
	void setCd(const RGBColor &c);
	void setCd(float r, float g, float b);
	void setCs(const RGBColor &c);
	void setCs(float r, float g, float b);

	RGBColor shade(ShadeRecord &sr) const override;
	RGBColor areaLightShade(ShadeRecord &sr) const override;
	RGBColor pathShade(ShadeRecord &sr) const override;

	inline const Lambertian &ambient() const { return ambientBrdf_; }
	inline Lambertian &ambient() { return ambientBrdf_; }
	inline const Lambertian &diffuse() const { return diffuseBrdf_; }
	inline Lambertian &diffuse() { return diffuseBrdf_; }
	inline const GlossySpecular &specular() const { return specularBrdf_; }
	inline GlossySpecular &specular() { return specularBrdf_; }

  private:
	Lambertian ambientBrdf_;
	Lambertian diffuseBrdf_;
	GlossySpecular specularBrdf_;
};

}

#endif
