#pragma once
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Components/ShaderStage.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/ShaderResourceType.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/GPUAccessFlags.hpp>

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
		struct RenderTargetBufferState
			: public GPUState::State
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
				using UnitState = std::unordered_map<int, State>;
			private:
				UnitState m_unit;
				std::vector<int> m_validatedUnitIndexList;
			public:
				virtual ~ShaderResourceBufferState() = default;

				void validate(int unitIndex);
				void invalidate(int unitIndex);
				[[nodiscard]] bool isValidated(int index) const noexcept;

				[[nodiscard]] std::vector<int> validatedUnitIndexList() const noexcept;

				[[nodiscard]] State& unit(int index);
			};
		private:
			std::unordered_map<ShaderResourceType, std::unordered_map<GPUAccessFlags, ShaderResourceBufferState>> m_resource;
		public:
			ShaderBufferState() noexcept;
			virtual ~ShaderBufferState() = default;

			[[nodiscard]] ShaderResourceBufferState& resource(ShaderResourceType type, GPUAccessFlags usage);
		};
	private:
		std::unordered_map<ShaderStage, ShaderBufferState> m_shader;
	public:
		State rasterizer;
		State depthStencilTester;
		State blender;

		RenderTargetBufferState renderTarget;
		State depthStencilBuffer;
	public:
		GPUState() noexcept;
		virtual ~GPUState() = default;

		[[nodiscard]] ShaderBufferState& shader(ShaderStage stage);
	};
}
