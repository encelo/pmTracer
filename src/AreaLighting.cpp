#include "AreaLighting.h"
#include "ShadeRecord.h"
#include "World.h"
#include "Material.h"

namespace pm {

RGBColor AreaLighting::traceRay(const Ray &ray, int depth) const
{
	ShadeRecord sr(world_.hitObjects(ray));

	if (sr.hitAnObject)
	{
		sr.ray = ray;
		return sr.material->areaLightShade(sr);
	}
	else
		return world_.background();
}

}
