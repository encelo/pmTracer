#ifndef PMTRACER_WORLD_H
#define PMTRACER_WORLD_H

#include <memory>
#include <vector>
#include "ViewPlane.h"
#include "Sphere.h"
#include "Tracer.h"
#include "Light.h"

namespace pm {

class RGBColor;

class World
{
public:
	World();

	inline const ViewPlane &viewPlane() const { return viewplane_; }
	inline ViewPlane &viewPlane() { return viewplane_; }
	inline RGBColor background() const { return background_; }

	inline const Tracer &tracer() const { return *tracer_; }
	inline void setTracer(std::unique_ptr<Tracer> tracer) { tracer_ = std::move(tracer); }

	inline const std::vector<std::unique_ptr<Geometry>> &objects() const { return objects_; }
	void addObject(std::unique_ptr<Geometry> object);

	inline const Light &ambientLight() const { return *ambientLight_; }
	inline Light &ambientLight() { return *ambientLight_; }
	void setAmbientLight(std::unique_ptr<Light> ambient);
	inline const std::vector<std::unique_ptr<Light>> &lights() const { return lights_; }
	void addLight(std::unique_ptr<Light> light);

	ShadeRecord hitObjects(const Ray &ray) const;

private:
	ViewPlane viewplane_;
	RGBColor background_;
	std::unique_ptr<Tracer> tracer_;
	std::vector<std::unique_ptr<Geometry>> objects_;
	std::unique_ptr<Light> ambientLight_;
	std::vector<std::unique_ptr<Light>> lights_;
};

}

#endif
