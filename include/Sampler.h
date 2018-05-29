#ifndef PMTRACER_SAMPLER_H
#define PMTRACER_SAMPLER_H

#include <vector>
#include <random>
#include "Vector2.h"
#include "Vector3.h"

namespace pm {

class Sampler
{
public:
	Sampler(int numSamples);
	virtual ~Sampler() { }

	/// Generates sample patterns in a unit square
	virtual void generateSamples() = 0;
	/// Sets up the randomly shuffled indices
	void setupShuffleIndices();
	/// Randomly shuffles the samples in each pattern
	void shuffleSamples();
	/// Returns next sample on unit square
	Vector2 sampleUnitSquare();
	/// Returns next sample on unit disk
	Vector2 sampleUnitDisk();
	/// Returns next sample on hemisphere
	Vector3 sampleHemisphere();

	inline int numSamples() const { return numSamples_; }

	void mapSamplesToDisk();
	void mapSamplesToHemisphere(float e);

protected:
	/// The number of samples points in a pattern
	int numSamples_;
	/// The number of sample sets (patterns) stored
	int numSets_;
	/// Sample points on a unit square
	std::vector<Vector2> samples_;
	/// Sample points on a unit disc
	std::vector<Vector2> diskSamples_;
	/// Sample points on a unit hemisphere
	std::vector<Vector3> hemisphereSamples_;
	/// Shuffled samples array indices
	std::vector<int> shuffledIndices_;
	/// The current number of sample points used
	unsigned long count_;
	/// Random index jump
	int jump_;

	std::default_random_engine rndGen_;
	std::uniform_real_distribution<float> rndFloatDist_;
	std::uniform_int_distribution<int> rndIntDist_;
};

}

#endif
