#include <GraphicsLib/Graphics/GPUResource/AlphaBlender/Components/AlphaBlenderDescriptor.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>




namespace cg
{
	AlphaBlenderDescriptorPerRenderTarget::AlphaBlenderDescriptorPerRenderTarget(bool isEnabled) noexcept
	{
		this->isEnabled = isEnabled;

		this->srcBlendFactor = BlendFactor::srcAlpha;
		this->destBlendFactor = BlendFactor::invSrcAlpha;
		this->blendOperator = BlendOperator::add;
		this->srcBlendAlphaFactor = BlendFactor::one;
		this->destBlendAlphaFactor = BlendFactor::zero;
		this->blendAlphaOperator = BlendOperator::add;
	}





	AlphaBlenderDescriptor::AlphaBlenderDescriptor() noexcept
	{
		m_blendFactor = cpp::Vector4D<float>(0.0f, 0.0f, 0.0f, 0.0f);

		m_elements.emplace(0, AlphaBlenderDescriptorPerRenderTarget(true));
		for (int i = 1; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
		{
			m_elements.emplace(i, AlphaBlenderDescriptorPerRenderTarget());
		}
	}


	const auto assert_ = [](int renderTargetIndex) 
	{ 
		Assert(0 <= renderTargetIndex && renderTargetIndex < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, "The renderTargetIndex must be between 0 adn %d", D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);
	};
	void AlphaBlenderDescriptor::enableBlending(int renderTargetIndex, bool isEnabled)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).isEnabled = isEnabled;
	}
	void AlphaBlenderDescriptor::setSrcBlendFactor(int renderTargetIndex, BlendFactor factor)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).srcBlendFactor = factor;
	}
	void AlphaBlenderDescriptor::setDestBlendFactor(int renderTargetIndex, BlendFactor factor)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).destBlendFactor = factor;
	}
	void AlphaBlenderDescriptor::setBlendOperator(int renderTargetIndex, BlendOperator op)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).blendOperator = op;
	}
	void AlphaBlenderDescriptor::setSrcBlendAlphaFactor(int renderTargetIndex, BlendFactor factor)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).srcBlendAlphaFactor = factor;
	}
	void AlphaBlenderDescriptor::setDestBlendAlphaFactor(int renderTargetIndex, BlendFactor factor)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).destBlendAlphaFactor = factor;
	}
	void AlphaBlenderDescriptor::setBlendAlphaOperator(int renderTargetIndex, BlendOperator op)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).blendAlphaOperator = op;
	}
	void AlphaBlenderDescriptor::setBlendFactor(cpp::Vector4D<float> blendFactor) noexcept
	{
		m_blendFactor = blendFactor;
	}
	AlphaBlenderDescriptorPerRenderTarget AlphaBlenderDescriptor::getElement(int renderTargetIndex) const
	{
		assert_(renderTargetIndex);
		return m_elements.at(renderTargetIndex);
	}
	cpp::Vector4D<float> AlphaBlenderDescriptor::getBlendFactor() const noexcept
	{
		return m_blendFactor;
	}
}