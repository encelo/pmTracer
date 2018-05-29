#ifndef PMTRACER_RAY_H
#define PMTRACER_RAY_H

#include "Vector3.h"

namespace pm {

class Ray
{
public:
	Vector3 o;
	Vector3 d;

	Ray() : o(0.0, 0.0, 0.0), d(1.0, 0.0, 0.0) { }
	Ray(const Vector3 &p, const Vector3 &v) : o(p), d(v) { }
};

}

#endif
