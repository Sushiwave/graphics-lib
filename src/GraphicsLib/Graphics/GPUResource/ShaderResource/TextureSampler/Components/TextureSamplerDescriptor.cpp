#include <GraphicsLib/Graphics/GPUResource/ShaderResource/TextureSampler/Components/TextureSamplerDescriptor.hpp>





namespace cg
{
	TextureSamplerDescriptor::TextureSamplerDescriptor() noexcept
	{
		filter = TextureFilter::point;
		addressU = TextureAddressMode::clamp;
		addressV = TextureAddressMode::clamp;
		addressW = TextureAddressMode::clamp;
		maxAnisotropy = 0;
		borderColor = cpp::Vector4D<float>(0.0f, 0.0f, 0.0f, 0.0f);
	}
}