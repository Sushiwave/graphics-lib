#pragma once
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>
#include <GraphicsLib/Graphics/GPUResource/DepthStencilTester/DepthStencilTester.hpp>
#include <GraphicsLib/ID/ID.hpp>

struct ID3D11DepthStencilState;





namespace cg
{
	namespace d3d11
	{
		class DepthStencilTester
			: public cg::DepthStencilTester
		{
		private:
			cpp::com_ptr<ID3D11DepthStencilState> m_depthStencilState;
		public:
			DepthStencilTester(ComparisonFunction depthFunction, ComparisonFunction stencilFunction, bool isDepthTestEnabled, bool isStencilTestEnabled, bool isDepthBufferWritingOperationEnabled);
			virtual ~DepthStencilTester() = default;
		};
	}
}
