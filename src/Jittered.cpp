#include "Jittered.h"

namespace pm {

Jittered::Jittered(unsigned int numSamples)
    : Sampler(Type::JITTERED, numSamples)
{
	Jittered::generateSamples();
}

void Jittered::generateSamples()
{
	const unsigned int n = static_cast<unsigned int>(sqrtf(static_cast<float>(numSamples_)));

	for (unsigned int p = 0; p < numSets_; p++)
		for (unsigned int j = 0; j < n; j++)
			for (unsigned int k = 0; k < n; k++)
			{
				Vector2 sp((k + rnd_.real()) / n, (j + rnd_.real()) / n);
				samples_.push_back(sp);
			}
}

}
