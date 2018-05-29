#include "SamplerState.h"
#include "Sampler.h"

namespace pm {

SamplerState::SamplerState()
	: count_(0), jump_(0), sampler_(nullptr)
{

}

SamplerState::SamplerState(Sampler *sampler)
	: count_(0), jump_(0), sampler_(sampler)
{

}

int SamplerState::numSamples() const
{
	return (sampler_) ? sampler_->numSamples() : 0;
}

Vector2 SamplerState::sampleUnitSquare() const
{
	return sampler_->sampleUnitSquare(count_, jump_);
}

Vector2 SamplerState::sampleUnitDisk() const
{
	return sampler_->sampleUnitDisk(count_, jump_);
}

Vector3 SamplerState::sampleHemisphere() const
{
	return sampler_->sampleHemisphere(count_, jump_);
}

}
