#ifndef PMTRACER_PINHOLE_H
#define PMTRACER_PINHOLE_H

#include "Camera.h"
#include "Vector2.h"

namespace pm {

class PinHole : public Camera
{
public:
	PinHole() : Camera(), distance_(1.0f), zoom_(1.0f) { }

	inline void setViewDistance(float distance) { distance_ = distance; }
	Vector3 rayDirection(float x, float y) const;

	using Camera::renderScene;
	void renderScene(World &world, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight, bool progressive) override;

private:
	/// View-plane distance
	float distance_;
	/// Zoom factor
	float zoom_;
};

}

#endif
