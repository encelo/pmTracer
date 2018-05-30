#include "Hammersley.h"

namespace pm {

Hammersley::Hammersley(int numSamples)
	: Sampler(numSamples)
{
	Hammersley::generateSamples();
}

void Hammersley::generateSamples()
{
	for (int p = 0; p < numSets_; p++)
	{
		for (int j = 0; j < numSamples_; j++)
		{
			Vector2 pv(static_cast<float>(j) / static_cast<float>(numSamples_), phi(j));
			samples_.push_back(pv);
		}
	}
}

float Hammersley::phi(int i)
{
	float x = 0.0;
	float f = 0.5;

	while (i)
	{
		x += f * static_cast<float>(i % 2);
		i /= 2;
		f *= 0.5;
	}

	return x;
}

}
