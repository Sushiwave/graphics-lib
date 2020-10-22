#include <GraphicsLib/Graphics/GPUState/GPUStateViewer.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>




namespace cg
{
	GPUState GPUStateViewer::view() noexcept
	{
		return GPUStateRecorder::main.getGPUState(GPUStateRecorder::m_mainRecordingThreadName.get());
	}
}
