#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Camera/Camera.hpp>
#include <GraphicsLib/Graphics/Scene/Components/Projection/Projection.hpp>





namespace cg
{
	class TransformConstantBufferHelper
	{
	public:
		static void storeWVP(DirectX::XMFLOAT4X4* wvp, const Transform& transform, const Transform& camera, const Projection& projection);
		static void storeW(DirectX::XMFLOAT4X4* w, const Transform& transform);
		static void storeVP(DirectX::XMFLOAT4X4* vp, const Transform& camera, const Projection& projection);
		static void storeN(DirectX::XMFLOAT4X4* n, const Transform& transform);
	};
}
