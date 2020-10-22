#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/API/API.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>
#include <Graphics/ShaderCodeParser/D3D11/D3D11ShaderCodeParser.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/Base/Shader.hpp>





namespace cg
{
#define D3D11ReleaseShader(SHADER) [&](){ d3d11::Device::getDeviceContext()->SHADER##SetShader(nullptr, nullptr, 0); }

	Shader::ReleaseCallDB Shader::m_releaseCallDB
	{
		{ ShaderStage::vs, D3D11ReleaseShader(VS) },
		{ ShaderStage::hs, D3D11ReleaseShader(HS) },
		{ ShaderStage::ds, D3D11ReleaseShader(DS) },
		{ ShaderStage::gs, D3D11ReleaseShader(GS) },
		{ ShaderStage::ps, D3D11ReleaseShader(PS) },
		{ ShaderStage::cs, D3D11ReleaseShader(CS) }
	};





	Shader::Shader(const SetCall& setCall, ShaderStage stage)
		: m_stage(stage),
		  m_setCall(setCall)
	{
	}

	ShaderStage Shader::getShaderStage() const noexcept
	{
		return m_stage;
	}

	ShaderResourceLocationDict Shader::getResourceLocationDict() const
	{
		if (m_isResourceLocationDictInitialized == false)
		{
			m_resourceLocationDict
#ifdef CONTEXT_D3D11
				= std::make_shared<d3d11::ShaderCodeParser>(std::const_pointer_cast<cg::Shader>(shared_from_this()))
#endif
				->parseShaderResourceLocation();

			m_isResourceLocationDictInitialized = true;
		}

		return m_resourceLocationDict;
	}

	void Shader::set() const
	{
		auto id = getID();
		if (id != GPUStateViewer::view().shader(m_stage).id)
		{
			m_setCall();
		}

		GPUStateRecorder::main.shaderSet(m_stage, id);
	}

	void Shader::release(ShaderStage stage)
	{
		if (GPUStateViewer::view().shader(stage).isEmpty) { return; }

		m_releaseCallDB.at(stage)();

		GPUStateRecorder::main.shaderReleased(stage);
	}
}