#ifndef PMTRACER_HALTON_H
#define PMTRACER_HALTON_H

#include "Sampler.h"

namespace pm {

class Halton : public Sampler
{
  public:
	explicit Halton(int numSamples);
	void generateSamples() override;

  private:
	float phi(int i, float base);
};

}

#endif
