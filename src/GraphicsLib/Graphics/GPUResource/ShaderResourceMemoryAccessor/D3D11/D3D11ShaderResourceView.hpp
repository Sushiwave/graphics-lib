#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResourceMemoryAccessor/ShaderResourceMemoryAccessor.hpp>
#include <ThirdParty/CPPLib/COM/com_ptr.hpp>

#include <d3d11.h>





namespace cg
{
	namespace d3d11
	{
		class ShaderResourceView
			: public ShaderResourceMemoryAccessor
		{
		private:
			cpp::com_ptr<ID3D11ShaderResourceView> m_view;
		public:
			ShaderResourceView() = default;
			virtual ~ShaderResourceView() = default;
			ShaderResourceView(ShaderResourceType type, const cpp::com_ptr<ID3D11ShaderResourceView>& cpD3DSRV);

			void generateMipMaps();

			ID3D11ShaderResourceView* getRawView() const;
		};
	}
}
