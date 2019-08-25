#ifndef PMTRACER_LIGHT_H
#define PMTRACER_LIGHT_H

#include "Vector3.h"
#include "RGBColor.h"

namespace pm {

class ShadeRecord;
class Ray;

class Light
{
  public:
	enum class Type
	{
		DIRECTIONAL,
		POINT,
		AMBIENT,
		AMBIENT_OCCLUDER,
		AREA,
		ENVIRONMENT
	};

	explicit Light(Type type)
	    : type_(type), castShadows_(true) {}
	virtual ~Light() {}

	inline Type type() const { return type_; }

	virtual Vector3 direction(ShadeRecord &sr) const = 0;
	virtual RGBColor L(ShadeRecord &sr) const = 0;
	virtual bool inShadow(const Ray &ray, const ShadeRecord &sr) const = 0;

	virtual float G(const ShadeRecord &sr) const { return 1.0f; }
	virtual float pdf(ShadeRecord &sr) const { return 1.0f; }

	inline bool castShadows() const { return castShadows_; }
	inline bool &editCastShadows() { return castShadows_; }
	inline void setCastShadows(bool castShadows) { castShadows_ = castShadows; }

  private:
	Type type_;

  protected:
	bool castShadows_;
};

}

#endif
