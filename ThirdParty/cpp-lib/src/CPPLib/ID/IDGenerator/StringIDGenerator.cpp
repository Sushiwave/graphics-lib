#include <CPPLib/ID/IDGenerator/StringIDGenerator.hpp>
#include <CPPLib/Math/Random/Random.hpp>





namespace cpp
{
	RandomInt<int> random;





	StringIDGenerator::StringIDGenerator(int length, const std::string& elementCharacters)
		: m_length(length),
		  m_elementCharacters(elementCharacters)
	{
	}

	int StringIDGenerator::length() const
	{
		return m_length;
	}

	std::string StringIDGenerator::generate() const
	{
		std::string id = "";
		const auto elementListLastIndex = int(m_elementCharacters.length()) - 1;
		for (int i = 0; i < m_length; ++i)
		{
			int rnd = random.next(0, elementListLastIndex);
			id += m_elementCharacters[random.next(0, elementListLastIndex)];
		}
		return id;
	}
}
