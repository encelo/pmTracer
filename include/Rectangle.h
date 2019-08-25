#ifndef PMTRACER_RECTANGLE_H
#define PMTRACER_RECTANGLE_H

#include "Geometry.h"
#include "Vector3.h"
#include "Ray.h"
#include "SamplerState.h"

namespace pm {

class Sampler;
class ShadeRecord;

class Rectangle : public Geometry
{
  public:
	Rectangle();
	Rectangle(const Vector3 &point, const Vector3 &a, const Vector3 &b);
	Rectangle(const Vector3 &point, const Vector3 &a, const Vector3 &b, const Vector3 &normal);

	void updateDimensions();

	bool hit(const Ray &ray, float &tMin, ShadeRecord &sr) const override;
	bool shadowHit(const Ray &ray, float &tMin) const override;

	Vector3 sample(void) const override;
	inline float pdf(ShadeRecord &sr) const override { return (invArea_); }
	inline Vector3 normal(const Vector3 &p) const override { return normal_; }

	inline const SamplerState &samplerState() const { return samplerState_; }
	inline void setSampler(Sampler *sampler) { samplerState_.setSampler(sampler); }

	inline const Vector3 &point() const { return point_; }
	inline Vector3 &editPoint() { return point_; }
	inline const Vector3 &sideA() const { return a_; }
	inline Vector3 &editSideA() { return a_; }
	inline const Vector3 &sideB() const { return b_; }
	inline Vector3 &editSideB() { return b_; }
	inline const Vector3 &normal() const { return normal_; }
	inline Vector3 &editNormal() { return normal_; }

  private:
	static constexpr float Epsilon = 0.000000001f;
	static constexpr float ShadowEpsilon = 0.000000001f;

	/// Corner vertex
	Vector3 point_;
	/// Side
	Vector3 a_;
	/// Side
	Vector3 b_;
	Vector3 normal_;
	SamplerState samplerState_;

	float aSquaredLength_;
	float bSquaredLength_;
	float invArea_;
};

}

#endif
