#include "PureRandom.h"

namespace pm {

PureRandom::PureRandom(int numSamples)
    : Sampler(numSamples)
{
	PureRandom::generateSamples();
}

void PureRandom::generateSamples()
{
	for (int p = 0; p < numSets_; p++)
		for (int q = 0; q < numSamples_; q++)
			samples_.push_back(Vector2(rnd_.real(), rnd_.real()));
}

}
