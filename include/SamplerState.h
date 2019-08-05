#ifndef PMTRACER_SAMPLERSTATE_H
#define PMTRACER_SAMPLERSTATE_H

#include "Vector2.h"
#include "Vector3.h"

namespace pm {

class Sampler;

class SamplerState
{
  public:
	SamplerState();
	SamplerState(Sampler *sampler);

	int numSamples() const;

	/// Returns next sample on unit square
	Vector2 sampleUnitSquare() const;
	/// Returns next sample on unit disk
	Vector2 sampleUnitDisk() const;
	/// Returns next sample on hemisphere
	Vector3 sampleHemisphere() const;

	inline const Sampler *sampler() const { return sampler_; }
	inline void setSampler(Sampler *sampler) { sampler_ = sampler; }

  private:
	/// The current number of sample points used
	mutable unsigned long count_;
	/// Random index jump
	mutable int jump_;

	Sampler *sampler_;
};

}

#endif
