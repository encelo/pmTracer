#include "Whitted.h"
#include "ShadeRecord.h"
#include "World.h"
#include "Material.h"

namespace pm {

RGBColor Whitted::traceRay(const Ray &ray, int depth) const
{
	if (depth > world_.viewPlane().maxDepth())
		return RGBColor(0.0f, 0.0f, 0.0f);
	else
	{
		ShadeRecord sr(world_.hitObjects(ray));

		if (sr.hitAnObject)
		{
			sr.depth = depth;
			sr.ray = ray; // for specular reflections
			return sr.material->shade(sr);
		}
		else
			return world_.background();
	}
}

}
