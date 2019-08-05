#ifndef PMTRACER_CAMERA_H
#define PMTRACER_CAMERA_H

#include "Vector3.h"

namespace pm {

class RGBColor;
class World;

class Camera
{
public:
	Camera() : eye_(0.0f, 0.0f, -1.0f), lookAt_(0.0f, 0.0f, 0.0f), up_(0.0f, 1.0f, 0.0f),
		u_(1.0f, 0.0f, 0.0f), v_(0.0f, 1.0f, 0.0f), w_(0.0f, 0.0f, 1.0f), exposureTime_(1.0f) { }
	virtual ~Camera() { }

	inline Vector3 &eye() { return eye_; }
	inline Vector3 &lookAt() { return lookAt_; }
	inline Vector3 &up() { return up_; }
	inline float &exposureTime() { return exposureTime_; }

	inline void setEye(float x, float y, float z) { eye_.set(x, y, z); }
	inline void setLookAt(float x, float y, float z) { lookAt_.set(x, y, z); }
	inline void setUp(float x, float y, float z) { up_.set(x, y, z); }
	inline void setExposureTime(float time) { exposureTime_ = time; }
	void computeUvw();

	void renderScene(World &world, RGBColor *frame);
	void renderScene(World &world, RGBColor *frame, int startX, int startY, int tileSize);
	void renderScene(World &world, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight);
	virtual void renderScene(World &world, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight, bool progressive) = 0;

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
