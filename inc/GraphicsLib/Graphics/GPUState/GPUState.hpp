#pragma once
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/ShaderResourceType.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessType.hpp>

#include <unordered_map>





namespace cg
{
	class GPUState
	{
	public:
		struct State
		{
			bool isEmpty = true;
			ID id = ID("");
		};
		struct StateOfBufferBoundedBySeveralResources
			: GPUState::State
		{
			using BoundedResourceIDList = std::vector<ID>;

			BoundedResourceIDList boundedResourceIDList;
		};
		struct DepthStencilBufferState
			: public GPUState::StateOfBufferBoundedBySeveralResources
		{				
		};
		struct RenderTargetBufferState
			: public GPUState::StateOfBufferBoundedBySeveralResources
		{
			int count = 0;
		};
		class ShaderBufferState
			: public GPUState::State
		{
		public:
			class ShaderResourceBufferState
			{
			public:
				class UnitState
					: public GPUState::State
				{
				};
			public:
				using UnitStateDict = std::unordered_map<int, UnitState>;
			private:
				UnitStateDict m_unitStateDict;
				std::vector<int> m_validatedUnitIndexList;
			public:
				virtual ~ShaderResourceBufferState() = default;

				void validate(int unitIndex);
				void invalidate(int unitIndex);
				[[nodiscard]] bool isValidated(int index) const noexcept;

				[[nodiscard]] std::vector<int> validatedUnitIndexList() const noexcept;

				[[nodiscard]] UnitState& unit(int index);
			};
		private:
			std::unordered_map<ShaderResourceType, std::unordered_map<GPUAccessType, ShaderResourceBufferState>> m_resource;
		public:
			ShaderBufferState() noexcept;
			virtual ~ShaderBufferState() = default;

			[[nodiscard]] ShaderResourceBufferState& resource(ShaderResourceType type, GPUAccessType usage);
		};
	private:
		std::unordered_map<ShaderStage, ShaderBufferState> m_shader;
	public:
		State rasterizerState;
		State depthStencilTesterState;
		State blender;

		RenderTargetBufferState renderTarget;
		DepthStencilBufferState depthStencilBuffer;
	public:
		GPUState() noexcept;
		virtual ~GPUState() = default;

		[[nodiscard]] ShaderBufferState& shader(ShaderStage stage);
	};
}
