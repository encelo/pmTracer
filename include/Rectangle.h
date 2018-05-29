#ifndef PMTRACER_RECTANGLE_H
#define PMTRACER_RECTANGLE_H

#include "Geometry.h"
#include "Vector3.h"
#include "Ray.h"

namespace pm {

class Sampler;
class ShadeRecord;

class Rectangle : public Geometry
{
public:
	Rectangle();
	Rectangle(const Vector3 &point, const Vector3 &a, const Vector3 &b);
	Rectangle(const Vector3 &point, const Vector3 &a, const Vector3 &b, const Vector3 &normal);

	bool hit(const Ray &ray, double &tMin, ShadeRecord &sr) const override;
	bool shadowHit(const Ray &ray, double &tMin) const override;

	Vector3 sample(void) const override;
	inline float pdf(ShadeRecord &sr) const override { return (invArea_); }
	inline Vector3 normal(const Vector3 &p) const { return normal_; }

	inline Sampler &sampler() const { return *sampler_; }
	inline void setSampler(std::unique_ptr<Sampler> sampler) { sampler_ = std::move(sampler); }

private:
	static constexpr double Epsilon = 0.000000001;
	static constexpr double ShadowEpsilon = 0.000000001;

	/// Corner vertex
	Vector3 point_;
	/// Side
	Vector3 a_;
	/// Side
	Vector3 b_;
	Vector3 normal_;
	std::unique_ptr<Sampler> sampler_;

	float aSquaredLength_;
	float bSquaredLength_;
	float invArea_;
};

}

#endif
