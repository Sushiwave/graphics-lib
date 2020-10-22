#include <GraphicsLib/Graphics/GPUState/MainGPUStateRecorder.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>





namespace cg
{
	void MainGPUStateRecorder::createNewRecordingThread(const std::string& name) noexcept
	{
		GPUStateRecorder::main.createNewRecordingThread(name);
	}
	void MainGPUStateRecorder::removeRecordingThread(const std::string& name) noexcept
	{
		GPUStateRecorder::main.removeRecordingThread(name);
	}
	GPUState MainGPUStateRecorder::getGPUState(const std::string& name)
	{
		return GPUStateRecorder::main.getGPUState(name);
	}
}
