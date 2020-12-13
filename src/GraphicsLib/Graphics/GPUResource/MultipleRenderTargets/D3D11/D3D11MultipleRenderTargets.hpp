#pragma once
#include <GraphicsLib/Graphics/GPUResource/RenderTarget/IRenderTarget.hpp>
#include <GraphicsLib/Graphics/GPUResource/MultipleRenderTargets/MultipleRenderTargets.hpp>

struct ID3D11RenderTargetView;





namespace cg
{
	namespace d3d11
	{
		class MultipleRenderTargets
			: public cg::MultipleRenderTargets
		{
		private:
			std::shared_ptr<ID3D11RenderTargetView*> m_renderTargetViewArray;
		public:
			MultipleRenderTargets() = default;
			MultipleRenderTargets(const std::vector<std::shared_ptr<IRenderTarget>>& renderTargetList);
			virtual ~MultipleRenderTargets() = default;



			MultipleRenderTargets& operator=(const MultipleRenderTargets& other);
		};
	}
}