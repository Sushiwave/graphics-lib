#pragma once
#include <GraphicsLib/API/API.hpp>
#include <GraphicsLib/Graphics/Scene/Scene.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Base/ShaderResource.hpp>





namespace cg
{
	class LightConstantBuffer
		: public GPUResource
	{
	public:
		class ElementBuffer
			: public ShaderResource
		{
		public:
			template <typename Data_>
			using DataUpdater = std::function<void(Data_&, const Scene& scene)>;
		private:
			using UBUpdater = std::function<void(const Scene& scene)>;
		private:
			UBUpdater m_update = [](const Scene&) {};
		private:
			std::shared_ptr<IDynamicConstantBuffer> m_constantBuffer;
		public:
			template <typename Data_>
			static ElementBuffer constructor(const DataUpdater<Data_>& dataUpdater)
			{
				return ElementBuffer(dataUpdater);
			}
		private:
			template <typename Data_>
			ElementBuffer(const DataUpdater<Data_>& dataUpdater)
			{
				auto constant_ = Constant(std::make_shared<Data_>());
				m_constantBuffer = API::shared.graphics()->createDynamicConstantBuffer(sizeof(Data_));
				auto constantBuffer = m_constantBuffer;

				m_update = [=](const Scene& scene)
				{
					dataUpdater(*std::reinterpret_pointer_cast<Data_>(constant_.getP()), scene);
					constantBuffer->update(constant_);
				};
			}
		public:
			ElementBuffer() = default;
			virtual ~ElementBuffer() = default;

			void update(const Scene& scene);
			void set(ShaderStage stage, int unit);

			[[nodiscard]] BoundedBufferLocationList getBoundedBufferLocationList() const override;
		};
	public:
		using BufferDict = std::unordered_map<ShaderStage, std::shared_ptr<ElementBuffer>>;
	private:
		BufferDict m_bufferForEachShaderStage;
		std::unordered_map<ID::Type, std::shared_ptr<ElementBuffer>> m_bufferDict;
	public:
		LightConstantBuffer() = default;
		LightConstantBuffer(const BufferDict& bufferForEachShaderStage);
		virtual ~LightConstantBuffer() = default;



		void update(const Scene& scene);
		void set(ShaderStage stage, int unit);
	};
}