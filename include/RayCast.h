#ifndef PMTRACER_RAYCAST_H
#define PMTRACER_RAYCAST_H

#include "Tracer.h"

namespace pm {

class RayCast : public Tracer
{
public:
	RayCast(World &world) : Tracer(world) { }

	RGBColor traceRay(const Ray &ray, int depth) const override;
};

}

#endif
