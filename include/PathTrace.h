#ifndef PMTRACER_PATHTRACE_H
#define PMTRACER_PATHTRACE_H

#include "Tracer.h"

namespace pm {

class PathTrace : public Tracer
{
  public:
	PathTrace(World &world)
	    : Tracer(world) {}

	RGBColor traceRay(const Ray &ray, int depth) const override;
};

}

#endif
