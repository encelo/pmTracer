#ifndef PMTRACER_SAMPLER_H
#define PMTRACER_SAMPLER_H

#include <vector>
#include "Random.h"
#include "Vector2.h"
#include "Vector3.h"

namespace pm {

class Sampler
{
  public:
	enum class Type
	{
		REGULAR,
		PURE_RANDOM,
		JITTERED,
		MULTI_JITTERED,
		NROOKS,
		HAMMERSLEY,
		HALTON
	};

	Sampler(Type type, unsigned int numSamples);
	virtual ~Sampler() {}

	inline Type type() const { return type_; }

	/// Returns next sample on unit square
	Vector2 sampleUnitSquare(unsigned long &count, int &jump);
	/// Returns next sample on unit disk
	Vector2 sampleUnitDisk(unsigned long &count, int &jump);
	/// Returns next sample on hemisphere
	Vector3 sampleHemisphere(unsigned long &count, int &jump);

	/// Generates sample patterns in a unit square
	virtual void generateSamples() = 0;
	/// Sets up the randomly shuffled indices
	void setupShuffleIndices();
	/// Randomly shuffles the samples in each pattern
	void shuffleSamples();

	void resize(unsigned int numSamples);

	inline unsigned int numSamples() const { return numSamples_; }
	inline unsigned int numSets() const { return numSets_; }

	void mapSamplesToDisk();
	void mapSamplesToHemisphere(float e);

  private:
	Type type_;

  protected:
	/// The number of samples points in a pattern
	unsigned int numSamples_;
	/// The number of sample sets (patterns) stored
	unsigned int numSets_;
	/// Sample points on a unit square
	std::vector<Vector2> samples_;
	/// Sample points on a unit disc
	std::vector<Vector2> diskSamples_;
	/// Sample points on a unit hemisphere
	std::vector<Vector3> hemisphereSamples_;
	/// Shuffled samples array indices
	std::vector<unsigned int> shuffledIndices_;

	Random rnd_;
};

}

#endif
