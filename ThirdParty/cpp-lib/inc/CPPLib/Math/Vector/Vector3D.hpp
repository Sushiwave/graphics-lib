#pragma once
#include <CPPLib/Math/Vector/Vector2D.hpp>
#include <CPPLib/DataStructure/Array/Array3.hpp>
#include <CPPLib/DataStructure/Array/Array4.hpp>
#include <CPPLib/Assert/Assert.hpp>





namespace cpp
{
	template <class T>
	struct Vector3D
	{
	public:
		T x, y, z;





	public:
		template <typename X_, typename Y_, typename Z_>
		constexpr Vector3D(X_ x, Y_ y, Z_ z) noexcept
			: x(static_cast<T>(x)),
			  y(static_cast<T>(y)),
			  z(static_cast<T>(z))
		{
		}
		constexpr Vector3D() noexcept
			: Vector3D(0, 0, 0)
		{
		}
		template <typename U>
		constexpr Vector3D(const Vector3D<U>& v) noexcept
			: Vector3D(v.x, v.y, v.z)
		{
		}
		constexpr Vector3D(T v) noexcept
			: Vector3D(v, v, v)
		{
		}
		template <typename XY_, typename Z_>
		constexpr Vector3D(const Vector2D<XY_>& xy, Z_ z) noexcept
			: Vector3D(xy.x, xy.y, z)
		{
		}
		template <typename X_, typename YZ_>
		constexpr Vector3D(X_ x, const Vector2D<YZ_>& yz) noexcept
			: Vector3D(x, yz.x, yz.y)
		{
		}
		template <typename U>
		constexpr Vector3D(const Array3<U>& a) noexcept
			: Vector3D(a[0], a[1], a[2])
		{
		}
		template <typename U>
		constexpr Vector3D(const Array4<U>& a) noexcept
			: Vector3D(a[0], a[1], a[2])
		{
		}




		~Vector3D() = default;





	public:
		constexpr T& at(int dimension)
		{
			switch (dimension)
			{
			case 1:
				return x;
			case 2:
				return y;
			case 3:
				return z;
			default:
				Assert(false, "The dimension must be between 1 and 3.");
				break;
			}
		}

		
		
		
		
		constexpr Vector3D<T> operator+() const
		{
			return *this;
		}
		constexpr Vector3D<T> operator-() const
		{
			return { -x, -y, -z };
		}





#define _DEFINE_V3_OPERATOR_OP_ASSIGN_V3_(op)\
	template <typename U>\
	constexpr Vector3D<T>& operator##op##(const Vector3D<U>& v)\
	{\
		x ##op## static_cast<T>(v.x);\
		y ##op## static_cast<T>(v.y);\
		z ##op## static_cast<T>(v.z);\
		return *this;\
	}\
	template <typename U>\
	constexpr Vector3D<T>& operator##op##(const U& k)\
	{\
		x ##op## static_cast<T>(k);\
		y ##op## static_cast<T>(k);\
		z ##op## static_cast<T>(k);\
		return *this;\
	}

