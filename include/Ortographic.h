#ifndef PMTRACER_ORTOGRAPHIC_H
#define PMTRACER_ORTOGRAPHIC_H

#include "Camera.h"

namespace pm {

class Ortographic : public Camera
{
public:
	Ortographic() : Camera() { }

	using Camera::renderScene;
	void renderScene(World &world, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight, bool progressive) override;
};

}

#endif
