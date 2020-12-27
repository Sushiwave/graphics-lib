#include <GraphicsLib/Graphics/GPUResource/DepthStencilTesterState/DepthStencilTesterState.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	DepthStencilTesterState::DepthStencilTesterState(const SetCall& setCall, ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled)
		: m_depthFunction(depthFunction),
		  m_stencilFunction(stencilFunction),
		  m_isDepthTestEnabled(isDepthTestEnabled),
		  m_isStencilTestEnabled(isStencilTestEnabled),
		  m_isDepthBufferWritingOperationEnabled(isDepthBufferWritingOperationEnabled),
		  m_setCall(setCall)
	{
	}

	ComparisonFunction DepthStencilTesterState::getDepthFunction() const noexcept
	{
		return m_depthFunction;
	}

	ComparisonFunction DepthStencilTesterState::getStencilFunction() const noexcept
	{
		return m_stencilFunction;
	}

	bool DepthStencilTesterState::isDepthTestEnabled() const noexcept
	{
		return m_isDepthTestEnabled;
	}

	bool DepthStencilTesterState::isStencilTestEnabled() const noexcept
	{
		return m_isStencilTestEnabled;
	}

	bool DepthStencilTesterState::isDepthBufferWritingOperationEnabled() const noexcept
	{
		return m_isDepthBufferWritingOperationEnabled;
	}

	void DepthStencilTesterState::release()
	{
		if (GPUStateViewer::view().depthStencilTester.isEmpty) { return; }

#ifdef CONTEXT_D3D11
		d3d11::Device::getDeviceContext()->OMSetDepthStencilState(nullptr, 0);
#endif

		GPUStateRecorder::main.depthStencilTesterReleased();
	}

	void DepthStencilTesterState::set() const
	{
		auto selfID = getID();
		if (selfID != GPUStateViewer::view().depthStencilTester.id)
		{
			m_setCall();
		}

		GPUStateRecorder::main.depthStencilTesterSet(selfID);
	}
}