		_DEFINE_V3_OPERATOR_OP_ASSIGN_V3_(=)
		_DEFINE_V3_OPERATOR_OP_ASSIGN_V3_(+=)
		_DEFINE_V3_OPERATOR_OP_ASSIGN_V3_(-=)
		_DEFINE_V3_OPERATOR_OP_ASSIGN_V3_(*=)
		_DEFINE_V3_OPERATOR_OP_ASSIGN_V3_(/=)

#define _DEFINE_V3_OPERATOR_ASSIGN_ARRAY_(x)\
	template <typename U>\
	constexpr Vector3D<T>& operator=(const Array##x##<U>& v)\
	{\
		x = static_cast<T>(v[0]);\
		y = static_cast<T>(v[1]);\
		z = static_cast<T>(v[2]);\
		return *this;\
	}
	
		_DEFINE_V3_OPERATOR_ASSIGN_ARRAY_(3)
		_DEFINE_V3_OPERATOR_ASSIGN_ARRAY_(4)





		template <typename U>
		constexpr bool operator==(const Vector3D<U>& v) const
		{
			return x == static_cast<T>(v.x) && y == static_cast<T>(v.y) && z == static_cast<T>(v.z);
		}
		template <typename U>
		constexpr bool operator!=(const Vector3D<U>& v) const
		{
			return x != static_cast<T>(v.x) || y != static_cast<T>(v.y) || z != static_cast<T>(v.z);
		}





		[[nodiscard]] constexpr bool isZero() const noexcept
		{
			return x == 0 && y == 0 && z == 0;
		}





		[[nodiscard]] constexpr T lengthSquare() const noexcept
		{
			return dot(*this);
		}
		[[nodiscard]] T length() const noexcept
		{
			return std::sqrt(lengthSquare());
		}





		template <typename X_, typename Y_, typename Z_>
		[[nodiscard]] constexpr T dot(X_ x, Y_ y, Z_ z) const noexcept
		{
			return this->x * static_cast<T>(x) + this->y * static_cast<T>(y) + this->z * static_cast<T>(z);
		}
		template <typename U>
		[[nodiscard]] constexpr T dot(const Vector3D<U>& v) const noexcept
		{
			return dot(v.x, v.y, v.z);
		}



		template <typename X_, typename Y_, typename Z_>
		[[nodiscard]] T distance(X_ x, Y_ y, Z_ z) const noexcept
		{
			return (Vector3D<T>(x, y, z)-(*this)).length();
		}
		template <typename U>
		[[nodiscard]] T distance(const Vector3D<U>& v) const noexcept
		{
			return distance(v.x, v.y, v.z);
		}





		template <typename X_, typename Y_, typename Z_>
		[[nodiscard]] constexpr Vector3D<T> cross(X_ x, Y_ y, Z_ z) const noexcept
		{
			return { this->y * static_cast<T>(z) - this->z * static_cast<T>(y), -this->x * static_cast<T>(z) + this->z * static_cast<T>(x), this->x * static_cast<T>(y) - this->y * static_cast<T>(x) };
		}
		template <typename U>
		[[nodiscard]] constexpr Vector3D<T> cross(const Vector3D<U>& v) const noexcept
		{
			return cross(v.x, v.y, v.z);
		}





		void normalize() noexcept
		{
			*this /= length();
		}
		[[nodiscard]] Vector3D<T> normalized() const noexcept
		{
			return *this / length();
		}





		[[nodiscard]] Vector2D<T> xx() const noexcept { return { x, x }; }
		[[nodiscard]] Vector2D<T> xy() const noexcept { return { x, y }; }
		[[nodiscard]] Vector2D<T> yx() const noexcept { return { y, x }; }
		[[nodiscard]] Vector2D<T> yy() const noexcept { return { y, y }; }





		[[nodiscard]] Vector3D<T> xxx() const noexcept { return { x, x, x }; }
		[[nodiscard]] Vector3D<T> xxy() const noexcept { return { x, x, y }; }
		[[nodiscard]] Vector3D<T> xxz() const noexcept { return { x, x, z }; }
		[[nodiscard]] Vector3D<T> xyx() const noexcept { return { x, y, x }; }
		[[nodiscard]] Vector3D<T> xyy() const noexcept { return { x, y, y }; }
		[[nodiscard]] Vector3D<T> xyz() const noexcept { return { x, y, z }; }
		[[nodiscard]] Vector3D<T> xzx() const noexcept { return { x, z, x }; }
		[[nodiscard]] Vector3D<T> xzy() const noexcept { return { x, z, y }; }
		[[nodiscard]] Vector3D<T> xzz() const noexcept { return { x, z, z }; }
		[[nodiscard]] Vector3D<T> yxx() const noexcept { return { y, x, x }; }
		[[nodiscard]] Vector3D<T> yxy() const noexcept { return { y, x, y }; }
		[[nodiscard]] Vector3D<T> yxz() const noexcept { return { y, x, z }; }
		[[nodiscard]] Vector3D<T> yyx() const noexcept { return { y, y, x }; }
		[[nodiscard]] Vector3D<T> yyy() const noexcept { return { y, y, y }; }
		[[nodiscard]] Vector3D<T> yyz() const noexcept { return { y, y, z }; }
		[[nodiscard]] Vector3D<T> yzx() const noexcept { return { y, z, x }; }
		[[nodiscard]] Vector3D<T> yzy() const noexcept { return { y, z, y }; }
		[[nodiscard]] Vector3D<T> yzz() const noexcept { return { y, z, z }; }
		[[nodiscard]] Vector3D<T> zxx() const noexcept { return { z, x, x }; }
		[[nodiscard]] Vector3D<T> zxy() const noexcept { return { z, x, y }; }
		[[nodiscard]] Vector3D<T> zxz() const noexcept { return { z, x, z }; }
		[[nodiscard]] Vector3D<T> zyx() const noexcept { return { z, y, x }; }
		[[nodiscard]] Vector3D<T> zyy() const noexcept { return { z, y, y }; }
		[[nodiscard]] Vector3D<T> zyz() const noexcept { return { z, y, z }; }
		[[nodiscard]] Vector3D<T> zzx() const noexcept { return { z, z, x }; }
		[[nodiscard]] Vector3D<T> zzy() const noexcept { return { z, z, y }; }
		[[nodiscard]] Vector3D<T> zzz() const noexcept { return { z, z, z }; }


	};





#define _DEFINE_V3_OPERATOR_K_V3_OP_V3_(op)\
	template <typename T, typename U>\
	inline constexpr Vector3D<T> operator##op##(U k, const Vector3D<T>& v)\
	{\
		return{ static_cast<T>(k)##op##v.x, static_cast<T>(k)##op##v.y, static_cast<T>(k)##op##v.z };\
	}\
	template <typename T, typename U>\
	inline constexpr Vector3D<T> operator##op##(const Vector3D<T>& v1, const Vector3D<U>& v2)\
	{\
		return{ v1.x##op##static_cast<T>(v2.x), v1.y##op##static_cast<T>(v2.y), v1.z##op##static_cast<T>(v2.z) };\
	}\
	template <typename T, typename U>\
	inline constexpr Vector3D<T> operator##op##(const Vector3D<T>& v, U k)\
	{\
		return{ v.x##op##static_cast<T>(k), v.y##op##static_cast<T>(k), v.z##op##static_cast<T>(k) };\
	}

	_DEFINE_V3_OPERATOR_K_V3_OP_V3_(+)
	_DEFINE_V3_OPERATOR_K_V3_OP_V3_(-)
	_DEFINE_V3_OPERATOR_K_V3_OP_V3_(*)
	_DEFINE_V3_OPERATOR_K_V3_OP_V3_(/)





	template <typename T, typename U>
	inline void assignVector3DToArray4(Array4<T>* a, const Vector3D<U>& v) noexcept
	{
		a->at(0) = v.x;
		a->at(1) = v.y;
		a->at(2) = v.z;
	}
	template <typename T, typename U>
	inline void assignVector3DToArray3(Array3<T>* a, const Vector3D<U>& v) noexcept
	{
		a->at(0) = v.x;
		a->at(1) = v.y;
		a->at(2) = v.z;
	}

	template <typename T, typename U>
	inline Vector3D<T> minVector(const Vector3D<T>& v1, const Vector3D<U>& v2) noexcept
	{
		auto minX = (std::min)(v1.x, v2.x);
		auto minY = (std::min)(v1.y, v2.y);
		auto minZ = (std::min)(v1.z, v2.z);
		return { minX, minY, minZ };
	}
	template <typename T, typename U>
	inline Vector3D<T> maxVector(const Vector3D<T>& v1, const Vector3D<U>& v2) noexcept
	{
		auto maxX = (std::max)(v1.x, v2.x);
		auto maxY = (std::max)(v1.y, v2.y);
		auto maxZ = (std::max)(v1.z, v2.z);
		return { maxX, maxY, maxZ };
	}

	template <typename T, typename U>
	inline constexpr Vector3D<T> reflect(const Vector3D<T>& in, const Vector3D<U>& normal) noexcept
	{
		return (in-normal*2.0*normal.dot(in)).normalized();
	}
	template <typename T>
	inline Vector3D<T> createTangent(const Vector3D<T>& normal) noexcept
	{
		if (abs(normal.x) > abs(normal.y))
		{
			return normal.cross(Vector3D<T>(0, 1, 0)).normalized();
		}
		else
		{
			return normal.cross(Vector3D<T>(1, 0, 0)).normalized();
		}
	}
	template <typename T>
	inline Vector3D<T> createBinormal(const Vector3D<T>& normal, const Vector3D<T>& tangent) noexcept
	{
		return normal.cross(tangent).normalized();
	}
	template <typename T>
	inline void createOrthoNormalBasis(const Vector3D<T>& normal, Vector3D<T>* pTangent, Vector3D<T>* pBinormal) noexcept
	{
		*pTangent = createTangent(normal);
		*pBinormal = createBinormal(normal, *pTangent);
	}
}
