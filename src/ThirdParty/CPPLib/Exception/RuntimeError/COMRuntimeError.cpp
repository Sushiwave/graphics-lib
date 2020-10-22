#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>





namespace cpp
{
	com_runtime_error::com_runtime_error(const std::string& exceptionType_, HRESULT errorCode_, const char* function_, const char* file_, uint64_t line_, const std::string& message_)
		: cpp::runtime_error(exceptionType_, function_, file_, line_, message_),
		  m_errorCode(errorCode_)
	{
	}
	com_runtime_error::com_runtime_error(HRESULT errorCode_, const char* function_, const char* file_, uint64_t line_, const std::string& message_)
		: cpp::com_runtime_error("COM Runtime", errorCode_, function_, file_, line_, message_)
	{
	}
	HRESULT com_runtime_error::errorCode() const noexcept
	{
		return m_errorCode;
	}
}
