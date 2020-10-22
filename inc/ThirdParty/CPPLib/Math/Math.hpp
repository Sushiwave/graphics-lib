#pragma once
#include <cmath>




namespace cpp
{
	class Math
	{
	public:
		static constexpr double PI = 3.14159265358979323846;
		static constexpr double HALF_PI = PI*0.5;
		static constexpr double TWO_PI = PI*2.0;
		static constexpr double INV_PI = 1.0/PI;
		static constexpr double INV_HALF_PI = 1.0/HALF_PI;
		static constexpr double INV_TWO_PI = 1.0/TWO_PI;

	public:
		template <typename T>
		static constexpr T degreeToRadian(T degree)
		{
			return degree/static_cast<T>(180.0)*static_cast<T>(PI);
		}
		template <typename T>
		static constexpr T radianToDegree(T radian)
		{
			return radian*static_cast<T>(INV_PI*180.0);
		}
	};
}