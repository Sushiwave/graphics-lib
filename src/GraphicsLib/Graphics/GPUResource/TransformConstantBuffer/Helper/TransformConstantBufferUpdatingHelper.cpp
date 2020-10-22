#include <GraphicsLib/Graphics/GPUResource/TransformConstantBuffer/Helper/TransformConstantBufferUpdatingHelper.hpp>





namespace cg
{
	void TransformConstantBufferHelper::storeWVP(DirectX::XMFLOAT4X4* wvp, const Transform& transform, const Transform& camera, const Projection& projection)
	{
		DirectX::XMFLOAT4X4 vp;
		storeVP(&vp, camera, projection);
		DirectX::XMStoreFloat4x4(wvp, DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&transform.createWorldMatrix()), DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&vp)))));
	}

	void TransformConstantBufferHelper::storeW(DirectX::XMFLOAT4X4* w, const Transform& transform)
	{
		DirectX::XMStoreFloat4x4(w, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&transform.createWorldMatrix())));
	}

	void TransformConstantBufferHelper::storeVP(DirectX::XMFLOAT4X4* vp, const Transform& camera, const Projection& projection)
	{
		DirectX::XMStoreFloat4x4(vp, DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&camera.createWorldMatrix())), DirectX::XMLoadFloat4x4(&projection.createMatrix()))));
	}

	void TransformConstantBufferHelper::storeN(DirectX::XMFLOAT4X4* n, const Transform& transform)
	{
		DirectX::XMStoreFloat4x4(n, DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&transform.createWorldMatrix())));
	}
}
