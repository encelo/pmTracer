#include "AreaLighting.h"
#include "ShadeRecord.h"
#include "World.h"
#include "Material.h"

namespace pm {

RGBColor AreaLighting::traceRay(const World &world, const Ray &ray, int depth) const
{
	ShadeRecord sr(world, *this);
	world.hitObjects(ray, sr);

	if (sr.hitAnObject)
	{
		sr.ray = ray;
		return sr.material->areaLightShade(sr);
	}
	else
		return world.background();
}

}
