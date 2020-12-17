#pragma once
#include <CPPLib/Math/Vector/Vector3D.hpp>
#include <CPPLib/Assert/Assert.hpp>





namespace cpp
{
	template <class T>
	struct Vector4D
	{
	public:
		T x, y, z, w;
	public:
		template <typename X_, typename Y_, typename Z_, typename W_>
		constexpr Vector4D(X_ x, Y_ y, Z_ z, W_ w) noexcept
			: x(static_cast<T>(x)),
			  y(static_cast<T>(y)),
			  z(static_cast<T>(z)),
			  w(static_cast<T>(w))
		{
		}
		constexpr Vector4D() noexcept
			: Vector4D(0, 0, 0, 0)
		{
		}
		template <typename U>
		constexpr Vector4D(const Vector4D<U>& v) noexcept
			: Vector4D(v.x, v.y, v.z, v.w)
		{
		}
		constexpr Vector4D(T v) noexcept
			: Vector4D(v, v, v, v)
		{
		}
		template <typename XY_, typename ZW_>
		constexpr Vector4D(const Vector2D<XY_>& xy, const Vector2D<ZW_>& zw) noexcept
			: Vector4D(xy.x, xy.y, zw.x, zw.y)
		{
		}
		template <typename XYZ_, typename W_>
		constexpr Vector4D(const Vector3D<XYZ_>& xyz, W_ w) noexcept
			: Vector4D(xyz.x, xyz.y, xyz.z, w)
		{
		}
		template <typename X_, typename YZW_>
		constexpr Vector4D(X_ x, const Vector3D<YZW_>& yzw) noexcept
			: Vector4D(x, yzw.x, yzw.y, yzw.z)
		{
		}
		template <typename U>
		constexpr Vector4D(const Array4<U> a) noexcept
			: Vector4D(a[0], a[1], a[2], a[3])
		{
		}





		~Vector4D() = default;





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
			case 4:
				return w;
			default:
				Assert(false, "The dimension must be between 1 and 4.");
				return x;
			}
		}





		constexpr Vector4D<T> operator+() const
		{
			return *this;
		}
		constexpr Vector4D<T> operator-() const
		{
			return { -x, -y, -z, -w };
		}






#define _DEFINE_V4_OPERATOR_OP_ASSIGN_V4_(op)\
	template <typename U>\
	constexpr Vector4D<T>& operator##op##(const Vector4D<U>& v)\
	{\
		x ##op## static_cast<T>(v.x);\
		y ##op## static_cast<T>(v.y);\
		z ##op## static_cast<T>(v.z);\
		w ##op## static_cast<T>(v.w);\
		return *this;\
	}\
	template <typename U>\
	constexpr Vector4D<T>& operator##op##(const U& k)\
	{\
		x ##op## static_cast<T>(k);\
		y ##op## static_cast<T>(k);\
		z ##op## static_cast<T>(k);\
		w ##op## static_cast<T>(k);\
		return *this;\
	}

		_DEFINE_V4_OPERATOR_OP_ASSIGN_V4_(=)
		_DEFINE_V4_OPERATOR_OP_ASSIGN_V4_(+=)
		_DEFINE_V4_OPERATOR_OP_ASSIGN_V4_(-=)
		_DEFINE_V4_OPERATOR_OP_ASSIGN_V4_(*=)
		_DEFINE_V4_OPERATOR_OP_ASSIGN_V4_(/=)

