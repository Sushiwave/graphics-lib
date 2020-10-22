#pragma once
#include <ThirdParty/CPPLib/Log/Log.hpp>

#include <array>
#include <string>





namespace cg
{
	class WavefrontOBJLoadingHelper
	{
	public:
		static std::string loadName(const std::string& line, const std::string& tag);

		template <typename T, int dimensionCount_>
		static std::array<T, dimensionCount_> loadVector(const std::string& line, const std::string& tag, const std::string& divider, bool isRealValue, bool isExpNotation = false)
		{
			std::array<T, dimensionCount_> vec = {};

			std::string cs = isRealValue ? (isExpNotation ? "%e" : "%f") : "%d";
			std::string format = tag + " ";
			for (int i = 0; i < dimensionCount_; ++i)
			{
				format += cs + ((i != dimensionCount_ - 1) ? divider : "");
			}
			const auto pFormat = format.c_str();

			const auto pLine = line.c_str();

			int loadedElementCount = 0;
			if (dimensionCount_ == 2)
			{
				loadedElementCount = sscanf_s(pLine, pFormat, &vec[0], &vec[1]);
			}
			else if (dimensionCount_ == 3)
			{
				loadedElementCount = sscanf_s(pLine, pFormat, &vec[0], &vec[1], &vec[2]);
			}
			else if (dimensionCount_ == 4)
			{
				loadedElementCount = sscanf_s(pLine, pFormat, &vec[0], &vec[1], &vec[2], &vec[3]);
			}
			else
			{
				LogEX("Failed to load vector data from: \"%s\"", line.c_str());
			}


			if (loadedElementCount != dimensionCount_)
			{
				LogEX("Failed to load vector data correctly from: \"%s\"", line.c_str());
			}

			return vec;
		}
	};
}
