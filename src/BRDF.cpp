#include "BRDF.h"
#include "Sampler.h"

namespace pm {

void BRDF::setSampler(Sampler *sampler)
{
	samplerState_.setSampler(sampler);
	sampler->mapSamplesToHemisphere(1.0f);
}

}
