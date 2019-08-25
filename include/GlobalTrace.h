#ifndef PMTRACER_GLOBALTRACE_H
#define PMTRACER_GLOBALTRACE_H

#include "Tracer.h"

namespace pm {

class GlobalTrace : public Tracer
{
  public:
	GlobalTrace()
	    : Tracer(Type::GLOBALTRACE) {}

	RGBColor traceRay(const World &world, const Ray &ray, int depth) const override;
};

}

#endif
