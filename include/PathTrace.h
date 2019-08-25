#ifndef PMTRACER_PATHTRACE_H
#define PMTRACER_PATHTRACE_H

#include "Tracer.h"

namespace pm {

class PathTrace : public Tracer
{
  public:
	PathTrace()
	    : Tracer(Type::PATHTRACE) {}

	RGBColor traceRay(const World &world, const Ray &ray, int depth) const override;
};

}

#endif
