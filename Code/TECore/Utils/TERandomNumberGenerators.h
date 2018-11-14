#ifndef TERANDOMNUMBERGENERATORS_H
#define TERANDOMNUMBERGENERATORS_H

#include "TEDataTypes.h"

#include <random>

namespace TE
{
	namespace Utils
	{
		class RandomI32Generator
		{
		public:
			RandomI32Generator(I32 rangeMin, I32 rangeMax)
				: m_distribution(rangeMin, rangeMax)
			{
			}

			I32 operator()()
			{
				return m_distribution(s_randomNumberGenerator);
			}
		private:
            std::uniform_int_distribution<I32> m_distribution;
			static std::mt19937 s_randomNumberGenerator;
		};

		std::mt19937 RandomI32Generator::s_randomNumberGenerator;

		class RandomF32Generator
		{
		public:
			RandomF32Generator(F32 rangeMin, F32 rangeMax)
				: m_distribution(rangeMin, rangeMax)
			{
			}

			F32 operator()()
			{
				return m_distribution(s_randomNumberGenerator);
			}
		private:
            std::uniform_real_distribution<F32> m_distribution;
			static std::mt19937 s_randomNumberGenerator;
		};

		std::mt19937 RandomF32Generator::s_randomNumberGenerator;
	}
}

#endif
