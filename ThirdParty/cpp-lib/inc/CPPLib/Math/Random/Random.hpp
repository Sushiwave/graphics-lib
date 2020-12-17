#pragma once
#include <random>





namespace cpp
{
	template <typename Distribution_, typename T>
	class MersenneTwister
	{
	private:
		using ParamType_ = typename Distribution_::param_type;
	protected:
		std::mt19937 m_mt;
		Distribution_ m_distribution;
		ParamType_ m_param;
	private:
		void m_setMinMax(T min, T max)
		{
			m_param._Init(min, max);
			m_distribution.param(m_param);
		}
	public:
		MersenneTwister() = default;
		MersenneTwister(unsigned int seed)
			: m_mt(seed)
		{
		}
		virtual ~MersenneTwister() = default;

		[[nodiscard]] T get(T min, T max)
		{
			m_setMinMax(min, max);
			return m_distribution(m_mt);
		}
		[[nodiscard]] T get(T min, T max, unsigned int seed)
		{
			m_mt.seed(seed);
			m_setMinMax(min, max);
			return m_distribution(m_mt);
		}
	};

	template <typename Engine_, typename T>
	class Random
	{
	private:
		using SeedGenerator_ = std::random_device;
	private:
		SeedGenerator_ m_seedGenerator;
		Engine_ m_engine;
	public:
		Random() noexcept
			: m_engine(m_seedGenerator())
		{
		}
		virtual ~Random() = default;

		[[nodiscard]] T next(T min, T max)
		{
			return m_engine.get(min, max);
		}
	};





	template <typename T>
	using MersenneTwisterInt = MersenneTwister<std::uniform_int_distribution<T>, T>;
	template <typename T>
	using MersenneTwisterReal = MersenneTwister<std::uniform_real_distribution<T>, T>;

	template <typename T>
	using RandomInt = Random<MersenneTwisterInt<T>, T>;
	template <typename T>
	using RandomReal = Random<MersenneTwisterReal<T>, T>;
}
