#include <GraphicsLib/Graphics/GPUResource/TransformConstantBuffer/Helper/TransformConstantBufferUpdatingHelper.hpp>
#include <GraphicsLib/Context.hpp>





namespace cg
{
#ifdef CONTEXT_D3D11
	#define TRANSPOSE(mat) DirectX::XMStoreFloat4x4(mat, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(mat)))
#else
	#define TRANSPOSE(mat)
#endif
	void TransformConstantBufferHelper::storeInvMat(DirectX::XMFLOAT4X4* invMat, const DirectX::XMFLOAT4X4& mat)
	{
		DirectX::XMStoreFloat4x4(invMat, DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&mat)));
	}
	








	void TransformConstantBufferHelper::storeWVP(DirectX::XMFLOAT4X4* wvp, const Transform& transform, const Shape& shape, const Camera& camera)
	{
		DirectX::XMFLOAT4X4 w;
		storeW(&w, transform, shape);
		DirectX::XMFLOAT4X4 vp;
		storeVP(&vp, camera);
		DirectX::XMStoreFloat4x4(wvp, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&vp), DirectX::XMLoadFloat4x4(&w)));
	}
	void TransformConstantBufferHelper::storeWVP(DirectX::XMFLOAT4X4* wvp, const Transform& transform, const Camera& camera)
	{
		DirectX::XMFLOAT4X4 w;
		storeW(&w, transform);
		DirectX::XMFLOAT4X4 vp;
		storeVP(&vp, camera);
		DirectX::XMStoreFloat4x4(wvp, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&vp), DirectX::XMLoadFloat4x4(&w)));
	}


	
	void TransformConstantBufferHelper::storeInvWVP(DirectX::XMFLOAT4X4* invWVP, const Transform& transform, const Shape& shape, const Camera& camera)
	{
		storeWVP(invWVP, transform, shape, camera);
		storeInvMat(invWVP, *invWVP);
	}
	void TransformConstantBufferHelper::storeInvWVP(DirectX::XMFLOAT4X4* invWVP, const Transform& transform, const Camera& camera)
	{
		storeWVP(invWVP, transform, camera);
		storeInvMat(invWVP, *invWVP);
	}



	void TransformConstantBufferHelper::storeW(DirectX::XMFLOAT4X4* w, const Transform& transform, const Shape& shape)
	{
		const auto smat = shape.createMatrix();
		const auto tmat = transform.createWorldMatrix();
		DirectX::XMStoreFloat4x4(w, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&smat), DirectX::XMLoadFloat4x4(&tmat)));
	
		TRANSPOSE(w);
	}
	void TransformConstantBufferHelper::storeW(DirectX::XMFLOAT4X4* w, const Transform& transform)
	{
		*w = transform.createWorldMatrix();	
	
		TRANSPOSE(w);
	}



	void TransformConstantBufferHelper::storeInvW(DirectX::XMFLOAT4X4* invW, const Transform& transform, const Shape& shape)
	{
		storeW(invW, transform, shape);
		storeInvMat(invW, *invW);
	}
	void TransformConstantBufferHelper::storeInvW(DirectX::XMFLOAT4X4* invW, const Transform& transform)
	{
		storeW(invW, transform);
		storeInvMat(invW, *invW);
	}



	void TransformConstantBufferHelper::storeV(DirectX::XMFLOAT4X4* v, const Camera& camera)
	{
		storeInvV(v, camera);
		DirectX::XMStoreFloat4x4(v, DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(v)));
	}



	void TransformConstantBufferHelper::storeInvV(DirectX::XMFLOAT4X4* invV, const Camera& camera)
	{
		*invV = camera.transform->createWorldMatrix();
	
		TRANSPOSE(invV);
	}



	void TransformConstantBufferHelper::storeP(DirectX::XMFLOAT4X4* p, const Camera& camera)
	{
		*p = camera.projection.createMatrix();

		TRANSPOSE(p);
	}



	void TransformConstantBufferHelper::storeInvP(DirectX::XMFLOAT4X4* invP, const Camera& camera)
	{
		storeP(invP, camera);
		DirectX::XMStoreFloat4x4(invP, DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(invP)));
	}



	void TransformConstantBufferHelper::storeVP(DirectX::XMFLOAT4X4* vp, const Camera& camera)
	{
		DirectX::XMFLOAT4X4 v;
		storeV(&v, camera);
		DirectX::XMFLOAT4X4 p;
		storeP(&p, camera);
		DirectX::XMStoreFloat4x4(vp, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&p), DirectX::XMLoadFloat4x4(&v)));
	}



	void TransformConstantBufferHelper::storeInvVP(DirectX::XMFLOAT4X4* invVP, const Camera& camera)
	{
		storeVP(invVP, camera);
		storeInvMat(invVP, *invVP);
	}



	void TransformConstantBufferHelper::storeN(DirectX::XMFLOAT4X4* n, const Transform& transform, const Shape& shape)
	{
		DirectX::XMFLOAT4X4 mat;
		storeW(&mat, transform, shape);
		DirectX::XMStoreFloat4x4(n, DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(&mat)));

		TRANSPOSE(n);
	}
}
