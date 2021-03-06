#ifndef PMTRACER_JITTERED_H
#define PMTRACER_JITTERED_H

#include "Sampler.h"

namespace pm {

class Jittered : public Sampler
{
  public:
	explicit Jittered(unsigned int numSamples);
	void generateSamples() override;
};

}

#endif
