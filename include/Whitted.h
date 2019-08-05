#ifndef PMTRACER_WHITTED_H
#define PMTRACER_WHITTED_H

#include "Tracer.h"

namespace pm {

class Whitted : public Tracer
{
  public:
	Whitted(World &world)
	    : Tracer(world) {}

	RGBColor traceRay(const Ray &ray, int depth) const override;
};

}

#endif
