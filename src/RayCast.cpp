#include "RayCast.h"
#include "ShadeRecord.h"
#include "World.h"
#include "Material.h"

namespace pm {

RGBColor RayCast::traceRay(const World &world, const Ray &ray, int depth) const
{
	ShadeRecord sr(world, *this);
	world.hitObjects(ray, sr);

	if (sr.hitAnObject)
	{
		sr.ray = ray; // for specular reflections
		return sr.material->shade(sr);
	}
	else
		return world.background();
}

}
