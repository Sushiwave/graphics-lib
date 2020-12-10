#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/ShaderResourceMemoryAccessor.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/RenderTarget.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>





namespace cg
{
#define D3D11ReleaseConstantBuffers(SHADER) [&](UINT unit){ d3d11::Device::getDeviceContext()->SHADER##SetConstantBuffers(unit, 1, ppEmptyCB); }
#define D3D11ReleaseShaderResources(SHADER) [&](UINT unit){ d3d11::Device::getDeviceContext()->SHADER##SetShaderResources(unit, 1, ppEmptySRV); }
#define D3D11ReleaseSamplers(SHADER) [&](UINT unit){ d3d11::Device::getDeviceContext()->SHADER##SetSamplers(unit, 1, ppEmptySampler); }
#define D3D11ReleaseUnorderedAccessViews(SHADER) [&](UINT unit){ d3d11::Device::getDeviceContext()->SHADER##SetUnorderedAccessViews(unit, 1, ppEmptyUAV, nullptr); }

	
	constexpr ID3D11Buffer* ppEmptyCB[1] = { nullptr };
	constexpr ID3D11ShaderResourceView* ppEmptySRV[1] = { nullptr };
	constexpr ID3D11SamplerState* ppEmptySampler[1] = { nullptr };
	constexpr ID3D11UnorderedAccessView* ppEmptyUAV[1] = { nullptr };





	ShaderResourceMemoryAccessor::ShaderResourceBufferLocationListRefDict ShaderResourceMemoryAccessor::m_dictForUpdatingShaderResourceBufferLocationList =
		[]()
	{
		ShaderResourceMemoryAccessor::ShaderResourceBufferLocationListRefDict dict;

		for (auto stage : ShaderStageAll)
		{
			dict.emplace(stage, std::unordered_map<ShaderResourceType, std::unordered_map<GPUAccessType, std::unordered_map<int, ShaderResourceBufferLocationListRef>>>());
			for (auto resourceType : ShaderResourceTypeAll)
			{
				dict[stage].emplace(resourceType, std::unordered_map<GPUAccessType, std::unordered_map<int, ShaderResourceBufferLocationListRef>>());
				const auto empty = std::unordered_map<int, ShaderResourceBufferLocationListRef>();
				dict[stage][resourceType].emplace(GPUAccessType::none, empty);
				dict[stage][resourceType].emplace(GPUAccessType::R, empty);
				dict[stage][resourceType].emplace(GPUAccessType::RW, empty);
			}
		}

		return dict;
	}();





#ifdef CONTEXT_D3D11
	const ShaderResourceMemoryAccessor::SetCallDB shaderResourceViewReleaseCallDB
	{
		{ ShaderStage::vs, D3D11ReleaseShaderResources(VS) },
		{ ShaderStage::hs, D3D11ReleaseShaderResources(HS) },
		{ ShaderStage::ds, D3D11ReleaseShaderResources(DS) },
		{ ShaderStage::gs, D3D11ReleaseShaderResources(GS) },
		{ ShaderStage::ps, D3D11ReleaseShaderResources(PS) },
		{ ShaderStage::cs, D3D11ReleaseShaderResources(CS) }
	};
	const ShaderResourceMemoryAccessor::SetCallDB unorderedAccessViewReleaseCallDB
	{
		{ ShaderStage::cs, D3D11ReleaseUnorderedAccessViews(CS) }
	};
#endif





	ShaderResourceMemoryAccessor::ReleaseCallDB ShaderResourceMemoryAccessor::m_releaseCallDB
	{
	#ifdef CONTEXT_D3D11
		{ ShaderResourceType::ConstantBuffer,
			{{ GPUAccessType::R,
				{{ ShaderStage::vs, D3D11ReleaseConstantBuffers(VS) },
				 { ShaderStage::hs, D3D11ReleaseConstantBuffers(HS) },
				 { ShaderStage::ds, D3D11ReleaseConstantBuffers(DS) },
				 { ShaderStage::gs, D3D11ReleaseConstantBuffers(GS) },
				 { ShaderStage::ps, D3D11ReleaseConstantBuffers(PS) },
				 { ShaderStage::cs, D3D11ReleaseConstantBuffers(CS) }}
			}}
		},
		{ ShaderResourceType::Texture,
			{{ GPUAccessType::R,  shaderResourceViewReleaseCallDB  },
			 { GPUAccessType::RW, unorderedAccessViewReleaseCallDB }}
		},
		{ ShaderResourceType::TextureSampler, {
			{{ GPUAccessType::R,
				{{ ShaderStage::vs, D3D11ReleaseSamplers(VS) },
				 { ShaderStage::hs, D3D11ReleaseSamplers(HS) },
				 { ShaderStage::ds, D3D11ReleaseSamplers(DS) },
				 { ShaderStage::gs, D3D11ReleaseSamplers(GS) },
				 { ShaderStage::ps, D3D11ReleaseSamplers(PS) },
				 { ShaderStage::cs, D3D11ReleaseSamplers(CS) }}
			}}
		}},
		{ ShaderResourceType::StructuredBuffer,
			{{ GPUAccessType::R,  shaderResourceViewReleaseCallDB  },
			 { GPUAccessType::RW, unorderedAccessViewReleaseCallDB }}
		},
	#endif
	};





