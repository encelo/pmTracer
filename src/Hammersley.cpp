#include "Hammersley.h"

namespace pm {

namespace {

	float phi(unsigned int i)
	{
		float x = 0.0f;
		float f = 0.5f;

		while (i > 0)
		{
			x += f * static_cast<float>(i % 2);
			i /= 2;
			f *= 0.5f;
		}

		return x;
	}

}

Hammersley::Hammersley(unsigned int numSamples)
    : Sampler(Type::HAMMERSLEY, numSamples)
{
	Hammersley::generateSamples();
}

void Hammersley::generateSamples()
{
	for (unsigned int p = 0; p < numSets_; p++)
	{
		for (unsigned int j = 0; j < numSamples_; j++)
		{
			Vector2 pv(static_cast<float>(j) / static_cast<float>(numSamples_), phi(j));
			samples_.push_back(pv);
		}
	}
}

}
