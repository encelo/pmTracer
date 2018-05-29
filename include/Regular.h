#ifndef PMTRACER_REGULAR_H
#define PMTRACER_REGULAR_H

#include "Sampler.h"

namespace pm {

class Regular : public Sampler
{
public:
	Regular(int numSamples);
	void generateSamples() override;
};

}

#endif
