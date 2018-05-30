#include <limits>
#include <algorithm>
#include "Sampler.h"

const float pi = 3.14159265358979323846;
const float pi4 = 3.14159265358979323846 / 4.0;

namespace pm {

Sampler::Sampler(int numSamples)
	: numSamples_(numSamples), numSets_(83),
	  rndFloatDist_(0.0f, 1.0f), rndIntDist_(0, std::numeric_limits<int>::max())
{
	samples_.reserve(numSamples_ * numSets_);
	setupShuffleIndices();
}

Vector2 Sampler::sampleUnitSquare(unsigned long &count, int &jump)
{
	// Start of a new pixel
	if (count % numSamples_ == 0)
		jump = (rndIntDist_(rndGen_) % numSets_) * numSamples_;

	return samples_[jump + shuffledIndices_[jump + count++ % numSamples_]];
}

Vector2 Sampler::sampleUnitDisk(unsigned long &count, int &jump)
{
	// Start of a new pixel
	if (count % numSamples_ == 0)
		jump = (rndIntDist_(rndGen_) % numSets_) * numSamples_;

	return diskSamples_[jump + shuffledIndices_[jump + count++ % numSamples_]];
}

Vector3 Sampler::sampleHemisphere(unsigned long &count, int &jump)
{
	// Start of a new pixel
	if (count % numSamples() == 0)
		jump = (rndIntDist_(rndGen_) % numSets_) * numSamples_;

	return hemisphereSamples_[jump + shuffledIndices_[jump + count++ % numSamples_]];
}

void Sampler::setupShuffleIndices()
{
	shuffledIndices_.reserve(numSamples_ * numSets_);
	std::vector<int> indices;
	indices.reserve(numSamples_);

	for (int i = 0; i < numSamples_; i++)
		indices.push_back(i);

	for (int p = 0; p < numSets_; p++)
	{
		std::random_shuffle(indices.begin(), indices.end());

		for (int i = 0; i < numSamples_; i++)
			shuffledIndices_.push_back(indices[i]);
	}
}

void Sampler::mapSamplesToDisk()
{
	if (diskSamples_.empty() == false)
		return;

	const int size = samples_.size();
	float r, phi;
	Vector2 sp;

	diskSamples_.reserve(size);

	for (int i = 0; i < size; i++)
	{
		// map sample point to [-1, 1]
		sp.x = 2.0 * samples_[i].x - 1.0;
		sp.y = 2.0 * samples_[i].y - 1.0;

		// determine the sector
		if (sp.x > -sp.y)
		{
			// sector 1
			if (sp.x > sp.y)
			{
				r = sp.x;
				phi = sp.y / sp.x;
			}
			// sector 2
			else
			{
				r = sp.y;
				phi = 2.0 - sp.x / sp.y;
			}
		}
		else
		{
			// sector 3
			if (sp.x < sp.y)
			{
				r = -sp.x;
				phi = 4.0 * sp.y / sp.x;
			}
			// sector 4
			else
			{
				r = -sp.y;
				// avoid division by zero at origin
				if (sp.y != 0.0)
					phi = 6 - sp.x / sp.y;
				else
					phi = 0.0;
			}
		}

		phi *= pi4;

		diskSamples_[i].x = r * cos(phi);
		diskSamples_[i].y = r * sin(phi);
	}
}

void Sampler::mapSamplesToHemisphere(float e)
{
	if (hemisphereSamples_.empty() == false)
		return;

	const int size = samples_.size();
	hemisphereSamples_.reserve(numSamples_ * numSets_);

	for (int i = 0; i < size; i++)
	{
		const float cosPhi = cos(2.0 * pi * samples_[i].x);
		const float sinPhi = sin(2.0 * pi * samples_[i].x);
		const float cosTheta = pow((1.0 - samples_[i].y), 1.0 / (e + 1.0));
		const float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

		hemisphereSamples_.push_back(Vector3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta));
	}
}

}
