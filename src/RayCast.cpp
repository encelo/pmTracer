#include "RayCast.h"
#include "ShadeRecord.h"
#include "World.h"
#include "Material.h"

namespace pm {

RGBColor RayCast::traceRay(const Ray &ray, int depth) const
{
	ShadeRecord sr(world_.hitObjects(ray));

	if (sr.hitAnObject)
	{
		sr.ray = ray; // for specular reflections
		return sr.material->shade(sr);
	}
	else
		return world_.background();
}

}
