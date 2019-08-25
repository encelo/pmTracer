#ifndef PMTRACER_RAYCAST_H
#define PMTRACER_RAYCAST_H

#include "Tracer.h"

namespace pm {

class RayCast : public Tracer
{
  public:
	RayCast()
	    : Tracer(Type::RAYCAST) {}

	RGBColor traceRay(const World &world, const Ray &ray, int depth) const override;
};

}

#endif
