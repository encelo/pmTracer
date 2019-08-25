#ifndef PMTRACER_WHITTED_H
#define PMTRACER_WHITTED_H

#include "Tracer.h"

namespace pm {

class Whitted : public Tracer
{
  public:
	Whitted()
	    : Tracer(Type::WHITTED) {}

	RGBColor traceRay(const World &world, const Ray &ray, int depth) const override;
};

}

#endif
