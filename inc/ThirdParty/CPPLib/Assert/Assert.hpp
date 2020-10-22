#pragma once
#include <stdio.h>
#include <string>





#ifdef _DEBUG
#define Assert(expr, message, ... )\
	{\
		constexpr auto SIZE = 512;\
		char c[SIZE];\
		sprintf_s(c, SIZE, (std::string(__FILE__)+"("+std::to_string(__LINE__)+") "+__FUNCTION__+"() -> "+message+"\n").c_str(), __VA_ARGS__);\
		_ASSERT_EXPR(expr, c);\
	}
#else
#define Assert(str, ...)
#endif