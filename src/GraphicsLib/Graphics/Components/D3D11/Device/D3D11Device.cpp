#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <GraphicsLib/System/System.hpp>
#include <Graphics/System/D3D11/Components/D3D11ScreenUpdater.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>




namespace cg
{
	namespace d3d11
	{
		cpp::com_ptr<ID3D11Device> Device::m_device;
		cpp::com_ptr<ID3D11DeviceContext> Device::m_deviceContext;
		bool Device::m_isNullFlag = true;

		bool Device::isNull() noexcept
		{
			return m_isNullFlag;
		}

		void Device::initialize(std::shared_ptr<d3d11::GraphicsSystemComponents>& components)
		{
			m_device = components->getDevice();
			m_deviceContext = components->getDeviceContext();
			m_isNullFlag = false;
		}

		cpp::com_ptr<ID3D11Device> Device::getDevice() noexcept
		{
			return m_device;
		}

		cpp::com_ptr<ID3D11DeviceContext> Device::getDeviceContext() noexcept
		{
			return m_deviceContext;
		}
		bool Device::recover(bool* outShouldResetAllGPUResources, std::shared_ptr<IScreenUpdater>* out)
		{
			*out = nullptr;

			HRESULT hr = m_device->GetDeviceRemovedReason();

			switch (hr)
			{
			case S_OK:
				LogEX("The cause of the device lost: The graphics device was enabled, disabled, or reset without invalidating the current graphics device. For example, this error code can be returned if an app is using Windows Advanced Rasterization Platform (WARP) and a hardware adapter becomes available.");
				break;
			case DXGI_ERROR_DEVICE_REMOVED:
				LogEX("The cause of the device lost: The graphics device has been physically removed, turned off, or a driver upgrade has occurred.");
				break;
			case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
				LogEX("The cause of the device lost: The graphics driver encountered an error and reset the device.");
				break;
			case DXGI_ERROR_DEVICE_HUNG:
				LogEX("The cause of the device lost: The graphics driver stopped responding because of an invalid combination of graphics commands sent by the app. If you get this error repeatedly, it is a likely indication that your app caused the device to hang and needs to be debugged.");
				break;
			case DXGI_ERROR_INVALID_CALL:
				LogEX("The cause of the device lost: The application provided invalid parameter data. If you get this error even once, it means that your code caused the device removed conditionand must be debugged.");
				break;
			}

			LogEX("Attempt to recover the lost device.");

			switch (hr)
			{
			case S_OK:
				*outShouldResetAllGPUResources = false;
				return true;
			case DXGI_ERROR_DEVICE_RESET:
			case DXGI_ERROR_DEVICE_REMOVED:
			case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
				*outShouldResetAllGPUResources = true;
				break;
			case DXGI_ERROR_DEVICE_HUNG:
			case DXGI_ERROR_INVALID_CALL:
			default:
				*outShouldResetAllGPUResources = false;
				return false;
			}

			*out = d3d11::GraphicsSystem().initialize(0, System::getWindowInfo().fullScreen());

			return true;
		}
		Device::CrashInfo::CrashInfo(bool hasCrashed, bool canRecover)
			: hasCrashed(hasCrashed),
			  canRecover(canRecover)
		{
		}
		Device::CrashInfo::~CrashInfo()
		{
		}
	}
}
