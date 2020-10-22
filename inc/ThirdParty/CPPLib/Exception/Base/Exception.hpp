#pragma once
#include <string>





namespace cpp
{
	template <typename exception_>
	class exception
		: public exception_
	{
	private:
		std::string m_exceptionType;
		std::string m_function;
		std::string m_file;
		std::string m_message;
	public:
		explicit exception(std::string exceptionType_, const char* function_, const char* file_, uint64_t line_, const std::string& message_)
			: exception_(message_),
			  m_exceptionType(exceptionType_),
			  m_function(std::string(function_) + "()"),
			  m_file(std::string(file_) + "(" + std::to_string(line_) + ")"),
			  m_message(m_exceptionType + " exception at " + m_function + " in " + m_file + " -> " + message_)
		{
		}
		virtual ~exception() = default;



		[[nodiscard]] std::string exceptionType() const noexcept
		{
			return m_exceptionType;
		}
		[[nodiscard]] std::string function() const noexcept
		{
			return m_function;
		}
		[[nodiscard]] std::string file() const noexcept
		{
			return m_file;
		}
		[[nodiscard]] std::string message() const noexcept
		{
			return m_message;
		}
	};
}
