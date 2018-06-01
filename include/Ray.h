#ifndef PMTRACER_RAY_H
#define PMTRACER_RAY_H

#include "Vector3.h"

namespace pm {

class Ray
{
public:
	Vector3 o;
	Vector3 d;

	Ray() : o(0.0f, 0.0f, 0.0f), d(1.0f, 0.0f, 0.0f) { }
	Ray(const Vector3 &p, const Vector3 &v) : o(p), d(v) { }
};

}

#endif
