#include "Jittered.h"

namespace pm {

Jittered::Jittered(int numSamples)
	: Sampler(numSamples)
{
	Jittered::generateSamples();
}

void Jittered::generateSamples()
{
	const int n = static_cast<int>(sqrtf(numSamples_));

	for (int p = 0; p < numSets_; p++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
			{
				Vector2 sp((k + rndFloatDist_(rndGen_)) / n, (j + rndFloatDist_(rndGen_)) / n);
				samples_.push_back(sp);
			}
}

}
