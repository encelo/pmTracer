#include <limits>
#include <algorithm>
#include <random>
#include "Sampler.h"

const float pi = 3.14159265358979323846264338327950288f;
const float pi4 = 0.785398163397448309615660845819875721f;

namespace pm {

Sampler::Sampler(Type type, unsigned int numSamples)
    : type_(type), numSamples_(numSamples), numSets_(83)
{
	samples_.reserve(numSamples_ * numSets_);
	setupShuffleIndices();
}

Vector2 Sampler::sampleUnitSquare(unsigned long &count, int &jump)
{
	// Start of a new pixel
	if (count % numSamples_ == 0)
		jump = rnd_.integer(0, numSets_) * numSamples_;

	return samples_[jump + shuffledIndices_[jump + count++ % numSamples_]];
}

Vector2 Sampler::sampleUnitDisk(unsigned long &count, int &jump)
{
	// Start of a new pixel
	if (count % numSamples_ == 0)
		jump = rnd_.integer(0, numSets_) * numSamples_;

	return diskSamples_[jump + shuffledIndices_[jump + count++ % numSamples_]];
}

Vector3 Sampler::sampleHemisphere(unsigned long &count, int &jump)
{
	// Start of a new pixel
	if (count % numSamples() == 0)
		jump = rnd_.integer(0, numSets_) * numSamples_;

	return hemisphereSamples_[jump + shuffledIndices_[jump + count++ % numSamples_]];
}

void Sampler::setupShuffleIndices()
{
	std::random_device rd;
	std::mt19937 g(rd());

	shuffledIndices_.reserve(numSamples_ * numSets_);
	std::vector<unsigned int> indices;
	indices.reserve(numSamples_);

	for (unsigned int i = 0; i < numSamples_; i++)
		indices.push_back(i);

	for (unsigned int p = 0; p < numSets_; p++)
	{
		std::shuffle(indices.begin(), indices.end(), g);

		for (unsigned int i = 0; i < numSamples_; i++)
			shuffledIndices_.push_back(indices[i]);
	}
}

void Sampler::resize(unsigned int numSamples)
{
	// Set the new number first as some methods will use it internally
	numSamples_ = numSamples;

	samples_.clear();
	diskSamples_.clear();
	hemisphereSamples_.clear();

	samples_.reserve(numSamples_ * numSets_);
	generateSamples();

	shuffledIndices_.clear();
	setupShuffleIndices();

	mapSamplesToDisk();
}

void Sampler::mapSamplesToDisk()
{
	const size_t size = samples_.size();
	if (diskSamples_.size() == size)
		return;

	diskSamples_.clear();
	diskSamples_.reserve(size);

	float r, phi;
	Vector2 sp;
	for (unsigned int i = 0; i < size; i++)
	{
		// map sample point to [-1, 1]
		sp.x = 2.0f * samples_[i].x - 1.0f;
		sp.y = 2.0f * samples_[i].y - 1.0f;

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
				phi = 2.0f - sp.x / sp.y;
			}
		}
		else
		{
			// sector 3
			if (sp.x < sp.y)
			{
				r = -sp.x;
				phi = 4.0f + sp.y / sp.x;
			}
			// sector 4
			else
			{
				r = -sp.y;
				// avoid division by zero at origin
				if (sp.y != 0.0f)
					phi = 6.0f - sp.x / sp.y;
				else
					phi = 0.0f;
			}
		}

		phi *= pi4;

		diskSamples_[i].x = r * cos(phi);
		diskSamples_[i].y = r * sin(phi);
	}
}

void Sampler::mapSamplesToHemisphere(float e)
{
	const size_t size = samples_.size();
	if (hemisphereSamples_.size() == size)
		return;

	hemisphereSamples_.clear();
	hemisphereSamples_.reserve(numSamples_ * numSets_);

	for (unsigned int i = 0; i < size; i++)
	{
		const float cosPhi = cosf(2.0f * pi * samples_[i].x);
		const float sinPhi = sinf(2.0f * pi * samples_[i].x);
		const float cosTheta = powf((1.0f - samples_[i].y), 1.0f / (e + 1.0f));
		const float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);

		hemisphereSamples_.push_back(Vector3(sinTheta * cosPhi, sinTheta * sinPhi, cosTheta));
	}
}

}
