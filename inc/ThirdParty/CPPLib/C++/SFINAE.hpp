#pragma once
#include <type_traits>





template <bool isEnabled, typename ReturnValType_ = std::nullptr_t>
using SFINAE_enable = std::enable_if_t<isEnabled, ReturnValType_>;

template <typename T1, typename T2, typename ReturnValType_ = std::nullptr_t>
using SFINAE_is_same = SFINAE_enable<std::is_same<T1, T2>::value, ReturnValType_>;
template <typename T1, typename T2, typename ReturnValType_ = std::nullptr_t>
using SFINAE_is_not_same = SFINAE_enable<!std::is_same<T1, T2>::value, ReturnValType_>;


#define SYSTEM_DEFINE_HAS_MEMBER(className, memberName)                      \
	template < typename T >                                                  \
	class has_##className                                                    \
	{																	     \
	private:														         \
		template <typename U>										         \
		static auto check(U x)->decltype(x.##memberName, std::true_type{});  \
		static std::false_type check(...);								     \
	public:															         \
		static bool const value = decltype(check(std::declval<T>()))::value; \
	}




#define DEFINE_HAS_FUNC(funcName) SYSTEM_DEFINE_HAS_MEMBER(funcName, funcName##())
#define DEFINE_HAS_MEMBER(memberName) SYSTEM_DEFINE_HAS_MEMBER(memberName, memberName)



#define SYSTEM_DEFINE_SFINAE_HAS_MEMBER(MACRO_DEFINE_HAS_MEMBER, memberName)     \
	MACRO_DEFINE_HAS_MEMBER(memberName);								         \
	template <typename T>           										     \
	using SFINAE_has_##memberName   = SFINAE_enable<has_##memberName<T>::value>; \
	template <typename T>           										     \
	using SFINAE_hasnt_##memberName = SFINAE_enable<!has_##memberName<T>::value> \



#define DEFINE_SFINAE_HAS_FUNC(funcName) SYSTEM_DEFINE_SFINAE_HAS_MEMBER(DEFINE_HAS_FUNC, funcName)
#define DEFINE_SFINAE_HAS_MEMBER(memberName) SYSTEM_DEFINE_SFINAE_HAS_MEMBER(DEFINE_HAS_MEMBER, memberName)
