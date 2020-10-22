#pragma once
#include <GraphicsLib/Graphics/GPUState/GPUState.hpp>

#include <string>





namespace cg
{
	class MainGPUStateRecorder
	{
	public:
		MainGPUStateRecorder() = default;
		virtual ~MainGPUStateRecorder() = default;



		static void createNewRecordingThread(const std::string& name) noexcept;
		static void removeRecordingThread(const std::string& name) noexcept;

		[[nodiscard]] static GPUState getGPUState(const std::string& name);
	};
}