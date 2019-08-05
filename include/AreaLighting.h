#ifndef PMTRACER_AREALIGHTING_H
#define PMTRACER_AREALIGHTING_H

#include "Tracer.h"

namespace pm {

class AreaLighting : public Tracer
{
  public:
	AreaLighting(World &world)
	    : Tracer(world) {}

	RGBColor traceRay(const Ray &ray, int depth) const override;
};

}

#endif
