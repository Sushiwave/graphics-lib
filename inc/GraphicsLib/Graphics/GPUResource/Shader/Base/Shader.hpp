#pragma once
#include <GraphicsLib/Graphics/GPUResource/Shader/Base/IShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <functional>





namespace cg
{
	class Shader
		: public GPUResource,
		  public std::enable_shared_from_this<Shader>,
		  public virtual IShader
	{
	public:
		using SetCall = std::function<void()>;
	private:
		using ReleaseCall = std::function<void()>;
		using ReleaseCallDB = std::unordered_map<ShaderStage, ReleaseCall>;
	private:
		ShaderStage m_stage;

		mutable bool m_isResourceLocationDictInitialized = false;
		mutable ShaderResourceLocationDict m_resourceLocationDict;

		SetCall m_setCall;
		static ReleaseCallDB m_releaseCallDB;
	public:
		Shader(const SetCall& setCall, ShaderStage stage);
		virtual ~Shader() = default;

		[[nodiscard]] ShaderStage getShaderStage() const noexcept override;
		[[nodiscard]] ShaderResourceLocationDict getResourceLocationDict() const override;

		void set() const override;

		static void release(ShaderStage stage);
	};
}
