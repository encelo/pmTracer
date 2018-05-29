#ifndef PMTRACER_GEOMETRY_H
#define PMTRACER_GEOMETRY_H

#include <memory>
#include "ShadeRecord.h"
#include "Ray.h"
#include "Material.h"

namespace pm {

class Geometry
{
public:
	Geometry() : castShadows_(true) { }
	virtual ~Geometry() { }

	virtual bool hit(const Ray &ray, double &tMin, ShadeRecord &sr) const = 0;
	virtual bool shadowHit(const Ray &ray, double &tMin) const = 0;

	virtual Vector3 sample(void) const { return Vector3(0.0, 0.0, 0.0); }
	virtual float pdf(ShadeRecord &sr) const { return 1.0f; }
	virtual Vector3 normal(const Vector3 &point) const = 0;

	inline bool castShadows() const { return castShadows_; }
	inline void setCastShadows(bool castShadows) { castShadows_ = castShadows; }

	inline const Material &material() const { return *material_; }
	inline void setMaterial(std::unique_ptr<Material> material) { material_ = std::move(material); }

protected:
	bool castShadows_;
	std::unique_ptr<Material> material_;
};

}

#endif
