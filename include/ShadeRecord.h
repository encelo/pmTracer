#ifndef PMTRACER_SHADERECORD_H
#define PMTRACER_SHADERECORD_H

#include "Vector3.h"
#include "Ray.h"
#include "RGBColor.h"

namespace pm {

class Material;
class World;

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
	double t;
	/// Reference to the world
	const World &w;

	ShadeRecord(const World &wr)
	    : hitAnObject(false), material(nullptr), w(wr) { }
};

}

#endif
