#ifndef PMTRACER_TRACER_H
#define PMTRACER_TRACER_H

#include "RGBColor.h"
#include "Ray.h"

namespace pm {

class World;

class Tracer
{
  public:
	enum class Type
	{
		RAYCAST,
		WHITTED,
		AREALIGHTING,
		PATHTRACE,
		GLOBALTRACE
	};

	explicit Tracer(Type type)
	    : type_(type) {}
	virtual ~Tracer() {}

	inline Type type() const { return type_; }

	virtual RGBColor traceRay(const World &world, const Ray &ray) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor traceRay(const World &world, const Ray &ray, int depth) const { return RGBColor(0.0f, 0.0f, 0.0f); }
	virtual RGBColor traceRay(const World &world, const Ray &ray, float &tMin, int depth) const { return RGBColor(0.0f, 0.0f, 0.0f); }

  private:
	Type type_;
};

}

#endif
