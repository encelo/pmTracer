#ifndef PMTRACER_HAMMERSLEY_H
#define PMTRACER_HAMMERSLEY_H

#include "Sampler.h"

namespace pm {

class Hammersley : public Sampler
{
public:
	explicit Hammersley(int numSamples);
	void generateSamples() override;

private:
	double phi(int i);
};

}

#endif
