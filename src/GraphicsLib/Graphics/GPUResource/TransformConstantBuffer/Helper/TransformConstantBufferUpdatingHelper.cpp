#include <GraphicsLib/Graphics/GPUResource/TransformConstantBuffer/Helper/TransformConstantBufferUpdatingHelper.hpp>





namespace cg
{
	void TransformConstantBufferHelper::storeWVP(DirectX::XMFLOAT4X4* wvp, const Transform& transform, const Camera& camera)
	{
		DirectX::XMFLOAT4X4 vp;
		storeVP(&vp, camera);
		DirectX::XMStoreFloat4x4(wvp, DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&transform.createWorldMatrix()), DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&vp)))));
	}

	void TransformConstantBufferHelper::storeW(DirectX::XMFLOAT4X4* w, const Transform& transform)
	{
		DirectX::XMStoreFloat4x4(w, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&transform.createWorldMatrix())));
	}

	void TransformConstantBufferHelper::storeVP(DirectX::XMFLOAT4X4* vp, const Camera& camera)
	{
		DirectX::XMStoreFloat4x4(vp, DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&camera.getTransformRef().createWorldMatrix())), DirectX::XMLoadFloat4x4(&camera.projection.createMatrix()))));
	}

	void TransformConstantBufferHelper::storeN(DirectX::XMFLOAT4X4* n, const Transform& transform)
	{
		DirectX::XMStoreFloat4x4(n, DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&transform.createWorldMatrix())));
	}
}
