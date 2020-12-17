#pragma once
#include <wrl/client.h>





#define SAFE_RELEASE(p) { if(p) { p->Release(); p = nullptr; } }





namespace cpp
{
	template< class T >
	using com_ptr = Microsoft::WRL::ComPtr<T>;
}
