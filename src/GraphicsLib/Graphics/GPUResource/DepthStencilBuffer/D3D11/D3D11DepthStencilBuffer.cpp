#include <Graphics/GPUResource/DepthStencilBuffer/D3D11/D3D11DepthStencilBuffer.hpp>
#include <Graphics/Components/D3D11/Device/D3D11Device.hpp>
#include <Graphics/GPUResource/ShaderResource/Texture/Texture2D/D3D11/D3D11DefaultTexture2D.hpp>
#include <Graphics/GPUResource/Helper/D3D11/D3D11CreateFunctions.hpp>
#include <GraphicsLib/API/API.hpp>
#include <GraphicsLib/Graphics/GPUResource/Shader/ComputeShader/IComputeShader.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/ShaderResourceMemoryAccessor.hpp>
#include <GraphicsLib/Graphics/GPUState/GPUStateRecorder.hpp>
#include <ThirdParty/CPPLib/Exception/RuntimeError/COMRuntimeError.hpp>
#include <GraphicsLib\Graphics\GPUResource\DepthStencilBuffer\DepthStencilBuffer.hpp>




namespace cg
{
	namespace d3d11
	{
		//https://wickedengine.net/2016/11/13/how-to-resolve-an-msaa-depthbuffer/
		const std::string resolveDepthTextureShader = "\
		Texture2DMS<float> ms : register(t0);\
		RWTexture2D<float> resolved : register(u0);\
		\
		[numthreads(16, 16, 1)]\
		void cs_main(uint3 id: SV_DispatchThreadID)\
		{\
			uint2 dimension;\
			uint sampleCount;\
			ms.GetDimensions(dimension.x, dimension.y, sampleCount);\
			\
			float depth = 1.#INF;\
			for (uint i = 0; i < sampleCount; ++i)\
			{\
				depth = min(depth, ms.Load(id.xy, i).r);\
			}\
			\
			resolved[id.xy] = depth;\
		}";

		const auto createDepthStencilTexture = [=](cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer, std::shared_ptr<IDefaultTexture2D> textureMS, DXGI_FORMAT format)->std::shared_ptr<IDefaultTexture2D>
		{
			const auto mostDetailedMipLevel = 0;
			auto depthStencilDesc = D3D11CreateFunctions::fetchTexture2DDescFrom(depthStencilBuffer.Get());

			if (textureMS)
			{
				cpp::com_ptr<ID3D11Texture2D> resolvedTextureBuffer;
				auto hr = D3D11CreateFunctions::createResolvedTexture(Device::getDevice().Get(), depthStencilBuffer.Get(), format, mostDetailedMipLevel, resolvedTextureBuffer.ReleaseAndGetAddressOf());
				if (FAILED(hr))
				{
					throw COM_RUNTIME_ERROR(hr, "Failed to create ResolvedTexture.");
				}

				auto resolvedTexture = std::make_shared<DefaultTexture2D>();
				std::weak_ptr<DefaultTexture2D> resolvedTextureWeak = resolvedTexture;

				auto computeShader = std::dynamic_pointer_cast<IComputeShader>(API::shared.graphics()->createShaderFromSourceCode(ShaderStage::cs, resolveDepthTextureShader, "cs_main", "cs_5_0"));
				auto texLocationDict = computeShader->getResourceLocationDict().at(ShaderResourceType::Texture);
				auto outputBufferLocation = texLocationDict.at("resolved");
				auto inputBufferLocation = texLocationDict.at("ms");
				auto threadGroupCount = cpp::Vector3D<int>(ceil(depthStencilDesc.Width / 16.0f), ceil(depthStencilDesc.Height / 16.0f), 1);

				auto resolve = [=]()
				{
					if (auto resolvedTextureSafe = resolvedTextureWeak.lock())
					{
						textureMS->set(ShaderStage::cs, inputBufferLocation, GPUAccessType::R);
						resolvedTextureSafe->set(ShaderStage::cs, outputBufferLocation, GPUAccessType::RW);

						computeShader->set();
						computeShader->dispatch(threadGroupCount.x, threadGroupCount.y, threadGroupCount.z);
					}
				};

				*resolvedTexture = DefaultTexture2D(RawTexture2D(resolvedTextureBuffer, true, static_cast<TextureFormat>(format), mostDetailedMipLevel, resolve));

				return resolvedTexture;
			}
			else
			{
			return std::make_shared<DefaultTexture2D>(RawTexture2D(depthStencilBuffer, static_cast<TextureFormat>(format), mostDetailedMipLevel));
			}
		};
		const auto checkDepthTextureFormat = [](DXGI_FORMAT d3dFormat)
		{
			::DXGI_FORMAT d3dDepthTextureFormat;
			D3D11CreateFunctions::checkDepthTextureFormat(d3dFormat, &d3dDepthTextureFormat);
			return d3dDepthTextureFormat;
		};
		const auto checkStencilTextureFormat = [](DXGI_FORMAT d3dFormat)
		{
			::DXGI_FORMAT d3dStencilTextureFormat;
			D3D11CreateFunctions::checkDepthStencilBufferFormat(d3dFormat, &d3dStencilTextureFormat);
			return d3dStencilTextureFormat;
		};
		const auto createDepthStencilBuffer = [](const cpp::Vector2D<int>& size, ::DXGI_FORMAT d3dFormat, int sampleCount, int qualityLevel)
		{
			cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer;
			D3D11_TEXTURE2D_DESC desc;
			auto pDevice = Device::getDevice().Get();

			::DXGI_FORMAT d3dDepthStencilBufferFormat;
			D3D11CreateFunctions::checkDepthStencilBufferFormat(d3dFormat, &d3dDepthStencilBufferFormat);
			D3D11CreateFunctions::createTexture2DDesc(pDevice, size.x, size.y, d3dDepthStencilBufferFormat, CPUAccessType::none, GPUAccessType::RW, 0, 0, false, sampleCount, qualityLevel, RawTexture2DType::DepthStencil, &desc);
			const auto hr = D3D11CreateFunctions::createTexture2D(pDevice, desc, nullptr, depthStencilBuffer.ReleaseAndGetAddressOf());
			if (FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create ResolvedTexture.");
			}

			return depthStencilBuffer;
		};
		const auto createDepthStencilView = [](DXGI_FORMAT d3dFormat, cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer)
		{
			cpp::com_ptr<ID3D11DepthStencilView> depthStencilView;
			auto pDevice = Device::getDevice().Get();

			const auto hr = D3D11CreateFunctions::createDepthStencilView(pDevice, depthStencilBuffer.Get(), d3dFormat, depthStencilView.ReleaseAndGetAddressOf());
			if (FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create DepthStencilView.");
			}

			return depthStencilView;
		};









