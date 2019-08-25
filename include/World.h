#ifndef PMTRACER_WORLD_H
#define PMTRACER_WORLD_H

#include <memory>
#include <vector>
#include "ViewPlane.h"
#include "Light.h"
#include "Sampler.h"
#include "Geometry.h"

namespace pm {

class RGBColor;
class Material;
class Emissive;

class World
{
  public:
	World();

	inline const ViewPlane &viewPlane() const { return viewplane_; }
	inline ViewPlane &viewPlane() { return viewplane_; }

	inline const RGBColor &background() const { return background_; }
	inline RGBColor &editBackground() { return background_; }
	inline void setBackground(float r, float g, float b) { background_.set(r, g, b); }
	inline void setBackground(const RGBColor &color) { background_ = color; }

	inline const std::vector<std::unique_ptr<Geometry>> &objects() const { return objects_; }
	inline std::vector<std::unique_ptr<Geometry>> &objects() { return objects_; }
	void addObject(std::unique_ptr<Geometry> object);
	template <class T, typename... Args>
	T *createObject(Args &&... args)
	{
		objects_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
		return static_cast<T *>(objects_.back().get());
	}

	inline const std::vector<std::unique_ptr<Material>> &materials() const { return materials_; }
	inline std::vector<std::unique_ptr<Material>> &materials() { return materials_; }
	void addMaterial(std::unique_ptr<Material> material);
	template <class T, typename... Args> T *createMaterial(Args &&... args);

	inline const Light &ambientLight() const { return *ambientLight_; }
	inline Light &ambientLight() { return *ambientLight_; }
	void setAmbientLight(std::unique_ptr<Light> ambient);
	inline const std::vector<std::unique_ptr<Light>> &lights() const { return lights_; }
	inline std::vector<std::unique_ptr<Light>> &lights() { return lights_; }
	void addLight(std::unique_ptr<Light> light);
	template <class T, typename... Args> T *createLight(Args &&... args);

	inline const std::vector<std::unique_ptr<Sampler>> &samplers() const { return samplers_; }
	inline std::vector<std::unique_ptr<Sampler>> &samplers() { return samplers_; }
	void addSampler(std::unique_ptr<Sampler> sampler);
	template <class T, typename... Args> T *createSampler(Args &&... args);

	void clear();
	void hitObjects(const Ray &ray, ShadeRecord &sr) const;

  private:
	ViewPlane viewplane_;
	RGBColor background_;
	std::vector<std::unique_ptr<Geometry>> objects_;
	std::vector<std::unique_ptr<Material>> materials_;
	std::unique_ptr<Light> ambientLight_;
	std::vector<std::unique_ptr<Light>> lights_;
	std::vector<std::unique_ptr<Sampler>> samplers_;
};

template <class T, typename... Args>
T *World::createMaterial(Args &&... args)
{
	materials_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	return static_cast<T *>(materials_.back().get());
}

template <class T, typename... Args>
T *World::createLight(Args &&... args)
{
	lights_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	return static_cast<T *>(lights_.back().get());
}

template <class T, typename... Args>
T *World::createSampler(Args &&... args)
{
	samplers_.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	return static_cast<T *>(samplers_.back().get());
}

}

#endif
