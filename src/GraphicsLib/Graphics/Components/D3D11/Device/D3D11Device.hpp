#pragma once
#include <Graphics/System/D3D11/Components/D3D11GraphicsSystemComponents.hpp>
#include <Window/System/WINAPI/Components/WINAPIWindow.hpp>





namespace cg
{
	namespace d3d11
	{
		class Device
		{
		private:
			struct CrashInfo
			{
				bool hasCrashed;
				bool canRecover;

				CrashInfo(bool hasCrashed, bool canRecover);
				virtual ~CrashInfo();
			};
		private:
			Device() = default;
			virtual ~Device() = default;

			static cpp::com_ptr<ID3D11Device> m_device;
			static cpp::com_ptr<ID3D11DeviceContext> m_deviceContext;

			static bool m_isNullFlag;
		public:
			[[nodiscard]] static bool isNull() noexcept;
			static void initialize(std::shared_ptr<d3d11::GraphicsSystemComponents>& components);
			[[nodiscard]] static cpp::com_ptr<ID3D11Device> getDevice() noexcept;
			[[nodiscard]] static cpp::com_ptr<ID3D11DeviceContext> getDeviceContext() noexcept;
			[[nodiscard]] static bool recover(bool* outShouldResetAllGPUResources, std::shared_ptr<IScreenUpdater>* outNewScreenUpdater);
		};
	}
}
