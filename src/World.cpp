#include <limits>
#include "World.h"
#include "Vector3.h"
#include "Ambient.h"
#include "RayCast.h"
#include "Whitted.h"
#include "PathTrace.h"
#include "Geometry.h"
#include "Material.h"
#include "ShadeRecord.h"

namespace pm {

World::World()
	: background_(0.0f, 0.0f, 0.0f),
	  tracer_(std::make_unique<Whitted>(*this)),
	  ambientLight_(std::make_unique<Ambient>())
{

}

void World::addObject(std::unique_ptr<Geometry> object)
{
	objects_.push_back(std::move(object));
}

void World::addMaterial(std::unique_ptr<Material> material)
{
	materials_.push_back(std::move(material));
}

void World::setAmbientLight(std::unique_ptr<Light> ambient)
{
	ambientLight_ = std::move(ambient);
}

void World::addLight(std::unique_ptr<Light> light)
{
	lights_.push_back(std::move(light));
}

void World::addSampler(std::unique_ptr<Sampler> sampler)
{
	samplers_.push_back(std::move(sampler));
}


ShadeRecord World::hitObjects(const Ray &ray) const
{
	ShadeRecord sr(*this);
	double t;
	Vector3 normal;
	Vector3 localHitPoint;
	double tMin = std::numeric_limits<double>::max();
	const size_t numObjects = objects_.size();

	for (unsigned int i = 0; i < numObjects; i++)
	{
		if (objects_[i]->hit(ray, t, sr) && (t < tMin))
		{
			sr.hitAnObject = true;
			tMin = t;
			sr.material = objects_[i]->material();
			sr.hitPoint = ray.o + t * ray.d;
			normal = sr.normal;
			localHitPoint = sr.localHitPoint;
		}
	}

	if (sr.hitAnObject)
	{
		sr.t = tMin;
		sr.normal = normal;
		sr.localHitPoint = localHitPoint;
	}

	return sr;
}

}
