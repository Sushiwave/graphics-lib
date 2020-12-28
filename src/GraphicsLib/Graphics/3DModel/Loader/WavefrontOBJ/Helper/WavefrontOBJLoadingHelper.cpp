#include <GraphicsLib/Graphics/3DModel/Loader/WavefrontOBJ/Helper/WavefrontOBJLoadingHelper.hpp>





namespace cg
{
	std::string WavefrontOBJLoadingHelper::loadName(const std::string& line, const std::string& tag)
	{
		auto tagPos = line.find(tag);
		if (tagPos == std::string::npos)
		{
			LogEX("Failed to load name data from: \"%s\"", line.c_str());
			return "";
		}
		auto tagEnd = tagPos+tag.size()-1;
		auto nameFirstIndex = tagEnd;
		const char space = ' ';
		do
		{
			if (line.size() <= nameFirstIndex)
			{
				LogEX("Failed to load name data from: \"%s\"", line.c_str());
				return "";
			}
			++nameFirstIndex;
		} while (line[nameFirstIndex] == space);

		return line.substr(nameFirstIndex);
	}
}
