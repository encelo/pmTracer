#include "Rectangle.h"
#include "Sampler.h"
#include "Hammersley.h"

namespace pm {

Rectangle::Rectangle()
    : Rectangle(Vector3(-0.5f, 0.0f, -0.5f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f), Vector3(0.0f, 1.0f, 0.0f))
{
}

Rectangle::Rectangle(const Vector3 &point, const Vector3 &a, const Vector3 &b)
    : Rectangle(point, a, b, cross(a, b))
{
}

Rectangle::Rectangle(const Vector3 &point, const Vector3 &a, const Vector3 &b, const Vector3 &normal)
    : Geometry(Type::RECTANGLE), point_(point), a_(a), b_(b), normal_(normal)
{
	updateDimensions();
}

void Rectangle::updateDimensions()
{
	normal_.normalize();

	const float area = a_.length() * b_.length();
	invArea_ = 1.0f / area;

	aSquaredLength_ = a_.sqrLength();
	bSquaredLength_ = b_.sqrLength();
}

bool Rectangle::hit(const Ray &ray, float &tMin, ShadeRecord &sr) const
{
	float t = dot((point_ - ray.o), normal_) / dot(ray.d, normal_);

	if (t <= Epsilon)
		return false;

	Vector3 p = ray.o + t * ray.d;
	Vector3 d = p - point_;

	const float dDotA = dot(d, a_);
	if (dDotA < 0.0f || dDotA > aSquaredLength_)
		return false;

	const float dDotB = dot(d, b_);
	if (dDotB < 0.0f || dDotB > bSquaredLength_)
		return false;

	tMin = t;
	sr.normal = normal_;
	sr.localHitPoint = p;

	return true;
}

bool Rectangle::shadowHit(const Ray &ray, float &tMin) const
{
	float t = dot((point_ - ray.o), normal_) / dot(ray.d, normal_);

	if (t <= Epsilon)
		return false;

	Vector3 p = ray.o + t * ray.d;
	Vector3 d = p - point_;

	const float dDotA = dot(d, a_);
	if (dDotA < 0.0f || dDotA > aSquaredLength_)
		return false;

	const float dDotB = dot(d, b_);
	if (dDotB < 0.0f || dDotB > bSquaredLength_)
		return false;

	tMin = t;

	return true;
}

Vector3 Rectangle::sample(void) const
{
	Vector2 sp = samplerState_.sampleUnitSquare();
	return Vector3(point_ + sp.x * a_ + sp.y * b_);
}

}
