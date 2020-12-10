#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/IShaderResourceMemoryAccessor.hpp>
#include <GraphicsLib/ID/ID.hpp>
#include <GraphicsLib/Context.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Components/ShaderResourceType.hpp>
#include <GraphicsLib/Graphics/GPUResource/Base/GPUResource.hpp>

#include <unordered_map>
#include <functional>





namespace cg
{
	class ShaderResourceMemoryAccessor
		: public GPUResource,
		  public IShaderResourceMemoryAccessor
	{
	public:
		using SetCall = std::function<void(int)>;
		using ReleaseCall = SetCall;
		using SetCallDB = std::unordered_map<ShaderStage, SetCall>;
		using ReleaseCallDB = std::unordered_map<ShaderResourceType, std::unordered_map<GPUAccessType, SetCallDB>>;
	private:
		using ShaderResourceBufferLocationListRef = std::shared_ptr<ShaderResourceBufferLocationList>;
		using ShaderResourceBufferLocationListRefDict = std::unordered_map<ShaderStage, std::unordered_map<ShaderResourceType, std::unordered_map<GPUAccessType, std::unordered_map<int, ShaderResourceBufferLocationListRef>>>>;
	private:
		ShaderResourceType m_type;
		GPUAccessType m_gpuAccessType;

		SetCallDB m_setCallDB;
		static ReleaseCallDB m_releaseCallDB;

		ShaderResourceBufferLocationListRef m_managedShaderResourceBufferLocationListRef;
		static ShaderResourceBufferLocationListRefDict m_dictForUpdatingShaderResourceBufferLocationList;
	public:
		ShaderResourceMemoryAccessor() = default;
		ShaderResourceMemoryAccessor(const ID& id, ShaderResourceType type, GPUAccessType gpuAccessType, const SetCallDB& setCallDB);
		virtual ~ShaderResourceMemoryAccessor() = default;

		void set(ShaderStage stage, int unit, const ID& resourceID) override;
		static void release(ShaderStage stage, ShaderResourceType resourceType, int unit, GPUAccessType usage);

		[[nodiscard]] ShaderResourceBufferLocationList getManagedShaderResourceBufferLocationList() const;
	};
}
