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

		GBufferContent(const std::string& name, std::shared_ptr<ITexture2D> buffer);
	};

	class GBuffer
		: public GPUResource
	{
	public:
		using BufferDict = std::unordered_map<std::string, std::shared_ptr<ITexture2D>>;
		using GBufferContents = std::vector<GBufferContent>;
	private:
		BufferDict m_bufferDict;
	private:
		static BufferDict createBufferDict(const std::vector<GBufferContent>& contents);
	public:
		GBuffer() = default;
		GBuffer(const std::vector<GBufferContent>& contents);
		virtual ~GBuffer() = default;

		[[nodiscard]] std::shared_ptr<ITexture2D> get(const std::string& name) const;

		[[nodiscard]] bool exists(const std::string& name) const noexcept;

		[[nodiscard]] GBufferContents getAllContents() const noexcept;
	};
}