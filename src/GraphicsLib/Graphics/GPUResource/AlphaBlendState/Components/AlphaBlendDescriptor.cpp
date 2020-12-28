#include <GraphicsLib/Graphics/GPUResource/AlphaBlendState/Components/AlphaBlendDescriptor.hpp>
#include <ThirdParty/CPPLib/Assert/Assert.hpp>




namespace cg
{
	AlphaBlendDescriptorPerRenderTarget::AlphaBlendDescriptorPerRenderTarget(bool isEnabled) noexcept
	{
		this->isEnabled = isEnabled;

		this->srcBlendFactor = BlendFactor::srcAlpha;
		this->destBlendFactor = BlendFactor::invSrcAlpha;
		this->blendOperator = BlendOperator::add;
		this->srcBlendAlphaFactor = BlendFactor::one;
		this->destBlendAlphaFactor = BlendFactor::zero;
		this->blendAlphaOperator = BlendOperator::add;
	}





	AlphaBlendDescriptor::AlphaBlendDescriptor() noexcept
	{
		m_blendFactor = cpp::Vector4D<float>(0.0f, 0.0f, 0.0f, 0.0f);

		m_elements.emplace(0, AlphaBlendDescriptorPerRenderTarget(true));
		for (int i = 1; i < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
		{
			m_elements.emplace(i, AlphaBlendDescriptorPerRenderTarget());
		}
	}


	const auto assert_ = [](int renderTargetIndex) 
	{ 
		Assert(0 <= renderTargetIndex && renderTargetIndex < D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, "The renderTargetIndex must be between 0 adn %d", D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT);
	};
	void AlphaBlendDescriptor::enableBlending(int renderTargetIndex, bool isEnabled)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).isEnabled = isEnabled;
	}
	void AlphaBlendDescriptor::setSrcBlendFactor(int renderTargetIndex, BlendFactor factor)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).srcBlendFactor = factor;
	}
	void AlphaBlendDescriptor::setDestBlendFactor(int renderTargetIndex, BlendFactor factor)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).destBlendFactor = factor;
	}
	void AlphaBlendDescriptor::setBlendOperator(int renderTargetIndex, BlendOperator op)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).blendOperator = op;
	}
	void AlphaBlendDescriptor::setSrcBlendAlphaFactor(int renderTargetIndex, BlendFactor factor)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).srcBlendAlphaFactor = factor;
	}
	void AlphaBlendDescriptor::setDestBlendAlphaFactor(int renderTargetIndex, BlendFactor factor)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).destBlendAlphaFactor = factor;
	}
	void AlphaBlendDescriptor::setBlendAlphaOperator(int renderTargetIndex, BlendOperator op)
	{
		assert_(renderTargetIndex);
		m_elements.at(renderTargetIndex).blendAlphaOperator = op;
	}
	void AlphaBlendDescriptor::setBlendFactor(cpp::Vector4D<float> blendFactor) noexcept
	{
		m_blendFactor = blendFactor;
	}
	AlphaBlendDescriptorPerRenderTarget AlphaBlendDescriptor::getElement(int renderTargetIndex) const
	{
		assert_(renderTargetIndex);
		return m_elements.at(renderTargetIndex);
	}
	cpp::Vector4D<float> AlphaBlendDescriptor::getBlendFactor() const noexcept
	{
		return m_blendFactor;
	}
}