		DepthStencilBuffer::DepthStencilBuffer(int width, int height, TextureFormat format, int sampleCount, int qualityLevel)
			: d3d11::DepthStencilBuffer(cpp::Vector2D<int>(width, height),
				                        static_cast<DXGI_FORMAT>(format),
				                        sampleCount,
				                        qualityLevel)
		{

		}
		cpp::com_ptr<ID3D11DepthStencilView> DepthStencilBuffer::getDepthStencilView() const
		{
			return m_depthStencilView;
		}
		DepthStencilBuffer::DepthStencilBuffer(const cpp::Vector2D<int>& size, DXGI_FORMAT d3dFormat, int sampleCount, int qualityLevel)
			: d3d11::DepthStencilBuffer(size,
										d3dFormat,
										checkDepthTextureFormat(d3dFormat),
										(d3dFormat != DXGI_FORMAT_D32_FLOAT && d3dFormat != DXGI_FORMAT_D16_UNORM) ? checkStencilTextureFormat(d3dFormat) : DXGI_FORMAT_UNKNOWN,
										createDepthStencilBuffer(size, d3dFormat, sampleCount, qualityLevel),
										sampleCount,
				                        qualityLevel)
		{
		}
		DepthStencilBuffer::DepthStencilBuffer(const cpp::Vector2D<int>& size, DXGI_FORMAT d3dFormat, DXGI_FORMAT d3dDepthTextureFormat, DXGI_FORMAT d3dStencilTextureFormat, cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer, int sampleCount, int qualityLevel)
			: d3d11::DepthStencilBuffer(size, d3dDepthTextureFormat, d3dStencilTextureFormat, depthStencilBuffer, createDepthStencilView(d3dFormat, depthStencilBuffer), sampleCount, qualityLevel)
		{
		}
		DepthStencilBuffer::DepthStencilBuffer(const cpp::Vector2D<int>& size, DXGI_FORMAT d3dDepthTextureFormat, DXGI_FORMAT d3dStencilTextureFormat, cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer, cpp::com_ptr<ID3D11DepthStencilView> depthStencilView, int sampleCount, int qualityLevel)
			: d3d11::DepthStencilBuffer(size,
				                        1 < sampleCount ? std::make_shared<DefaultTexture2D>(RawTexture2D(depthStencilBuffer, static_cast<TextureFormat>(d3dDepthTextureFormat), 0))   : nullptr, 
										((d3dStencilTextureFormat != DXGI_FORMAT_UNKNOWN) && (1 < sampleCount)) ? std::make_shared<DefaultTexture2D>(RawTexture2D(depthStencilBuffer, static_cast<TextureFormat>(d3dStencilTextureFormat), 0)) : nullptr,
				                        d3dDepthTextureFormat, 
				                        d3dStencilTextureFormat,
				                        depthStencilBuffer,
				                        depthStencilView,
				                        sampleCount,
				                        qualityLevel)
		{
		}
		DepthStencilBuffer::DepthStencilBuffer(const cpp::Vector2D<int>& size, std::shared_ptr<IDefaultTexture2D> depthTextureMS, std::shared_ptr<IDefaultTexture2D> stencilTextureMS, DXGI_FORMAT d3dDepthTextureFormat, DXGI_FORMAT d3dStencilTextureFormat, cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer, cpp::com_ptr<ID3D11DepthStencilView> depthStencilView, int sampleCount, int qualityLevel)
			: d3d11::DepthStencilBuffer(size,
				                        depthTextureMS,
				                        stencilTextureMS,
				                        createDepthStencilTexture(depthStencilBuffer, depthTextureMS, d3dDepthTextureFormat),
				                        (d3dStencilTextureFormat == DXGI_FORMAT_UNKNOWN) ? nullptr : createDepthStencilTexture(depthStencilBuffer, stencilTextureMS, d3dStencilTextureFormat),
				                        depthStencilView,
				                        sampleCount,
				                        qualityLevel)
		{
		}
		DepthStencilBuffer::DepthStencilBuffer(const cpp::Vector2D<int>& size, std::shared_ptr<IDefaultTexture2D> depthTextureMS, std::shared_ptr<IDefaultTexture2D> stencilTextureMS, std::shared_ptr<IDefaultTexture2D> depthTexture, std::shared_ptr<IDefaultTexture2D> stencilTexture, cpp::com_ptr<ID3D11DepthStencilView> depthStencilView, int sampleCount, int qualityLevel)
			: cg::DepthStencilBuffer([=](float depth, int stencil) {Device::getDeviceContext()->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, depth, stencil); },
				                     depthTexture,
				                     depthTextureMS,
				                     stencilTexture,
				                     stencilTextureMS,
				                     sampleCount,
				                     qualityLevel),
			  m_depthStencilView(depthStencilView)
		{
		}
		/*
		DepthStencilBuffer::DepthStencilBuffer(int width, int height, TextureFormat format, int sampleCount, int qualityLevel)
			: d3d11::DepthStencilBuffer(Vector2D<int>(width, height), static_cast<DXGI_FORMAT>(format), sampleCount, qualityLevel)
		{
			cpp::com_ptr<ID3D11Texture2D> depthStencilBuffer;
			D3D11_TEXTURE2D_DESC desc;
			auto d3dFormat = static_cast<DXGI_FORMAT>(format);
			auto pDevice = Device::getDevice().Get();

			DXGI_FORMAT d3dDepthStencilBufferFormat;
			D3D11CreateFunctions::checkDepthStencilBufferFormat(d3dFormat, &d3dDepthStencilBufferFormat);
			D3D11CreateFunctions::createTexture2DDesc(pDevice, width, height, d3dDepthStencilBufferFormat, CPUAccessType::none, GPUAccessType::RW, 0, 0, false, sampleCount, qualityLevel, RawTexture2DType::DepthStencil, &desc);
			auto hr = D3D11CreateFunctions::createTexture2D(pDevice, desc, nullptr, depthStencilBuffer.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create ResolvedTexture.");
			}
			hr = D3D11CreateFunctions::createDepthStencilView(pDevice, depthStencilBuffer.Get(), d3dFormat, m_depthStencilView.ReleaseAndGetAddressOf());
			if(FAILED(hr))
			{
				throw COM_RUNTIME_ERROR(hr, "Failed to create DepthStencilView.");
			}

			const auto isMultisampleEnabled = 1 < desc.SampleDesc.Count;

			DXGI_FORMAT d3dDepthTextureFormat;
			D3D11CreateFunctions::checkDepthTextureFormat(d3dFormat, &d3dDepthTextureFormat);
			if (isMultisampleEnabled)
			{
				m_depthTextureMS = std::make_shared<DefaultTexture2D>(RawTexture2D(depthStencilBuffer, static_cast<TextureFormat>(d3dDepthTextureFormat), 0));
			}
			m_depthTexture = createDepthStencilTexture(depthStencilBuffer.Get(), m_depthTextureMS, d3dDepthTextureFormat);

			if (d3dFormat != DXGI_FORMAT_D32_FLOAT && d3dFormat != DXGI_FORMAT_D16_UNORM)
			{
				DXGI_FORMAT d3dStencilTextureFormat;
				D3D11CreateFunctions::checkStencilTextureFormat(d3dFormat, &d3dStencilTextureFormat);
				if (isMultisampleEnabled)
				{
					m_stencilTextureMS = std::make_shared<DefaultTexture2D>(RawTexture2D(depthStencilBuffer, static_cast<TextureFormat>(d3dStencilTextureFormat), 0));
				}
				m_stencilTexture = createDepthStencilTexture(depthStencilBuffer.Get(), m_stencilTextureMS, d3dStencilTextureFormat);
			}
		}*/
	}
}