#include "Jittered.h"

namespace pm {

Jittered::Jittered(int numSamples)
    : Sampler(numSamples)
{
	Jittered::generateSamples();
}

void Jittered::generateSamples()
{
	const int n = static_cast<int>(sqrtf(static_cast<float>(numSamples_)));

	for (int p = 0; p < numSets_; p++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
			{
				Vector2 sp((k + rnd_.real()) / n, (j + rnd_.real()) / n);
				samples_.push_back(sp);
			}
}

}
