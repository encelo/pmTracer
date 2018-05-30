#ifndef PMTRACER_WORLD_H
#define PMTRACER_WORLD_H

#include <memory>
#include <vector>
#include "ViewPlane.h"
#include "Tracer.h"
#include "Light.h"
#include "Sampler.h"

namespace pm {

class RGBColor;
class Geometry;
class Material;

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
	template<class T, typename... Args>
	T* createObject(Args&&... args)
	{
		objects_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		return static_cast<T*>(objects_.back().get());
	}

	inline const std::vector<std::unique_ptr<Material>> &materials() const { return materials_; }
	void addMaterial(std::unique_ptr<Material> material);
	template<class T, typename... Args> T* createMaterial(Args&&... args);

	inline const Light &ambientLight() const { return *ambientLight_; }
	inline Light &ambientLight() { return *ambientLight_; }
	void setAmbientLight(std::unique_ptr<Light> ambient);
	inline const std::vector<std::unique_ptr<Light>> &lights() const { return lights_; }
	void addLight(std::unique_ptr<Light> light);
	template<class T, typename... Args> T* createLight(Args&&... args);

	inline const std::vector<std::unique_ptr<Sampler>> &samplers() const { return samplers_; }
	void addSampler(std::unique_ptr<Sampler> sampler);
	template<class T, typename... Args> T* createSampler(Args&&... args);

	ShadeRecord hitObjects(const Ray &ray) const;

private:
	ViewPlane viewplane_;
	RGBColor background_;
	std::unique_ptr<Tracer> tracer_;
	std::vector<std::unique_ptr<Geometry>> objects_;
	std::vector<std::unique_ptr<Material>> materials_;
	std::unique_ptr<Light> ambientLight_;
	std::vector<std::unique_ptr<Light>> lights_;
	std::vector<std::unique_ptr<Sampler>> samplers_;
};

template<class T, typename... Args>
T* World::createMaterial(Args&&... args)
{
	materials_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	return static_cast<T*>(materials_.back().get());
}

template<class T, typename... Args>
T* World::createLight(Args&&... args)
{
	lights_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	return static_cast<T*>(lights_.back().get());
}

template<class T, typename... Args>
T* World::createSampler(Args&&... args)
{
	samplers_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	return static_cast<T*>(samplers_.back().get());
}


}

#endif
