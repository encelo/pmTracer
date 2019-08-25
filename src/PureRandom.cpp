#include "PureRandom.h"

namespace pm {

PureRandom::PureRandom(unsigned int numSamples)
    : Sampler(Type::PURE_RANDOM, numSamples)
{
	PureRandom::generateSamples();
}

void PureRandom::generateSamples()
{
	for (unsigned int p = 0; p < numSets_; p++)
		for (unsigned int q = 0; q < numSamples_; q++)
			samples_.push_back(Vector2(rnd_.real(), rnd_.real()));
}

}
