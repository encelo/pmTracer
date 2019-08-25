#ifndef PMTRACER_CAMERA_H
#define PMTRACER_CAMERA_H

#include "Vector3.h"

namespace pm {

class RGBColor;
class World;
class Tracer;

class Camera
{
  public:
	enum class Type
	{
		ORTOGRAPHIC,
		PINHOLE,
	};

	explicit Camera(Type type)
	    : type_(type), eye_(0.0f, 0.0f, -1.0f), lookAt_(0.0f, 0.0f, 0.0f), up_(0.0f, 1.0f, 0.0f),
	      u_(1.0f, 0.0f, 0.0f), v_(0.0f, 1.0f, 0.0f), w_(0.0f, 0.0f, 1.0f), exposureTime_(1.0f) {}
	virtual ~Camera() {}

	inline Type type() const { return type_; }

	inline const Vector3 &eye() const { return eye_; }
	inline Vector3 &editEye() { return eye_; }
	inline const Vector3 &lookAt() const { return lookAt_; }
	inline Vector3 &editLookAt() { return lookAt_; }
	inline const Vector3 &up() const { return up_; }
	inline Vector3 &editUp() { return up_; }
	inline float exposureTime() const { return exposureTime_; }
	inline float &editExposureTime() { return exposureTime_; }
	void computeUvw();

	void renderScene(World &world, Tracer &tracer, RGBColor *frame);
	void renderScene(World &world, Tracer &tracer, RGBColor *frame, int startX, int startY, int tileSize);
	void renderScene(World &world, Tracer &tracer, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight);
	virtual void renderScene(World &world, Tracer &tracer, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight, bool progressive) = 0;

  private:
	Type type_;

  protected:
	Vector3 eye_;
	Vector3 lookAt_;
	Vector3 up_;

	Vector3 u_;
	Vector3 v_;
	Vector3 w_;

	float exposureTime_;
};

}

#endif
