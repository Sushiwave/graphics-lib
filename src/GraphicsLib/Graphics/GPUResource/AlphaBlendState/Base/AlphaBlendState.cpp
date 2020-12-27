#include <GraphicsLib/Graphics/GPUResource/AlphaBlendState/AlphaBlendState.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	AlphaBlendState::AlphaBlendState(const SetCall& setCall)
		: m_setCall(setCall)
	{
	}

	void AlphaBlendState::release()
	{
		if (GPUStateViewer::view().blender.isEmpty) { return; }

#ifdef CONTEXT_D3D11
		d3d11::Device::getDeviceContext()->OMSetBlendState(nullptr, nullptr, 0);
#endif

		GPUStateRecorder::main.blenderReleased();
	}

	void AlphaBlendState::set()
	{
		auto selfID = getID();
		if (selfID != GPUStateViewer::view().blender.id)
		{
			m_setCall();
		}

		GPUStateRecorder::main.blenderSet(selfID);
	}
}