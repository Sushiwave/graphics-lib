#pragma once
#include <ThirdParty/CPPLib/Exception/Base/Exception.hpp>

#include <stdexcept>





namespace cpp
{
	class runtime_error
		: public cpp::exception<std::runtime_error>
	{
	protected:
		explicit runtime_error(const std::string& exceptionType_, const char* function_, const char* file_, uint64_t line_, const std::string& message_);
	public:
		explicit runtime_error(const char* function_, const char* file_, uint64_t line_, const std::string& message_);
		virtual ~runtime_error() = default;
	};
}

#define RUNTIME_ERROR(message) cpp::runtime_error(__FUNCTION__, __FILE__, __LINE__, message)
