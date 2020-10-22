#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Base/ITexture2D.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <unordered_map>
#include <memory>





namespace cg
{
	struct GBufferContent
	{
		std::string name;
		std::shared_ptr<ITexture2D> buffer;
	};

	class GBuffer
		: GPUResource
	{
	public:
		using BufferDict = std::unordered_map<std::string, std::shared_ptr<ITexture2D>>;
	private:
		BufferDict m_bufferDict;
	private:
		BufferDict m_createBufferDict(const std::vector<GBufferContent>& contents);
	public:
		GBuffer() = default;
		GBuffer(const std::vector<GBufferContent>& contents);
		virtual ~GBuffer() = default;

		[[nodiscard]] std::shared_ptr<ITexture2D> get(const std::string& name) const;

		[[nodiscard]] bool exists(const std::string& name) const noexcept;
	};
}