#pragma once
#include <ThirdParty/CPPLib/Exception/RuntimeError/Base/RuntimeError.hpp>
#include <d3d.h>





namespace cpp
{
	class com_runtime_error
		: public cpp::runtime_error
	{
	private:
		HRESULT m_errorCode;
	protected:
		explicit com_runtime_error(const std::string& exceptionType, HRESULT errorCode, const char* function_, const char* file_, uint64_t line_, const std::string& message_);
	public:
		explicit com_runtime_error(HRESULT errorCode, const char* function_, const char* file_, uint64_t line_, const std::string& message_);
		virtual ~com_runtime_error() = default;

		[[nodiscard]] HRESULT errorCode() const noexcept;
	};
}

#define COM_RUNTIME_ERROR(errorCodeHRESULT, message) cpp::com_runtime_error(errorCodeHRESULT, __FUNCTION__, __FILE__, __LINE__, message)
