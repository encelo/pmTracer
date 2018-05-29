#include "Camera.h"
#include "World.h"

namespace pm {

void Camera::computeUvw()
{
	w_ = eye_ - lookAt_;
	w_.normalize();
	u_ = cross(up_, w_);
	u_.normalize();
	v_ = cross(w_, u_);

/*
	// take care of the singularity by hardwiring in specific camera orientations
	if (eye_.x == lookAt_.x && eye_.z == lookAt_.z && eye_.y > lookAt_.y)
	{
		// camera looking vertically down
		u_ = Vector3(0, 0, 1);
		v_ = Vector3(1, 0, 0);
		w_ = Vector3(0, 1, 0);
	}

	if (eye_.x == lookAt_.x && eye_.z == lookAt_.z && eye_.y < lookAt_.y)
	{
		// camera looking vertically up
		u_ = Vector3(1, 0, 0);
		v_ = Vector3(0, 0, 1);
		w_ = Vector3(0, -1, 0);
	}
*/
}

void Camera::renderScene(World &world, RGBColor *frame)
{
	renderScene(world, frame, 0, 0, world.viewPlane().width(), world.viewPlane().height());
}

void Camera::renderScene(World &world, RGBColor *frame, int startX, int startY, int tileSize)
{
	renderScene(world, frame, startX, startY, tileSize, tileSize);
}

}
