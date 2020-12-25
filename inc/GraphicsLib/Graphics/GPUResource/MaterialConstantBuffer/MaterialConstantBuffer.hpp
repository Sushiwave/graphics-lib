#pragma once
#include <GraphicsLib/API/API.hpp>
#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Material/Material.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/ShaderResource.hpp>




namespace cg
{
	class MaterialConstantBuffer
		: public GPUResource
	{
	public:
		class ElementBuffer
			: public ShaderResource
		{
		private:
			std::shared_ptr<IDynamicConstantBuffer> m_constantBuffer;
		public:
			ElementBuffer(unsigned int byteStride);
			ElementBuffer() = default;
			virtual ~ElementBuffer() = default;

			void update(ShaderStage stage, const Material& material);
			void set(ShaderStage stage, int unit);

			[[nodiscard]] BoundedBufferLocationList getBoundedBufferLocationList() const override;
		};
	public:
		using BufferDict = std::unordered_map<ShaderStage, std::shared_ptr<ElementBuffer>>;
	private:
		BufferDict m_bufferForEachShaderStage;
		std::unordered_map<ID::Type, std::shared_ptr<ElementBuffer>> m_bufferDict;
	public:
		MaterialConstantBuffer() = default;
		MaterialConstantBuffer(const BufferDict& bufferForEachShaderStage);
		virtual ~MaterialConstantBuffer() = default;



		void update(ShaderStage stage, const Material& material);
		void set(ShaderStage stage, int unit);
	};

	 
}
