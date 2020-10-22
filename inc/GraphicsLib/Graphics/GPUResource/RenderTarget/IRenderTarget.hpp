#pragma once
#include <GraphicsLib/Graphics/GPUResource/DepthStencilBuffer/IDepthStencilBuffer.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>





namespace cg
{
	class IRenderTarget
		: public virtual IGPUResource
	{
	public:
		virtual void changeClearColor(float r, float g, float b, float a = 1.0f) = 0;
		virtual void changeClearColor(const cpp::Vector3D<float>& clearColor) = 0;
		virtual void changeClearColor(const cpp::Vector4D<float>& clearColor) = 0;

		[[nodiscard]] virtual cpp::Vector4D<float> getClearColor() const = 0;
		[[nodiscard]] virtual cpp::Vector2D<int> getSize() const = 0;

		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D> getRenderingResult() const = 0;
		[[nodiscard]] virtual std::shared_ptr<IDefaultTexture2D> getRenderingResultMS() const = 0;

		virtual void set(std::shared_ptr<IDepthStencilBuffer> depthStencilBuffer) const = 0;

		[[nodiscard]] virtual int getMostDetailedMip() const = 0;
		[[nodiscard]] virtual int getMostRoughedMip() const = 0;
		[[nodiscard]] virtual int getMSAASampleCount() const = 0;
		[[nodiscard]] virtual int getMSAAQualityLevel() const = 0;

		virtual void refresh() = 0;
	};
}
