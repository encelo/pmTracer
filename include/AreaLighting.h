#ifndef PMTRACER_AREALIGHTING_H
#define PMTRACER_AREALIGHTING_H

#include "Tracer.h"

namespace pm {

class AreaLighting : public Tracer
{
  public:
	AreaLighting()
	    : Tracer(Type::AREALIGHTING) {}

	RGBColor traceRay(const World &world, const Ray &ray, int depth) const override;
};

}

#endif
