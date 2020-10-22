#pragma once
#include <tchar.h>
#include <windows.h>
#include <ctime>





#ifdef _DEBUG
#define Log(message, ...)\
	{\
		TCHAR c[512];\
		_stprintf_s(c, message, __VA_ARGS__ );\
		OutputDebugString(c);\
	}
#define LogEX(message, ...)\
	{\
		auto t = std::time(nullptr);\
		struct tm now;\
		localtime_s(&now, &t);\
		Log(("%d/%d/%d %02d:%02d:%02d "+std::string(__FILE__)+"("+std::to_string(__LINE__)+") "+__FUNCTION__+"() -> "+message+"\n").c_str(), now.tm_year+1900, now.tm_mon+1, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec)\
	}
#else
	#define Log(message, ...)
	#define LogEX(message, ...)
#endif
