#pragma once
#include <CPPLib/DataStructure/Array/Array2.hpp>
#include <CPPLib/DataStructure/Array/Array4.hpp>
#include <CPPLib/Assert/Assert.hpp>

#include <cmath>





namespace cpp
{
	template <class T>
	struct Vector2D
	{
	public:
		T x, y;





	public:
		template <typename X_, typename Y_>
		constexpr Vector2D(X_ x, Y_ y) noexcept
			: x(static_cast<T>(x)),
			  y(static_cast<T>(y))
		{
		}
		constexpr Vector2D() noexcept
			: Vector2D(0, 0)
		{
		}
		constexpr Vector2D(T v) noexcept
			: Vector2D(v, v, v)
		{
		}
		template <typename U>
		constexpr Vector2D(const Array2<U>& a) noexcept
			: Vector2D(a[0], a[1])
		{
		}
		template <typename U>
		constexpr Vector2D(const Array4<U>& a) noexcept
			: Vector2D(a[0], a[1])
		{
		}





		~Vector2D() = default;





	public:
		constexpr T& at(int dimension)
		{
			switch (dimension)
			{
			case 1:
				return x;
			case 2:
				return y;
			default:
				Assert(false, "The dimension must be between 1 and 2.");
				break;
			}
		}





		constexpr Vector2D<T> operator+() const
		{
			return *this;
		}

		constexpr Vector2D<T> operator-() const
		{
			return { -x, -y };
		}






#define _DEFINE_V2_OPERATOR_OP_ASSIGN_V2_(op)\
	template <typename U>\
	constexpr Vector2D<T>& operator##op##(const Vector2D<U>& v)\
	{\
		x ##op## static_cast<T>(v.x);\
		y ##op## static_cast<T>(v.y);\
		return *this;\
	}\
	template <typename U>\
	constexpr Vector2D<T>& operator##op##(const U& k)\
	{\
		x ##op## static_cast<T>(k);\
		y ##op## static_cast<T>(k);\
		return *this;\
	}

		_DEFINE_V2_OPERATOR_OP_ASSIGN_V2_(= )
		_DEFINE_V2_OPERATOR_OP_ASSIGN_V2_(+= )
		_DEFINE_V2_OPERATOR_OP_ASSIGN_V2_(-= )
		_DEFINE_V2_OPERATOR_OP_ASSIGN_V2_(*= )
		_DEFINE_V2_OPERATOR_OP_ASSIGN_V2_(/= )

#define _DEFINE_V2_OPERATOR_ASSIGN_ARRAY_(x)\
	template <typename U>\
	constexpr Vector2D<T>& operator=(const Array##x##<U>& v)\
	{\
		x = static_cast<T>(v[0]);\
		y = static_cast<T>(v[1]);\
		return *this;\
	}

		_DEFINE_V2_OPERATOR_ASSIGN_ARRAY_(2)
		_DEFINE_V2_OPERATOR_ASSIGN_ARRAY_(4)





		template <typename U>
		constexpr bool operator==(const Vector2D<U>& v) const
		{
			return x == static_cast<U>(v.x) && y == static_cast<U>(v.y);
		}
		template <typename U>
		constexpr bool operator!=(const Vector2D<U>& v) const
		{
			return x != static_cast<U>(v.x) || y != static_cast<U>(v.y);
		}





		[[nodiscard]] constexpr bool isZero() const noexcept
		{
			return x == 0 && y == 0;
		}





		template <typename X_, typename Y_>
		[[nodiscard]] T distance(X_ x, Y_ y) const noexcept
		{
			return std::sqrt(dot(Vector2D<T>(x, y) - (*this)));
		}
		template <typename U>
		[[nodiscard]] T distance(const Vector2D<U>& v) const noexcept
		{
			return distance(v.x, v.y);
		}





		template <typename X_, typename Y_>
		[[nodiscard]] constexpr T dot(X_ x, Y_ y) const noexcept
		{
			return this->x * static_cast<T>(x) + this->y * static_cast<T>(y);
		}
		template <typename U>
		[[nodiscard]] constexpr T dot(const Vector2D<U>& v) const noexcept
		{
			return dot(v.x, v.y);
		}





		[[nodiscard]] constexpr T lengthSquare() const noexcept
		{
			return dot(*this);
		}
		[[nodiscard]] T length() const noexcept
		{
			return std::sqrt(lengthSquare());
		}





		void normalize() noexcept
		{
			*this /= length();
		}
		[[nodiscard]] Vector2D<T> normalized() const noexcept
		{
			return *this / length();
		}





		[[nodiscard]] Vector2D<T> xx() const noexcept { return { x, x }; }
		[[nodiscard]] Vector2D<T> xy() const noexcept { return { x, y }; }
		[[nodiscard]] Vector2D<T> yx() const noexcept { return { y, x }; }
		[[nodiscard]] Vector2D<T> yy() const noexcept { return { y, y }; }
	};





#define _DEFINE_V2_OPERATOR_K_V2_OP_V2_(op)\
	template <typename T, typename U>\
	inline constexpr Vector2D<T> operator##op##(U k, const Vector2D<T>& v)\
	{\
		return { static_cast<T>(k)##op##v.x, static_cast<T>(k)##op##v.y };\
	}\
	template <typename T, typename U>\
	inline constexpr Vector2D<T> operator##op##(const Vector2D<T>& v1, const Vector2D<U>& v2)\
	{\
		return { v1.x##op##static_cast<T>(v2.x), v1.y##op##static_cast<T>(v2.y) };\
	}\
	template <typename T, typename U>\
	inline constexpr Vector2D<T> operator##op##(const Vector2D<T>& v, U k)\
	{\
		return { v.x##op##static_cast<T>(k), v.y##op##static_cast<T>(k) };\
	}

	_DEFINE_V2_OPERATOR_K_V2_OP_V2_(+)
	_DEFINE_V2_OPERATOR_K_V2_OP_V2_(-)
	_DEFINE_V2_OPERATOR_K_V2_OP_V2_(*)
	_DEFINE_V2_OPERATOR_K_V2_OP_V2_(/ )





	template <typename T, typename U>
	inline void assignVector2DToArray4(Array4<T>* a, const Vector2D<U>& v) noexcept
	{
		a->at(0) = v.x;
		a->at(1) = v.y;
	}
	template <typename T, typename U>
	inline void assignVector2DToArray2(Array2<T>* a, const Vector2D<U>& v) noexcept
	{
		a->at(0) = v.x;
		a->at(1) = v.y;
	}
}
