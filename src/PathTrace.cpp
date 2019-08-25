#include "PathTrace.h"
#include "ShadeRecord.h"
#include "World.h"
#include "Material.h"

namespace pm {

RGBColor PathTrace::traceRay(const World &world, const Ray &ray, int depth) const
{
	if (depth > world.viewPlane().maxDepth())
		return RGBColor(0.0f, 0.0f, 0.0f);
	else
	{
		ShadeRecord sr(world, *this);
		world.hitObjects(ray, sr);

		if (sr.hitAnObject)
		{
			sr.depth = depth;
			sr.ray = ray;
			return sr.material->pathShade(sr);
		}
		else
			return world.background();
	}
}

}
