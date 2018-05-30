#include "Ortographic.h"
#include "Ray.h"
#include "RGBColor.h"
#include "World.h"

namespace pm {

void Ortographic::renderScene(World &world, RGBColor *frame, int startX, int startY, int tileWidth, int tileHeight)
{
	Ray ray;
	ray.d = Vector3(0.0, 0.0, -1.0);
	const ViewPlane &vp = world.viewPlane();
	const float zw = 100.0; // hard-coded

	const int numSamples = vp.samplerState().numSamples();
	for (int r = startY; r < startY + tileHeight; r++)
	{
		for (int c = startX; c < startX + tileWidth; c++)
		{
			RGBColor pixel(0.0f, 0.0f, 0.0f);
			for (int j = 0; j < numSamples; j++)
			{
				const Vector2 sp = vp.samplerState().sampleUnitSquare();
				const float x = vp.pixelSize() * (c - 0.5 * vp.width() + sp.x);
				const float y = vp.pixelSize() * (r - 0.5 * vp.height() + sp.y);
				ray.o = Vector3(x, y, zw);
				pixel += world.tracer().traceRay(ray, 0);
			}
			pixel /= numSamples;
			frame[r * vp.width() + c] = pixel;
		}
	}
}

}
