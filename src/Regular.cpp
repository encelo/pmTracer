#include "Regular.h"

namespace pm {

Regular::Regular(int numSamples)
	: Sampler(numSamples)
{
	Regular::generateSamples();
}

void Regular::generateSamples()
{
	const int n = static_cast<int>(sqrtf(static_cast<float>(numSamples_)));

	for (int i = 0; i < numSets_; i++)
		for (int p = 0; p < n; p++)
			for (int q = 0; q < n; q++)
				samples_.push_back(Vector2((q + 0.5) / n, (p + 0.5) / n));
}

}
