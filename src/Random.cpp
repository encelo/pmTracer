#include <cmath> // for ldexp()
#include <cassert>
#include "Random.h"

namespace pm {

namespace {

	const uint64_t DefaultInitState = 0x853c49e6748fea9bULL;
	const uint64_t DefaultInitSequence = 0xda3e39cb94b95bdbULL;

	uint32_t random(uint64_t &state, uint64_t &increment)
	{
		const uint64_t oldState = state;
		state = oldState * 6364136223846793005ULL + increment;
		const uint32_t xorShifted = ((oldState >> 18u) ^ oldState) >> 27u;
		const uint32_t rotation = oldState >> 59u;
		return (xorShifted >> rotation) | (xorShifted << ((-rotation) & 31));
	}

	uint32_t boundRandom(uint64_t &state, uint64_t &increment, uint32_t bound)
	{
		const uint32_t threshold = -bound % bound;
		while (true)
		{
			const uint32_t r = random(state, increment);
			if (r >= threshold)
				return r % bound;
		}
	}

}

Random::Random()
    : Random(DefaultInitState, DefaultInitSequence)
{
}

Random::Random(uint64_t initState, uint64_t initSequence)
    : state_(0ULL), increment_(0ULL)
{
	init(initState, initSequence);
}

void Random::init(uint64_t initState, uint64_t initSequence)
{
	state_ = 0U;
	increment_ = (initSequence << 1u) | 1u;
	random(state_, increment_);
	state_ += initState;
	random(state_, increment_);
}

uint32_t Random::integer()
{
	return random(state_, increment_);
}

uint32_t Random::integer(uint32_t min, uint32_t max)
{
	assert(min <= max);
	return min + boundRandom(state_, increment_, max - min);
}

float Random::real()
{
	return static_cast<float>(ldexp(random(state_, increment_), -32));
}

float Random::real(float min, float max)
{
	assert(min <= max);
	return min + static_cast<float>(ldexp(random(state_, increment_), -32)) * (max - min);
}

}
