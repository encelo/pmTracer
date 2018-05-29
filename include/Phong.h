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
	void setCd(const RGBColor &color);
	void setCd(float r, float g, float b);
	void setCs(const RGBColor &color);
	void setCs(float r, float g, float b);

	RGBColor shade(ShadeRecord &sr) const override;
	RGBColor areaLightShade(ShadeRecord &sr) const override;
	RGBColor pathShade(ShadeRecord &sr) const;

	inline Lambertian &ambient() { return *ambientBrdf_; }
	inline Lambertian &diffuse() { return *diffuseBrdf_; }
	inline GlossySpecular &specular() { return *specularBrdf_; }

private:
	std::unique_ptr<Lambertian> ambientBrdf_;
	std::unique_ptr<Lambertian> diffuseBrdf_;
	std::unique_ptr<GlossySpecular> specularBrdf_;
};

}

#endif
