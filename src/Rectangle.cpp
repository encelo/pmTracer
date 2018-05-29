#include "Rectangle.h"
#include "Sampler.h"
#include "Hammersley.h"

namespace pm {

Rectangle::Rectangle()
	: Rectangle(Vector3(-0.5, 0.0, -0.5), Vector3(1.0, 0.0, 0.0), Vector3(0.0, 0.0, 1.0), Vector3(0.0, 1.0, 0.0))
{

}

Rectangle::Rectangle(const Vector3 &point, const Vector3 &a, const Vector3 &b)
	: Rectangle(point, a, b, cross(a, b))
{

}

Rectangle::Rectangle(const Vector3 &point, const Vector3 &a, const Vector3 &b, const Vector3 &normal)
	: Geometry(), point_(point), a_(a), b_(b), normal_(normal), sampler_(std::make_unique<Hammersley>(16))
{
	normal_.normalize();

	const float area = a.length() * b.length();
	invArea_ = 1.0f / area;

	aSquaredLength_ = a.sqrLength();
	bSquaredLength_ = b.sqrLength();
}

bool Rectangle::hit(const Ray &ray, double &tMin, ShadeRecord &sr) const
{
	double t = dot((point_ - ray.o), normal_) / dot(ray.d, normal_);

	if (t <= Epsilon)
		return false;

	Vector3 p = ray.o + t * ray.d;
	Vector3 d = p - point_;

	const double dDotA = dot(d, a_);
	if (dDotA < 0.0 || dDotA > aSquaredLength_)
		return false;

	const double dDotB = dot(d, b_);
	if (dDotB < 0.0 || dDotB > bSquaredLength_)
		return false;

	tMin = t;
	sr.normal = normal_;
	sr.localHitPoint = p;

	return true;
}

bool Rectangle::shadowHit(const Ray &ray, double &tMin) const
{
	double t = dot((point_ - ray.o), normal_) / dot(ray.d, normal_);

	if (t <= Epsilon)
		return false;

	Vector3 p = ray.o + t * ray.d;
	Vector3 d = p - point_;

	const double dDotA = dot(d, a_);
	if (dDotA < 0.0 || dDotA > aSquaredLength_)
		return false;

	const double dDotB = dot(d, b_);
	if (dDotB < 0.0 || dDotB > bSquaredLength_)
		return false;

	tMin = t;

	return true;
}

Vector3 Rectangle::sample(void) const
{
	Vector2 sp = sampler_->sampleUnitSquare();
	return Vector3(point_ + sp.x * a_ + sp.y * b_);
}

}
