#ifndef PMTRACER_MATTE_H
#define PMTRACER_MATTE_H

#include <memory>
#include "Material.h"
#include "Lambertian.h"

namespace pm {

class Matte : public Material
{
public:
	Matte();

	void setKa(float ka);
	void setKd(float kd);
	void setCd(const RGBColor &color);
	void setCd(float r, float g, float b);

	RGBColor shade(ShadeRecord &sr) const override;
	RGBColor areaLightShade(ShadeRecord &sr) const override;
	RGBColor pathShade(ShadeRecord &sr) const override;
	RGBColor globalShade(ShadeRecord &sr) const override;

	inline Lambertian &ambient() { return *ambientBrdf_; }
	inline Lambertian &diffuse() { return *diffuseBrdf_; }

private:
	std::unique_ptr<Lambertian> ambientBrdf_;
	std::unique_ptr<Lambertian> diffuseBrdf_;
};

}

#endif