	ShaderResourceMemoryAccessor::ShaderResourceMemoryAccessor(const ID& id, ShaderResourceType type, GPUAccessType gpuAccessType, const SetCallDB& setCallDB)
		: GPUResource(id),
	  	  m_type(type),
		  m_gpuAccessType(gpuAccessType),
		  m_setCallDB(setCallDB),
		  m_managedShaderResourceBufferLocationListRef(std::make_shared<ShaderResourceBufferLocationList>())
	{
	}



	void ShaderResourceMemoryAccessor::set(ShaderStage stage, int unitIndex, const ID& resourceID)
	{
		if (resourceID == GPUStateViewer::view().shader(stage).resource(m_type, m_gpuAccessType).unit(unitIndex).id) { return; }



		GPUStateRecorder::main.shaderResourceSet(stage, m_type, m_gpuAccessType, unitIndex, resourceID);



		const auto avoidSimultaneousReadingAndWritingToShaderResources = [&](ShaderResourceType accessorType, GPUAccessType usage)
		{
			for (auto stage : ShaderStageAll)
			{
				auto bufferState = GPUStateViewer::view().shader(stage).resource(accessorType, usage);

				const auto& validatedUnitIndexList = bufferState.validatedUnitIndexList();
				for (auto index : validatedUnitIndexList)
				{
					const auto& unitState = bufferState.unit(index);
					if (unitState.id == resourceID)
					{
						ShaderResourceMemoryAccessor::release(stage, accessorType, index, usage);
					}
				}
			}
		};
		if (m_gpuAccessType == GPUAccessType::R)
		{
			avoidSimultaneousReadingAndWritingToShaderResources(m_type, GPUAccessType::RW);
		}
		else if (m_gpuAccessType == GPUAccessType::RW)
		{
			avoidSimultaneousReadingAndWritingToShaderResources(m_type, GPUAccessType::R);
		}
		
		const auto avoidSimultaneousReadingAndWritingToRenderTargetRelatedResources = [&](GPUState::StateOfBufferBoundedBySeveralResources state, std::string resourceName)
		{
			if (state.isEmpty == false)
			{
				for (auto id : state.boundedResourceIDList)
				{
					if (id == resourceID)
					{
						RenderTarget::release();
						LogEX("Released a render target buffer from the pipeline to avoid simultaneous reading and writing to [ "+resourceName+": "+id.get()+" ].");
						return true;
					}
				}
			}
			return false;
		};
		if (avoidSimultaneousReadingAndWritingToRenderTargetRelatedResources(GPUStateViewer::view().depthStencilBuffer, "Depth Stencil Buffer") == false)
		{
			avoidSimultaneousReadingAndWritingToRenderTargetRelatedResources(GPUStateViewer::view().renderTarget, "Render Target");
		}



		m_setCallDB.at(stage)(unitIndex);



		auto location = BoundedBufferLocation(stage, unitIndex, m_gpuAccessType);
		m_managedShaderResourceBufferLocationListRef->emplace_back(location);
		m_dictForUpdatingShaderResourceBufferLocationList.at(stage).at(m_type).at(m_gpuAccessType).emplace(unitIndex, m_managedShaderResourceBufferLocationListRef);
	}
	void ShaderResourceMemoryAccessor::release(ShaderStage stage, ShaderResourceType resourceType, int unitIndex, GPUAccessType usage)
	{
		if (GPUStateViewer::view().shader(stage).resource(resourceType, usage).isValidated(unitIndex) == false) { return; }



		m_releaseCallDB.at(resourceType).at(usage).at(stage)(unitIndex);



		GPUStateRecorder::main.shaderResourceReleased(stage, resourceType, usage, unitIndex);



		if (m_dictForUpdatingShaderResourceBufferLocationList.at(stage).at(resourceType).at(usage).count(unitIndex) == 0) { return; }

		auto& shaderResourceBufferLocationList = m_dictForUpdatingShaderResourceBufferLocationList.at(stage).at(resourceType).at(usage).at(unitIndex);
		auto begin = shaderResourceBufferLocationList->begin();
		auto end = shaderResourceBufferLocationList->end();
		for (auto ite = begin; ite != end; ++ite)
		{
			if (ite->stage == stage && ite->unit == unitIndex)
			{
				shaderResourceBufferLocationList->erase(ite);
				m_dictForUpdatingShaderResourceBufferLocationList.at(stage).at(resourceType).at(usage).erase(unitIndex);
				break;
			}
		}
	}

	ShaderResourceBufferLocationList ShaderResourceMemoryAccessor::getManagedShaderResourceBufferLocationList() const
	{
		return *m_managedShaderResourceBufferLocationListRef;
	}
}