#include "NRooks.h"

namespace pm {

NRooks::NRooks(int numSamples)
	: Sampler(numSamples)
{
	NRooks::generateSamples();
}

void NRooks::generateSamples()
{
	const int n = static_cast<int>(sqrtf(numSamples_));

	for (int p = 0; p < numSets_; p++)
		for (int i = 0; i < numSamples_; i++)
		{
			Vector2 sp((i + rndFloatDist_(rndGen_)) / numSamples_, (i + rndFloatDist_(rndGen_)) / numSamples_);
			samples_.push_back(sp);
		}

	shuffleXCoords();
	shuffleYCoords();
}

void NRooks::shuffleXCoords()
{
	for (int p = 0; p < numSets_; p++)
		for (int i = 0; i <  numSamples_ - 1; i++)
		{
			const int target = rndIntDist_(rndGen_) % numSamples_ + p * numSamples_;
			const float temp = samples_[i + p * numSamples_ + 1].x;
			samples_[i + p * numSamples_ + 1].x = samples_[target].x;
			samples_[target].x = temp;
		}
}

void NRooks::shuffleYCoords()
{
	for (int p = 0; p < numSets_; p++)
		for (int i = 0; i <  numSamples_ - 1; i++)
		{
			const int target = rndIntDist_(rndGen_) % numSamples_ + p * numSamples_;
			const float temp = samples_[i + p * numSamples_ + 1].y;
			samples_[i + p * numSamples_ + 1].y = samples_[target].y;
			samples_[target].y = temp;
		}
}

}
