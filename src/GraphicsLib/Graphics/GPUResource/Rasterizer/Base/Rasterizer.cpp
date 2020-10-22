#include <GraphicsLib/Graphics/GPUResource/Rasterizer/Rasterizer.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	Rasterizer::Rasterizer(const SetCall& setCall)
		: m_setCall(setCall)
	{
	}

	void Rasterizer::release()
	{
		if (GPUStateViewer::view().rasterizer.isEmpty) { return; }

#ifdef CONTEXT_D3D11
		d3d11::Device::getDeviceContext()->RSSetState(nullptr);
#endif

		GPUStateRecorder::main.rasterizerReleased();
	}
	void Rasterizer::set()
	{
		auto selfID = getID();
		if (selfID != GPUStateViewer::view().rasterizer.id)
		{
			m_setCall();
		}

		GPUStateRecorder::main.rasterizerSet(selfID);
	}
}
