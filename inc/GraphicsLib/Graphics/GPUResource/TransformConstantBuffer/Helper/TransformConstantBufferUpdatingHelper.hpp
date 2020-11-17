#pragma once
#include <GraphicsLib/Graphics/Scene/Components/Camera/Camera.hpp>





namespace cg
{
	class TransformConstantBufferHelper
	{
	public:
		static void storeWVP(DirectX::XMFLOAT4X4* wvp, const Transform& transform, const Camera& camera);
		static void storeInvWVP(DirectX::XMFLOAT4X4* invWVP, const Transform& transform, const Camera& camera);

		static void storeW(DirectX::XMFLOAT4X4* w, const Transform& transform);
		static void storeInvW(DirectX::XMFLOAT4X4* invW, const Transform& transform);

		static void storeV(DirectX::XMFLOAT4X4* v, const Camera& camera);
		static void storeInvV(DirectX::XMFLOAT4X4* invV, const Camera& camera);

		static void storeP(DirectX::XMFLOAT4X4* p, const Camera& camera);
		static void storeInvP(DirectX::XMFLOAT4X4* invP, const Camera& camera);

		static void storeVP(DirectX::XMFLOAT4X4* vp, const Camera& camera);
		static void storeInvVP(DirectX::XMFLOAT4X4* invVP, const Camera& camera);

		static void storeN(DirectX::XMFLOAT4X4* n, const Transform& transform);
	};
}
