#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/TextureSampler/Components/TextureSamplerDescriptor.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/TextureSampler/ITextureSampler.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/ShaderResource.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>

namespace cg
{
	namespace d3d11 
	{ 
		class TextureSamplerState; 
	}
}





namespace cg
{
	namespace d3d11
	{
		class TextureSampler
			: public ShaderResource,
			public ITextureSampler
		{
		private:
			std::shared_ptr<TextureSamplerState> m_state;
		public:
			TextureSampler() = default;
			TextureSampler(const TextureSamplerDescriptor& desc);
			virtual ~TextureSampler() = default;

			void set(ShaderStage stage, int unit) override;

			[[nodiscard]] BoundedBufferLocationList getBoundedBufferLocationList() const override;
		};
	}
}
