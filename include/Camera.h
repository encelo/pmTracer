#ifndef PMTRACER_CAMERA_H
#define PMTRACER_CAMERA_H

#include "Vector3.h"

namespace pm {

class RGBColor;
class World;

class Camera
{
public:
	Camera() : eye_(0.0, 0.0, -1.0), lookAt_(0.0, 0.0, 0.0), up_(0.0, 1.0, 0.0),
		u_(1.0, 0.0, 0.0), v_(0.0, 1.0, 0.0), w_(0.0, 0.0, 1.0), exposureTime_(1.0f) { }
	virtual ~Camera() { }

	inline void setEye(double x, double y, double z) { eye_.set(x, y, z); }
	inline void setLookAt(double x, double y, double z) { lookAt_.set(x, y, z); }
	inline void setUp(double x, double y, double z) { up_.set(x, y, z); }
	inline void setExposureTime(float time) { exposureTime_ = time; }
	void computeUvw();

	void renderScene(World &world, RGBColor *frame);
	void renderScene(World &world, RGBColor *frame, int startX, int startY, int tileSize);
	virtual void renderScene(World &world, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight) = 0;

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
