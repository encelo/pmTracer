#include "PinHole.h"
#include "Ray.h"
#include "RGBColor.h"
#include "World.h"

namespace pm {

void PinHole::renderScene(World &world, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight)
{
	Ray ray;
	ray.o = eye_;
	const ViewPlane &vp = world.viewPlane();

	int depth = 0; // recursion depth
	const float pixelSize = vp.pixelSize() / zoom_;

	for (int r = startY; r < startY + tileHeight; r++)
	{
		for (int c = startX; c < startX + tileWidth; c++)
		{
			RGBColor pixel(0.0f, 0.0f, 0.0f);
			for (int j = 0; j < vp.sampler().numSamples(); j++)
			{
				const Vector2 sp = vp.sampler().sampleUnitSquare();
				const double x = pixelSize * (c - 0.5 * vp.width() + sp.x);
				const double y = pixelSize * (r - 0.5 * vp.height() + sp.y);
				ray.d = rayDirection(x, y);
				pixel += world.tracer().traceRay(ray, depth);
			}
			pixel /= vp.sampler().numSamples();
			pixel *= exposureTime_;
			frame[r * vp.width() + c] = pixel;
		}
	}
}

Vector3 PinHole::rayDirection(double x, double y) const
{
	Vector3 dir = x * u_ + y * v_ - distance_ * w_;
	dir.normalize();

	return dir;
}

}
