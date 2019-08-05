#include "MultiJittered.h"

namespace pm {

MultiJittered::MultiJittered(int numSamples)
    : Sampler(numSamples)
{
	MultiJittered::generateSamples();
}

void MultiJittered::generateSamples(void)
{
	// num_samples needs to be a perfect square
	const int n = static_cast<int>(sqrtf(static_cast<float>(numSamples_)));
	const float subcellWidth = 1.0f / static_cast<float>(numSamples_);

	// fill the samples array with dummy points to allow us to use the [ ] notation
	// when we set the initial patterns

	Vector2 fillPoint;
	for (int i = 0; i < numSamples_ * numSets_; i++)
		samples_.push_back(fillPoint);

	// distribute points in the initial patterns
	for (int p = 0; p < numSets_; p++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				samples_[i * n + j + p * numSamples_].x = (i * n + j) * subcellWidth + rnd_.real() * subcellWidth;
				samples_[i * n + j + p * numSamples_].y = (j * n + i) * subcellWidth + rnd_.real() * subcellWidth;
			}

	// shuffle x coordinates
	for (int p = 0; p < numSets_; p++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				// random integer between j and n - 1
				const int k = static_cast<int>(rnd_.real() * (n - 1 - j) + j);
				const float t = samples_[i * n + j + p * numSamples_].x;
				samples_[i * n + j + p * numSamples_].x = samples_[i * n + k + p * numSamples_].x;
				samples_[i * n + k + p * numSamples_].x = t;
			}

	// shuffle y coordinates
	for (int p = 0; p < numSets_; p++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				// random integer between j and n - 1
				const int k = static_cast<int>(rnd_.real() * (n - 1 - j) + j);
				float t = samples_[j * n + i + p * numSamples_].y;
				samples_[j * n + i + p * numSamples_].y = samples_[k * n + i + p * numSamples_].y;
				samples_[k * n + i + p * numSamples_].y = t;
			}
}

}
