#include "NRooks.h"

namespace pm {

NRooks::NRooks(unsigned int numSamples)
    : Sampler(Type::NROOKS, numSamples)
{
	NRooks::generateSamples();
}

void NRooks::generateSamples()
{
	for (unsigned int p = 0; p < numSets_; p++)
		for (unsigned int i = 0; i < numSamples_; i++)
		{
			const Vector2 sp((i + rnd_.real()) / numSamples_, (i + rnd_.real()) / numSamples_);
			samples_.push_back(sp);
		}

	shuffleXCoords();
	shuffleYCoords();
}

void NRooks::shuffleXCoords()
{
	for (unsigned int p = 0; p < numSets_; p++)
		for (unsigned int i = 0; i < numSamples_ - 1; i++)
		{
			const int unsigned target = rnd_.integer(0, numSamples_) + p * numSamples_;
			const float temp = samples_[i + p * numSamples_ + 1].x;
			samples_[i + p * numSamples_ + 1].x = samples_[target].x;
			samples_[target].x = temp;
		}
}

void NRooks::shuffleYCoords()
{
	for (unsigned int p = 0; p < numSets_; p++)
		for (unsigned int i = 0; i < numSamples_ - 1; i++)
		{
			const unsigned int target = rnd_.integer(0, numSamples_) + p * numSamples_;
			const float temp = samples_[i + p * numSamples_ + 1].y;
			samples_[i + p * numSamples_ + 1].y = samples_[target].y;
			samples_[target].y = temp;
		}
}

}
