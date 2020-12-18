#include <GraphicsLib/Graphics/GPUResource/TransformConstantBuffer/Helper/TransformConstantBufferUpdatingHelper.hpp>





namespace cg
{
	void TransformConstantBufferHelper::storeWVP(DirectX::XMFLOAT4X4* wvp, const Transform& transform, const Camera& camera)
	{
		DirectX::XMFLOAT4X4 w;
		storeW(&w, transform);
		DirectX::XMFLOAT4X4 vp;
		storeVP(&vp, camera);
		DirectX::XMStoreFloat4x4(wvp, DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&w)), DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&vp)))));
	}

	void TransformConstantBufferHelper::storeInvWVP(DirectX::XMFLOAT4X4* invWVP, const Transform& transform, const Camera& camera)
	{
		storeWVP(invWVP, transform, camera);
		DirectX::XMStoreFloat4x4(invWVP, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(invWVP)))));
	}

	void TransformConstantBufferHelper::storeW(DirectX::XMFLOAT4X4* w, const Transform& transform)
	{
		const auto mat = transform.createWorldMatrix();
		DirectX::XMStoreFloat4x4(w, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mat)));
	}

	void TransformConstantBufferHelper::storeInvW(DirectX::XMFLOAT4X4* invW, const Transform& transform)
	{
		storeW(invW, transform);
		DirectX::XMStoreFloat4x4(invW, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(invW)))));
	}

	void TransformConstantBufferHelper::storeV(DirectX::XMFLOAT4X4* v, const Camera& camera)
	{
		storeInvV(v, camera);
		DirectX::XMStoreFloat4x4(v, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(v)))));
	}

	void TransformConstantBufferHelper::storeInvV(DirectX::XMFLOAT4X4* invV, const Camera& camera)
	{
		const auto mat = camera.transform->createWorldMatrix();
		DirectX::XMStoreFloat4x4(invV, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mat)));
	}

	void TransformConstantBufferHelper::storeP(DirectX::XMFLOAT4X4* p, const Camera& camera)
	{
		const auto mat = camera.projection.createMatrix();
		DirectX::XMStoreFloat4x4(p, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mat)));
	}

	void TransformConstantBufferHelper::storeInvP(DirectX::XMFLOAT4X4* invP, const Camera& camera)
	{
		storeP(invP, camera);
		DirectX::XMStoreFloat4x4(invP, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(invP)))));
	}

	void TransformConstantBufferHelper::storeVP(DirectX::XMFLOAT4X4* vp, const Camera& camera)
	{
		DirectX::XMFLOAT4X4 v;
		storeV(&v, camera);
		DirectX::XMFLOAT4X4 p;
		storeP(&p, camera);
		DirectX::XMStoreFloat4x4(vp, DirectX::XMMatrixTranspose(DirectX::XMMatrixMultiply(DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&v)), DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&p)))));
	}

	void TransformConstantBufferHelper::storeInvVP(DirectX::XMFLOAT4X4* invVP, const Camera& camera)
	{
		storeVP(invVP, camera);
		DirectX::XMStoreFloat4x4(invVP, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(invVP)))));
	}

	void TransformConstantBufferHelper::storeN(DirectX::XMFLOAT4X4* n, const Transform& transform)
	{
		const auto mat = transform.createWorldMatrix();
		DirectX::XMStoreFloat4x4(n, DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&mat)))));
	}
}
