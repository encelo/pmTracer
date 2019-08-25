#ifndef PMTRACER_PINHOLE_H
#define PMTRACER_PINHOLE_H

#include "Camera.h"
#include "Vector2.h"

namespace pm {

class PinHole : public Camera
{
  public:
	PinHole()
	    : Camera(Type::PINHOLE), distance_(1.0f), zoom_(1.0f) {}

	inline float viewDistance() const { return distance_; }
	inline float &editViewDistance() { return distance_; }
	inline float zoom() const { return zoom_; }
	inline float &editZoom() { return zoom_; }

	Vector3 rayDirection(float x, float y) const;

	using Camera::renderScene;
	void renderScene(World &world, Tracer &tracer, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight, bool progressive) override;

  private:
	/// View-plane distance
	float distance_;
	/// Zoom factor
	float zoom_;
};

}

#endif
