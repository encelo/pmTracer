#ifndef PMTRACER_MULTIJITTERED_H
#define PMTRACER_MULTIJITTERED_H

#include "Sampler.h"

namespace pm {

class MultiJittered : public Sampler
{
  public:
	explicit MultiJittered(int numSamples);
	void generateSamples() override;
};

}

#endif
