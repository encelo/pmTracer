#ifndef PMTRACER_TRACER_H
#define PMTRACER_TRACER_H

#include "RGBColor.h"
#include "Ray.h"

namespace pm {

class World;

class Tracer
{
  public:
	Tracer(World &w)
	    : world_(w) {}
	virtual ~Tracer() {}

	virtual RGBColor traceRay(const Ray &ray) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor traceRay(const Ray &ray, int depth) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor traceRay(const Ray &ray, float &tMin, int depth) const { return RGBColor(0.0f, 0.0f, 0.0f); }

  protected:
	World &world_;
};

}

#endif
