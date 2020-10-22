#include <ThirdParty/CPPLib/Exception/RuntimeError/Base/RuntimeError.hpp>





namespace cpp
{
	runtime_error::runtime_error(const std::string& exceptionType_, const char* function_, const char* file_, uint64_t line_, const std::string& message_)
		: cpp::exception<std::runtime_error>(exceptionType_, function_, file_, line_, message_)
	{
	}
	runtime_error::runtime_error(const char* function_, const char* file_, uint64_t line_, const std::string& message_)
		: cpp::runtime_error("Runtime", function_, file_, line_, message_)
	{
	}
}
