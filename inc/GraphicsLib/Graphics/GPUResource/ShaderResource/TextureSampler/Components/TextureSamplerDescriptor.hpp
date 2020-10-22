#pragma once
#include "TextureAddressMode.hpp"
#include "TextureFilter.hpp"
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>





namespace cg
{
	struct TextureSamplerDescriptor
	{
		TextureSamplerDescriptor() noexcept;
		virtual ~TextureSamplerDescriptor() = default;

		TextureFilter filter;

		TextureAddressMode addressU;
		TextureAddressMode addressV;
		TextureAddressMode addressW;

		int maxAnisotropy;
		cpp::Vector4D<float> borderColor;
	};
}
