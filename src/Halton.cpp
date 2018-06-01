#include "Halton.h"

namespace pm {

Halton::Halton(int numSamples)
	: Sampler(numSamples)
{
	Halton::generateSamples();
}

void Halton::generateSamples()
{
	for (int p = 0; p < numSets_; p++)
	{
		for (int j = 0; j < numSamples_; j++)
		{
			Vector2 pv(static_cast<float>(j) / static_cast<float>(numSamples_), phi(j, 2.0f));
			samples_.push_back(pv);
		}
	}
}

float Halton::phi(int i, float base)
{
	float f = 1.0f;
	float r = 0.0f;

	while(i > 0)
	{
		f = f / base;
		r = r + f * (fmodf(static_cast<float>(i), base));
		i = static_cast<int>(i / base);
	}

	return r;
}

}
