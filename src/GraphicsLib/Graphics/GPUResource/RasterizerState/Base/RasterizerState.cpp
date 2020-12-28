#include <GraphicsLib/Graphics/GPUResource/RasterizerState/RasterizerState.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	RasterizerState::RasterizerState(const SetCall& setCall)
		: m_setCall(setCall)
	{
	}

	void RasterizerState::release()
	{
		if (GPUStateViewer::view().rasterizerState.isEmpty) { return; }

#ifdef CONTEXT_D3D11
		d3d11::Device::getDeviceContext()->RSSetState(nullptr);
#endif

		GPUStateRecorder::main.rasterizerStateReleased();
	}
	void RasterizerState::set()
	{
		auto selfID = getID();
		if (selfID != GPUStateViewer::view().rasterizerState.id)
		{
			m_setCall();
		}

		GPUStateRecorder::main.rasterizerStateSet(selfID);
	}
}
