#pragma once
#include <string>
#include <vector>





namespace cpp
{
	class StringIDGenerator
	{
	private:
		const int m_length;
		const std::string m_elementCharacters;
	public:
		StringIDGenerator(int length, const std::string& elementCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
		virtual ~StringIDGenerator() = default;

		[[nodiscard]] int length() const;

		[[nodiscard]] std::string generate() const;
	};
}
