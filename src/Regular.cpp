#include "Regular.h"

namespace pm {

Regular::Regular(unsigned int numSamples)
    : Sampler(Type::REGULAR, numSamples)
{
	Regular::generateSamples();
}

void Regular::generateSamples()
{
	const unsigned int n = static_cast<unsigned int>(sqrtf(static_cast<float>(numSamples_)));

	for (unsigned int i = 0; i < numSets_; i++)
		for (unsigned int p = 0; p < n; p++)
			for (unsigned int q = 0; q < n; q++)
				samples_.push_back(Vector2((q + 0.5f) / n, (p + 0.5f) / n));
}

}
