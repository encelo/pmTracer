#ifndef PMTRACER_GLOBALTRACE_H
#define PMTRACER_GLOBALTRACE_H

#include "Tracer.h"

namespace pm {

class GlobalTrace : public Tracer
{
  public:
	GlobalTrace(World &world)
	    : Tracer(world) {}

	RGBColor traceRay(const Ray &ray, int depth) const override;
};

}

#endif
