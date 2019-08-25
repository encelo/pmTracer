#ifndef PMTRACER_NROOKS_H
#define PMTRACER_NROOKS_H

#include "Sampler.h"

namespace pm {

class NRooks : public Sampler
{
  public:
	explicit NRooks(unsigned int numSamples);
	void generateSamples() override;

  private:
	void shuffleXCoords();
	void shuffleYCoords();
};

}

#endif
