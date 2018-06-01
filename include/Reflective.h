#ifndef PMTRACER_REFLECTIVE_H
#define PMTRACER_REFLECTIVE_H

#include "Phong.h"
#include "PerfectSpecular.h"

namespace pm {

class Reflective : public Phong
{
public:
	Reflective();

	RGBColor shade(ShadeRecord &sr) const override;
	RGBColor areaLightShade(ShadeRecord &sr) const override;
	RGBColor pathShade(ShadeRecord &sr) const override;
	RGBColor globalShade(ShadeRecord &sr) const override;

private:
	std::unique_ptr<PerfectSpecular> reflectiveBrdf_;
};

}

#endif
