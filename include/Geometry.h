#ifndef PMTRACER_GEOMETRY_H
#define PMTRACER_GEOMETRY_H

#include "ShadeRecord.h"
#include "Ray.h"
#include "Material.h"

namespace pm {

class Geometry
{
  public:
	enum class Type
	{
		SPHERE,
		PLANE,
		RECTANGLE
	};

	explicit Geometry(Type type)
	    : type_(type), castShadows_(true), material_(nullptr) {}
	virtual ~Geometry() {}

	inline Type type() const { return type_; }

	virtual bool hit(const Ray &ray, float &tMin, ShadeRecord &sr) const = 0;
	virtual bool shadowHit(const Ray &ray, float &tMin) const = 0;

	virtual Vector3 sample(void) const { return Vector3(0.0f, 0.0f, 0.0f); }
	virtual float pdf(ShadeRecord &sr) const { return 1.0f; }
	virtual Vector3 normal(const Vector3 &point) const = 0;

	inline bool castShadows() const { return castShadows_; }
	inline bool &editCastShadows() { return castShadows_; }
	inline void setCastShadows(bool castShadows) { castShadows_ = castShadows; }

	inline const Material *material() const { return material_; }
	inline Material *material() { return material_; }
	inline void setMaterial(Material *material) { material_ = material; }

  private:
	Type type_;

  protected:
	bool castShadows_;
	Material *material_;
};

}

#endif
