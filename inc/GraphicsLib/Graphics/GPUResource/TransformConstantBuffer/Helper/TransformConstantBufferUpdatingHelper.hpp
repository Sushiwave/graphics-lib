#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Camera/Camera.hpp>





namespace cg
{
	class TransformConstantBufferHelper
	{
	public:
		static void storeWVP(DirectX::XMFLOAT4X4* wvp, const Transform& transform, const Camera& camera);
		static void storeW(DirectX::XMFLOAT4X4* w, const Transform& transform);
		static void storeVP(DirectX::XMFLOAT4X4* vp, const Camera& camera);
		static void storeN(DirectX::XMFLOAT4X4* n, const Transform& transform);
	};
}
