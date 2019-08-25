#ifndef PMTRACER_SHADERECORD_H
#define PMTRACER_SHADERECORD_H

#include "Vector3.h"
#include "Ray.h"
#include "RGBColor.h"

namespace pm {

class Material;
class World;
class Tracer;

class ShadeRecord
{
  public:
	/// True if the ray hit an object
	bool hitAnObject;
	/// Material of the nearest object
	const Material *material;
	/// World coordinates of hit point
	Vector3 hitPoint;
	/// Hit point in local object coordinates
	Vector3 localHitPoint;
	/// Surface normal at hit point
	Vector3 normal;
	/// For specular highlights
	Ray ray;
	/// Recursion depth
	int depth;
	/// For area lights
	Vector3 dir;
	/// Ray parameter
	float t;
	/// Reference to the world
	const World &world;
	/// Reference to the tracer
	const Tracer &tracer;

	ShadeRecord(const World &wr, const Tracer &tr)
	    : hitAnObject(false), material(nullptr),
	      depth(0), t(0.0f), world(wr), tracer(tr) {}
};

}

#endif