#define _DEFINE_V4_OPERATOR_ASSIGN_ARRAY_(x)\
	template <typename U>\
	constexpr Vector4D<T>& operator=(const Array##x##<U>& v)\
	{\
		x = static_cast<T>(v[0]);\
		y = static_cast<T>(v[1]);\
		z = static_cast<T>(v[2]);\
		w = static_cast<T>(v[3]);\
		return *this;\
	}

		_DEFINE_V4_OPERATOR_ASSIGN_ARRAY_(4)





		template <typename U>
		constexpr bool operator==(const Vector4D<U>& v) const
		{
			return x == v.x && y == v.y && z == v.z && w == v.w;
		}
		constexpr bool operator!=(const Vector4D<T>& v) const
		{
			return x != v.x || y != v.y || z != v.z || w != v.w;
		}





		[[nodiscard]] constexpr bool isZero() const noexcept
		{
			return x == 0 && y == 0 && z == 0 && w == 0;
		}





		template <typename X_, typename Y_, typename Z_, typename W_>
		[[nodiscard]] constexpr T dot(X_ x, Y_ y, Z_ z, W_ w) const noexcept
		{
			return this->x * static_cast<T>(x) + this->y * static_cast<T>(y) + this->z * static_cast<T>(z) + this->w * static_cast<T>(w);
		}
		template <typename U>
		[[nodiscard]] constexpr T dot(const Vector4D<U>& v) const noexcept
		{
			return dot(v.x, v.y, v.z, v.w);
		}





		template <typename X_, typename Y_, typename Z_, typename W_>
		[[nodiscard]] T distance(X_ x, Y_ y, Z_ z, W_ w) const noexcept
		{
			return std::sqrt(dot(Vector4D<T>(x, y, z, w) - (*this)));
		}
		template <typename U>
		[[nodiscard]] T distance(const Vector4D<U>& v) const noexcept
		{
			return distance(v.x, v.y, v.z, v.w);
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
		[[nodiscard]] Vector4D<T> normalized() const noexcept
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





		[[nodiscard]] Vector4D<T> xxxx() const noexcept { return { y, x, x, x }; }
		[[nodiscard]] Vector4D<T> xxxy() const noexcept { return { y, x, x, y }; }
		[[nodiscard]] Vector4D<T> xxxz() const noexcept { return { y, x, x, z }; }
		[[nodiscard]] Vector4D<T> xxxw() const noexcept { return { y, x, x, w }; }
		[[nodiscard]] Vector4D<T> xxyx() const noexcept { return { y, x, y, x }; }
		[[nodiscard]] Vector4D<T> xxyy() const noexcept { return { y, x, y, y }; }
		[[nodiscard]] Vector4D<T> xxyz() const noexcept { return { y, x, y, z }; }
		[[nodiscard]] Vector4D<T> xxyw() const noexcept { return { y, x, y, w }; }
		[[nodiscard]] Vector4D<T> xxzx() const noexcept { return { y, x, z, x }; }
		[[nodiscard]] Vector4D<T> xxzy() const noexcept { return { y, x, z, y }; }
		[[nodiscard]] Vector4D<T> xxzz() const noexcept { return { y, x, z, z }; }
		[[nodiscard]] Vector4D<T> xxzw() const noexcept { return { y, x, z, w }; }
		[[nodiscard]] Vector4D<T> xxwx() const noexcept { return { y, x, w, x }; }
		[[nodiscard]] Vector4D<T> xxwy() const noexcept { return { y, x, w, y }; }
		[[nodiscard]] Vector4D<T> xxwz() const noexcept { return { y, x, w, z }; }
		[[nodiscard]] Vector4D<T> xxww() const noexcept { return { y, x, w, w }; }
		
		[[nodiscard]] Vector4D<T> xyxx() const noexcept { return { y, y, x, x }; }
		[[nodiscard]] Vector4D<T> xyxy() const noexcept { return { y, y, x, y }; }
		[[nodiscard]] Vector4D<T> xyxz() const noexcept { return { y, y, x, z }; }
		[[nodiscard]] Vector4D<T> xyxw() const noexcept { return { y, y, x, w }; }
		[[nodiscard]] Vector4D<T> xyyx() const noexcept { return { y, y, y, x }; }
		[[nodiscard]] Vector4D<T> xyyy() const noexcept { return { y, y, y, y }; }
		[[nodiscard]] Vector4D<T> xyyz() const noexcept { return { y, y, y, z }; }
		[[nodiscard]] Vector4D<T> xyyw() const noexcept { return { y, y, y, w }; }
		[[nodiscard]] Vector4D<T> xyzx() const noexcept { return { y, y, z, x }; }
		[[nodiscard]] Vector4D<T> xyzy() const noexcept { return { y, y, z, y }; }
		[[nodiscard]] Vector4D<T> xyzz() const noexcept { return { y, y, z, z }; }
		[[nodiscard]] Vector4D<T> xyzw() const noexcept { return { y, y, z, w }; }
		[[nodiscard]] Vector4D<T> xywx() const noexcept { return { y, y, w, x }; }
		[[nodiscard]] Vector4D<T> xywy() const noexcept { return { y, y, w, y }; }
		[[nodiscard]] Vector4D<T> xywz() const noexcept { return { y, y, w, z }; }
		[[nodiscard]] Vector4D<T> xyww() const noexcept { return { y, y, w, w }; }

		[[nodiscard]] Vector4D<T> xzxx() const noexcept { return { y, z, x, x }; }
		[[nodiscard]] Vector4D<T> xzxy() const noexcept { return { y, z, x, y }; }
		[[nodiscard]] Vector4D<T> xzxz() const noexcept { return { y, z, x, z }; }
		[[nodiscard]] Vector4D<T> xzxw() const noexcept { return { y, z, x, w }; }
		[[nodiscard]] Vector4D<T> xzyx() const noexcept { return { y, z, y, x }; }
		[[nodiscard]] Vector4D<T> xzyy() const noexcept { return { y, z, y, y }; }
		[[nodiscard]] Vector4D<T> xzyz() const noexcept { return { y, z, y, z }; }
		[[nodiscard]] Vector4D<T> xzyw() const noexcept { return { y, z, y, w }; }
		[[nodiscard]] Vector4D<T> xzzx() const noexcept { return { y, z, z, x }; }
		[[nodiscard]] Vector4D<T> xzzy() const noexcept { return { y, z, z, y }; }
		[[nodiscard]] Vector4D<T> xzzz() const noexcept { return { y, z, z, z }; }
		[[nodiscard]] Vector4D<T> xzzw() const noexcept { return { y, z, z, w }; }
		[[nodiscard]] Vector4D<T> xzwx() const noexcept { return { y, z, w, x }; }
		[[nodiscard]] Vector4D<T> xzwy() const noexcept { return { y, z, w, y }; }
		[[nodiscard]] Vector4D<T> xzwz() const noexcept { return { y, z, w, z }; }
		[[nodiscard]] Vector4D<T> xzww() const noexcept { return { y, z, w, w }; }

		[[nodiscard]] Vector4D<T> xwxx() const noexcept { return { y, w, x, x }; }
		[[nodiscard]] Vector4D<T> xwxy() const noexcept { return { y, w, x, y }; }
		[[nodiscard]] Vector4D<T> xwxz() const noexcept { return { y, w, x, z }; }
		[[nodiscard]] Vector4D<T> xwxw() const noexcept { return { y, w, x, w }; }
		[[nodiscard]] Vector4D<T> xwyx() const noexcept { return { y, w, y, x }; }
		[[nodiscard]] Vector4D<T> xwyy() const noexcept { return { y, w, y, y }; }
		[[nodiscard]] Vector4D<T> xwyz() const noexcept { return { y, w, y, z }; }
		[[nodiscard]] Vector4D<T> xwyw() const noexcept { return { y, w, y, w }; }
		[[nodiscard]] Vector4D<T> xwzx() const noexcept { return { y, w, z, x }; }
		[[nodiscard]] Vector4D<T> xwzy() const noexcept { return { y, w, z, y }; }
		[[nodiscard]] Vector4D<T> xwzz() const noexcept { return { y, w, z, z }; }
		[[nodiscard]] Vector4D<T> xwzw() const noexcept { return { y, w, z, w }; }
		[[nodiscard]] Vector4D<T> xwwx() const noexcept { return { y, w, w, x }; }
		[[nodiscard]] Vector4D<T> xwwy() const noexcept { return { y, w, w, y }; }
		[[nodiscard]] Vector4D<T> xwwz() const noexcept { return { y, w, w, z }; }
		[[nodiscard]] Vector4D<T> xwww() const noexcept { return { y, w, w, w }; }



		[[nodiscard]] Vector4D<T> yxxx() const noexcept { return { y, x, x, x }; }
		[[nodiscard]] Vector4D<T> yxxy() const noexcept { return { y, x, x, y }; }
		[[nodiscard]] Vector4D<T> yxxz() const noexcept { return { y, x, x, z }; }
		[[nodiscard]] Vector4D<T> yxxw() const noexcept { return { y, x, x, w }; }
		[[nodiscard]] Vector4D<T> yxyx() const noexcept { return { y, x, y, x }; }
		[[nodiscard]] Vector4D<T> yxyy() const noexcept { return { y, x, y, y }; }
		[[nodiscard]] Vector4D<T> yxyz() const noexcept { return { y, x, y, z }; }
		[[nodiscard]] Vector4D<T> yxyw() const noexcept { return { y, x, y, w }; }
		[[nodiscard]] Vector4D<T> yxzx() const noexcept { return { y, x, z, x }; }
		[[nodiscard]] Vector4D<T> yxzy() const noexcept { return { y, x, z, y }; }
		[[nodiscard]] Vector4D<T> yxzz() const noexcept { return { y, x, z, z }; }
		[[nodiscard]] Vector4D<T> yxzw() const noexcept { return { y, x, z, w }; }
		[[nodiscard]] Vector4D<T> yxwx() const noexcept { return { y, x, w, x }; }
		[[nodiscard]] Vector4D<T> yxwy() const noexcept { return { y, x, w, y }; }
		[[nodiscard]] Vector4D<T> yxwz() const noexcept { return { y, x, w, z }; }
		[[nodiscard]] Vector4D<T> yxww() const noexcept { return { y, x, w, w }; }

		[[nodiscard]] Vector4D<T> yyxx() const noexcept { return { y, y, x, x }; }
		[[nodiscard]] Vector4D<T> yyxy() const noexcept { return { y, y, x, y }; }
		[[nodiscard]] Vector4D<T> yyxz() const noexcept { return { y, y, x, z }; }
		[[nodiscard]] Vector4D<T> yyxw() const noexcept { return { y, y, x, w }; }
		[[nodiscard]] Vector4D<T> yyyx() const noexcept { return { y, y, y, x }; }
		[[nodiscard]] Vector4D<T> yyyy() const noexcept { return { y, y, y, y }; }
		[[nodiscard]] Vector4D<T> yyyz() const noexcept { return { y, y, y, z }; }
		[[nodiscard]] Vector4D<T> yyyw() const noexcept { return { y, y, y, w }; }
		[[nodiscard]] Vector4D<T> yyzx() const noexcept { return { y, y, z, x }; }
		[[nodiscard]] Vector4D<T> yyzy() const noexcept { return { y, y, z, y }; }
		[[nodiscard]] Vector4D<T> yyzz() const noexcept { return { y, y, z, z }; }
		[[nodiscard]] Vector4D<T> yyzw() const noexcept { return { y, y, z, w }; }
		[[nodiscard]] Vector4D<T> yywx() const noexcept { return { y, y, w, x }; }
		[[nodiscard]] Vector4D<T> yywy() const noexcept { return { y, y, w, y }; }
		[[nodiscard]] Vector4D<T> yywz() const noexcept { return { y, y, w, z }; }
		[[nodiscard]] Vector4D<T> yyww() const noexcept { return { y, y, w, w }; }

		[[nodiscard]] Vector4D<T> yzxx() const noexcept { return { y, z, x, x }; }
		[[nodiscard]] Vector4D<T> yzxy() const noexcept { return { y, z, x, y }; }
		[[nodiscard]] Vector4D<T> yzxz() const noexcept { return { y, z, x, z }; }
		[[nodiscard]] Vector4D<T> yzxw() const noexcept { return { y, z, x, w }; }
		[[nodiscard]] Vector4D<T> yzyx() const noexcept { return { y, z, y, x }; }
		[[nodiscard]] Vector4D<T> yzyy() const noexcept { return { y, z, y, y }; }
		[[nodiscard]] Vector4D<T> yzyz() const noexcept { return { y, z, y, z }; }
		[[nodiscard]] Vector4D<T> yzyw() const noexcept { return { y, z, y, w }; }
		[[nodiscard]] Vector4D<T> yzzx() const noexcept { return { y, z, z, x }; }
		[[nodiscard]] Vector4D<T> yzzy() const noexcept { return { y, z, z, y }; }
		[[nodiscard]] Vector4D<T> yzzz() const noexcept { return { y, z, z, z }; }
		[[nodiscard]] Vector4D<T> yzzw() const noexcept { return { y, z, z, w }; }
		[[nodiscard]] Vector4D<T> yzwx() const noexcept { return { y, z, w, x }; }
		[[nodiscard]] Vector4D<T> yzwy() const noexcept { return { y, z, w, y }; }
		[[nodiscard]] Vector4D<T> yzwz() const noexcept { return { y, z, w, z }; }
		[[nodiscard]] Vector4D<T> yzww() const noexcept { return { y, z, w, w }; }

		[[nodiscard]] Vector4D<T> ywxx() const noexcept { return { y, w, x, x }; }
		[[nodiscard]] Vector4D<T> ywxy() const noexcept { return { y, w, x, y }; }
		[[nodiscard]] Vector4D<T> ywxz() const noexcept { return { y, w, x, z }; }
		[[nodiscard]] Vector4D<T> ywxw() const noexcept { return { y, w, x, w }; }
		[[nodiscard]] Vector4D<T> ywyx() const noexcept { return { y, w, y, x }; }
		[[nodiscard]] Vector4D<T> ywyy() const noexcept { return { y, w, y, y }; }
		[[nodiscard]] Vector4D<T> ywyz() const noexcept { return { y, w, y, z }; }
		[[nodiscard]] Vector4D<T> ywyw() const noexcept { return { y, w, y, w }; }
		[[nodiscard]] Vector4D<T> ywzx() const noexcept { return { y, w, z, x }; }
		[[nodiscard]] Vector4D<T> ywzy() const noexcept { return { y, w, z, y }; }
		[[nodiscard]] Vector4D<T> ywzz() const noexcept { return { y, w, z, z }; }
		[[nodiscard]] Vector4D<T> ywzw() const noexcept { return { y, w, z, w }; }
		[[nodiscard]] Vector4D<T> ywwx() const noexcept { return { y, w, w, x }; }
		[[nodiscard]] Vector4D<T> ywwy() const noexcept { return { y, w, w, y }; }
		[[nodiscard]] Vector4D<T> ywwz() const noexcept { return { y, w, w, z }; }
		[[nodiscard]] Vector4D<T> ywww() const noexcept { return { y, w, w, w }; }



		[[nodiscard]] Vector4D<T> zxxx() const noexcept { return { z, x, x, x }; }
		[[nodiscard]] Vector4D<T> zxxy() const noexcept { return { z, x, x, y }; }
		[[nodiscard]] Vector4D<T> zxxz() const noexcept { return { z, x, x, z }; }
		[[nodiscard]] Vector4D<T> zxxw() const noexcept { return { z, x, x, w }; }
		[[nodiscard]] Vector4D<T> zxyx() const noexcept { return { z, x, y, x }; }
		[[nodiscard]] Vector4D<T> zxyy() const noexcept { return { z, x, y, y }; }
		[[nodiscard]] Vector4D<T> zxyz() const noexcept { return { z, x, y, z }; }
		[[nodiscard]] Vector4D<T> zxyw() const noexcept { return { z, x, y, w }; }
		[[nodiscard]] Vector4D<T> zxzx() const noexcept { return { z, x, z, x }; }
		[[nodiscard]] Vector4D<T> zxzy() const noexcept { return { z, x, z, y }; }
		[[nodiscard]] Vector4D<T> zxzz() const noexcept { return { z, x, z, z }; }
		[[nodiscard]] Vector4D<T> zxzw() const noexcept { return { z, x, z, w }; }
		[[nodiscard]] Vector4D<T> zxwx() const noexcept { return { z, x, w, x }; }
		[[nodiscard]] Vector4D<T> zxwy() const noexcept { return { z, x, w, y }; }
		[[nodiscard]] Vector4D<T> zxwz() const noexcept { return { z, x, w, z }; }
		[[nodiscard]] Vector4D<T> zxww() const noexcept { return { z, x, w, w }; }

		[[nodiscard]] Vector4D<T> zyxx() const noexcept { return { z, y, x, x }; }
		[[nodiscard]] Vector4D<T> zyxy() const noexcept { return { z, y, x, y }; }
		[[nodiscard]] Vector4D<T> zyxz() const noexcept { return { z, y, x, z }; }
		[[nodiscard]] Vector4D<T> zyxw() const noexcept { return { z, y, x, w }; }
		[[nodiscard]] Vector4D<T> zyyx() const noexcept { return { z, y, y, x }; }
		[[nodiscard]] Vector4D<T> zyyy() const noexcept { return { z, y, y, y }; }
		[[nodiscard]] Vector4D<T> zyyz() const noexcept { return { z, y, y, z }; }
		[[nodiscard]] Vector4D<T> zyyw() const noexcept { return { z, y, y, w }; }
		[[nodiscard]] Vector4D<T> zyzx() const noexcept { return { z, y, z, x }; }
		[[nodiscard]] Vector4D<T> zyzy() const noexcept { return { z, y, z, y }; }
		[[nodiscard]] Vector4D<T> zyzz() const noexcept { return { z, y, z, z }; }
		[[nodiscard]] Vector4D<T> zyzw() const noexcept { return { z, y, z, w }; }
		[[nodiscard]] Vector4D<T> zywx() const noexcept { return { z, y, w, x }; }
		[[nodiscard]] Vector4D<T> zywy() const noexcept { return { z, y, w, y }; }
		[[nodiscard]] Vector4D<T> zywz() const noexcept { return { z, y, w, z }; }
		[[nodiscard]] Vector4D<T> zyww() const noexcept { return { z, y, w, w }; }

		[[nodiscard]] Vector4D<T> zzxx() const noexcept { return { z, z, x, x }; }
		[[nodiscard]] Vector4D<T> zzxy() const noexcept { return { z, z, x, y }; }
		[[nodiscard]] Vector4D<T> zzxz() const noexcept { return { z, z, x, z }; }
		[[nodiscard]] Vector4D<T> zzxw() const noexcept { return { z, z, x, w }; }
		[[nodiscard]] Vector4D<T> zzyx() const noexcept { return { z, z, y, x }; }
		[[nodiscard]] Vector4D<T> zzyy() const noexcept { return { z, z, y, y }; }
		[[nodiscard]] Vector4D<T> zzyz() const noexcept { return { z, z, y, z }; }
		[[nodiscard]] Vector4D<T> zzyw() const noexcept { return { z, z, y, w }; }
		[[nodiscard]] Vector4D<T> zzzx() const noexcept { return { z, z, z, x }; }
		[[nodiscard]] Vector4D<T> zzzy() const noexcept { return { z, z, z, y }; }
		[[nodiscard]] Vector4D<T> zzzz() const noexcept { return { z, z, z, z }; }
		[[nodiscard]] Vector4D<T> zzzw() const noexcept { return { z, z, z, w }; }
		[[nodiscard]] Vector4D<T> zzwx() const noexcept { return { z, z, w, x }; }
		[[nodiscard]] Vector4D<T> zzwy() const noexcept { return { z, z, w, y }; }
		[[nodiscard]] Vector4D<T> zzwz() const noexcept { return { z, z, w, z }; }
		[[nodiscard]] Vector4D<T> zzww() const noexcept { return { z, z, w, w }; }

		[[nodiscard]] Vector4D<T> zwxx() const noexcept { return { z, w, x, x }; }
		[[nodiscard]] Vector4D<T> zwxy() const noexcept { return { z, w, x, y }; }
		[[nodiscard]] Vector4D<T> zwxz() const noexcept { return { z, w, x, z }; }
		[[nodiscard]] Vector4D<T> zwxw() const noexcept { return { z, w, x, w }; }
		[[nodiscard]] Vector4D<T> zwyx() const noexcept { return { z, w, y, x }; }
		[[nodiscard]] Vector4D<T> zwyy() const noexcept { return { z, w, y, y }; }
		[[nodiscard]] Vector4D<T> zwyz() const noexcept { return { z, w, y, z }; }
		[[nodiscard]] Vector4D<T> zwyw() const noexcept { return { z, w, y, w }; }
		[[nodiscard]] Vector4D<T> zwzx() const noexcept { return { z, w, z, x }; }
		[[nodiscard]] Vector4D<T> zwzy() const noexcept { return { z, w, z, y }; }
		[[nodiscard]] Vector4D<T> zwzz() const noexcept { return { z, w, z, z }; }
		[[nodiscard]] Vector4D<T> zwzw() const noexcept { return { z, w, z, w }; }
		[[nodiscard]] Vector4D<T> zwwx() const noexcept { return { z, w, w, x }; }
		[[nodiscard]] Vector4D<T> zwwy() const noexcept { return { z, w, w, y }; }
		[[nodiscard]] Vector4D<T> zwwz() const noexcept { return { z, w, w, z }; }
		[[nodiscard]] Vector4D<T> zwww() const noexcept { return { z, w, w, w }; }



		[[nodiscard]] Vector4D<T> wxxx() const noexcept { return { w, x, x, x }; }
		[[nodiscard]] Vector4D<T> wxxy() const noexcept { return { w, x, x, y }; }
		[[nodiscard]] Vector4D<T> wxxz() const noexcept { return { w, x, x, z }; }
		[[nodiscard]] Vector4D<T> wxxw() const noexcept { return { w, x, x, w }; }
		[[nodiscard]] Vector4D<T> wxyx() const noexcept { return { w, x, y, x }; }
		[[nodiscard]] Vector4D<T> wxyy() const noexcept { return { w, x, y, y }; }
		[[nodiscard]] Vector4D<T> wxyz() const noexcept { return { w, x, y, z }; }
		[[nodiscard]] Vector4D<T> wxyw() const noexcept { return { w, x, y, w }; }
		[[nodiscard]] Vector4D<T> wxzx() const noexcept { return { w, x, z, x }; }
		[[nodiscard]] Vector4D<T> wxzy() const noexcept { return { w, x, z, y }; }
		[[nodiscard]] Vector4D<T> wxzz() const noexcept { return { w, x, z, z }; }
		[[nodiscard]] Vector4D<T> wxzw() const noexcept { return { w, x, z, w }; }
		[[nodiscard]] Vector4D<T> wxwx() const noexcept { return { w, x, w, x }; }
		[[nodiscard]] Vector4D<T> wxwy() const noexcept { return { w, x, w, y }; }
		[[nodiscard]] Vector4D<T> wxwz() const noexcept { return { w, x, w, z }; }
		[[nodiscard]] Vector4D<T> wxww() const noexcept { return { w, x, w, w }; }

		[[nodiscard]] Vector4D<T> wyxx() const noexcept { return { w, y, x, x }; }
		[[nodiscard]] Vector4D<T> wyxy() const noexcept { return { w, y, x, y }; }
		[[nodiscard]] Vector4D<T> wyxz() const noexcept { return { w, y, x, z }; }
		[[nodiscard]] Vector4D<T> wyxw() const noexcept { return { w, y, x, w }; }
		[[nodiscard]] Vector4D<T> wyyx() const noexcept { return { w, y, y, x }; }
		[[nodiscard]] Vector4D<T> wyyy() const noexcept { return { w, y, y, y }; }
		[[nodiscard]] Vector4D<T> wyyz() const noexcept { return { w, y, y, z }; }
		[[nodiscard]] Vector4D<T> wyyw() const noexcept { return { w, y, y, w }; }
		[[nodiscard]] Vector4D<T> wyzx() const noexcept { return { w, y, z, x }; }
		[[nodiscard]] Vector4D<T> wyzy() const noexcept { return { w, y, z, y }; }
		[[nodiscard]] Vector4D<T> wyzz() const noexcept { return { w, y, z, z }; }
		[[nodiscard]] Vector4D<T> wyzw() const noexcept { return { w, y, z, w }; }
		[[nodiscard]] Vector4D<T> wywx() const noexcept { return { w, y, w, x }; }
		[[nodiscard]] Vector4D<T> wywy() const noexcept { return { w, y, w, y }; }
		[[nodiscard]] Vector4D<T> wywz() const noexcept { return { w, y, w, z }; }
		[[nodiscard]] Vector4D<T> wyww() const noexcept { return { w, y, w, w }; }

		[[nodiscard]] Vector4D<T> wzxx() const noexcept { return { w, z, x, x }; }
		[[nodiscard]] Vector4D<T> wzxy() const noexcept { return { w, z, x, y }; }
		[[nodiscard]] Vector4D<T> wzxz() const noexcept { return { w, z, x, z }; }
		[[nodiscard]] Vector4D<T> wzxw() const noexcept { return { w, z, x, w }; }
		[[nodiscard]] Vector4D<T> wzyx() const noexcept { return { w, z, y, x }; }
		[[nodiscard]] Vector4D<T> wzyy() const noexcept { return { w, z, y, y }; }
		[[nodiscard]] Vector4D<T> wzyz() const noexcept { return { w, z, y, z }; }
		[[nodiscard]] Vector4D<T> wzyw() const noexcept { return { w, z, y, w }; }
		[[nodiscard]] Vector4D<T> wzzx() const noexcept { return { w, z, z, x }; }
		[[nodiscard]] Vector4D<T> wzzy() const noexcept { return { w, z, z, y }; }
		[[nodiscard]] Vector4D<T> wzzz() const noexcept { return { w, z, z, z }; }
		[[nodiscard]] Vector4D<T> wzzw() const noexcept { return { w, z, z, w }; }
		[[nodiscard]] Vector4D<T> wzwx() const noexcept { return { w, z, w, x }; }
		[[nodiscard]] Vector4D<T> wzwy() const noexcept { return { w, z, w, y }; }
		[[nodiscard]] Vector4D<T> wzwz() const noexcept { return { w, z, w, z }; }
		[[nodiscard]] Vector4D<T> wzww() const noexcept { return { w, z, w, w }; }

		[[nodiscard]] Vector4D<T> wwxx() const noexcept { return { w, w, x, x }; }
		[[nodiscard]] Vector4D<T> wwxy() const noexcept { return { w, w, x, y }; }
		[[nodiscard]] Vector4D<T> wwxz() const noexcept { return { w, w, x, z }; }
		[[nodiscard]] Vector4D<T> wwxw() const noexcept { return { w, w, x, w }; }
		[[nodiscard]] Vector4D<T> wwyx() const noexcept { return { w, w, y, x }; }
		[[nodiscard]] Vector4D<T> wwyy() const noexcept { return { w, w, y, y }; }
		[[nodiscard]] Vector4D<T> wwyz() const noexcept { return { w, w, y, z }; }
		[[nodiscard]] Vector4D<T> wwyw() const noexcept { return { w, w, y, w }; }
		[[nodiscard]] Vector4D<T> wwzx() const noexcept { return { w, w, z, x }; }
		[[nodiscard]] Vector4D<T> wwzy() const noexcept { return { w, w, z, y }; }
		[[nodiscard]] Vector4D<T> wwzz() const noexcept { return { w, w, z, z }; }
		[[nodiscard]] Vector4D<T> wwzw() const noexcept { return { w, w, z, w }; }
		[[nodiscard]] Vector4D<T> wwwx() const noexcept { return { w, w, w, x }; }
		[[nodiscard]] Vector4D<T> wwwy() const noexcept { return { w, w, w, y }; }
		[[nodiscard]] Vector4D<T> wwwz() const noexcept { return { w, w, w, z }; }
		[[nodiscard]] Vector4D<T> wwww() const noexcept { return { w, w, w, w }; }
	};





#define _DEFINE_V4_OPERATOR_K_V4_OP_V4_(op)\
	template <typename T, typename U>\
	inline constexpr Vector4D<T> operator##op##(U k, const Vector4D<T>& v)\
	{\
		return{ static_cast<T>(k)##op##v.x, static_cast<T>(k)##op##v.y, static_cast<T>(k)##op##v.z, static_cast<T>(k)##op##v.w };\
	}\
	template <typename T, typename U>\
	inline constexpr Vector4D<T> operator##op##(const Vector4D<T>& v1, const Vector4D<U>& v2)\
	{\
		return{ v1.x##op##static_cast<T>(v2.x), v1.y##op##static_cast<T>(v2.y), v1.z##op##static_cast<T>(v2.z), v1.w##op##static_cast<T>(v2.w) };\
	}\
	template <typename T, typename U>\
	inline constexpr Vector4D<T> operator##op##(const Vector4D<T>& v, U k)\
	{\
		return{ v.x##op##static_cast<T>(k), v.y##op##static_cast<T>(k), v.z##op##static_cast<T>(k), v.w##op##static_cast<T>(k) };\
	}

	_DEFINE_V4_OPERATOR_K_V4_OP_V4_(+)
	_DEFINE_V4_OPERATOR_K_V4_OP_V4_(-)
	_DEFINE_V4_OPERATOR_K_V4_OP_V4_(*)
	_DEFINE_V4_OPERATOR_K_V4_OP_V4_(/ )





	template <typename T, typename U>
	inline void assignVector4DToArray4(Array4<T>* a, const Vector4D<U>& v) noexcept
	{
		a->at(0) = v.x;
		a->at(1) = v.y;
		a->at(2) = v.z;
		a->at(3) = v.w;
	}
}