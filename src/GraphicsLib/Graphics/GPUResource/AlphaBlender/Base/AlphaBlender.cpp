#include <GraphicsLib/Graphics/GPUResource/AlphaBlender/AlphaBlender.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	AlphaBlender::AlphaBlender(const SetCall& setCall)
		: m_setCall(setCall)
	{
	}

	void AlphaBlender::release()
	{
		if (GPUStateViewer::view().blender.isEmpty) { return; }

#ifdef CONTEXT_D3D11
		d3d11::Device::getDeviceContext()->OMSetBlendState(nullptr, nullptr, 0);
#endif

		GPUStateRecorder::main.blenderReleased();
	}

	void AlphaBlender::set()
	{
		auto selfID = getID();
		if (selfID != GPUStateViewer::view().blender.id)
		{
			m_setCall();
		}

		GPUStateRecorder::main.blenderSet(selfID);
	}
}