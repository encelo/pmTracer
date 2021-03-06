#ifndef PMTRACER_PURERANDOM_H
#define PMTRACER_PURERANDOM_H

#include "Sampler.h"

namespace pm {

class PureRandom : public Sampler
{
  public:
	explicit PureRandom(unsigned int numSamples);
	void generateSamples() override;
};

}

#endif
