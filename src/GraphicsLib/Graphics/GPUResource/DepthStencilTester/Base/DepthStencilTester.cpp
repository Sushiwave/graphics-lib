#include <GraphicsLib/Graphics/GPUResource/DepthStencilTester/DepthStencilTester.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	DepthStencilTester::DepthStencilTester(const SetCall& setCall, ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled)
		: m_depthFunction(depthFunction),
		  m_stencilFunction(stencilFunction),
		  m_isDepthTestEnabled(isDepthTestEnabled),
		  m_isStencilTestEnabled(isStencilTestEnabled),
		  m_isDepthBufferWritingOperationEnabled(isDepthBufferWritingOperationEnabled),
		  m_setCall(setCall)
	{
	}

	ComparisonFunction DepthStencilTester::getDepthFunction() const noexcept
	{
		return m_depthFunction;
	}

	ComparisonFunction DepthStencilTester::getStencilFunction() const noexcept
	{
		return m_stencilFunction;
	}

	bool DepthStencilTester::isDepthTestEnabled() const noexcept
	{
		return m_isDepthTestEnabled;
	}

	bool DepthStencilTester::isStencilTestEnabled() const noexcept
	{
		return m_isStencilTestEnabled;
	}

	bool DepthStencilTester::isDepthBufferWritingOperationEnabled() const noexcept
	{
		return m_isDepthBufferWritingOperationEnabled;
	}

	void DepthStencilTester::release()
	{
		if (GPUStateViewer::view().depthStencilTester.isEmpty) { return; }

#ifdef CONTEXT_D3D11
		d3d11::Device::getDeviceContext()->OMSetDepthStencilState(nullptr, 0);
#endif

		GPUStateRecorder::main.depthStencilTesterReleased();
	}

	void DepthStencilTester::set() const
	{
		auto selfID = getID();
		if (selfID != GPUStateViewer::view().depthStencilTester.id)
		{
			m_setCall();
		}

		GPUStateRecorder::main.depthStencilTesterSet(selfID);
	}
}
