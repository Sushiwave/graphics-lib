#pragma once
#include <GraphicsLib/Context.hpp>
#include <ThirdParty/CPPLib/Math/Vector/Vector4D.hpp>
#include "BlendOperator.hpp"
#include "BlendFactor.hpp"

#include <unordered_map>





namespace cg
{
	class AlphaBlenderDescriptorPerRenderTarget
	{
	public:
		bool isEnabled;
		BlendFactor   srcBlendFactor;
		BlendFactor   destBlendFactor;
		BlendOperator blendOperator;
		BlendFactor   srcBlendAlphaFactor;
		BlendFactor   destBlendAlphaFactor;
		BlendOperator blendAlphaOperator;
		BlendFactor   blendFactor;
	public:
		AlphaBlenderDescriptorPerRenderTarget(bool isEnabled = false) noexcept;
		virtual ~AlphaBlenderDescriptorPerRenderTarget() = default;
	};
	class AlphaBlenderDescriptor
	{
	private:
		using Elements = std::unordered_map<int, AlphaBlenderDescriptorPerRenderTarget>;
	private:
		Elements m_elements;
		cpp::Vector4D<float> m_blendFactor;
	public:
		AlphaBlenderDescriptor() noexcept;
		virtual ~AlphaBlenderDescriptor() = default;

		void enableBlending(int renderTargetIndex, bool isEnabled);
		void setSrcBlendFactor(int renderTargetIndex, BlendFactor fact);
		void setDestBlendFactor(int renderTargetIndex, BlendFactor factor);
		void setBlendOperator(int renderTargetIndex, BlendOperator op);
		void setSrcBlendAlphaFactor(int renderTargetIndex, BlendFactor factor);
		void setDestBlendAlphaFactor(int renderTargetIndex, BlendFactor factor);
		void setBlendAlphaOperator(int renderTargetIndex, BlendOperator op);
		void setBlendFactor(cpp::Vector4D<float> blendFactor) noexcept;

		[[nodiscard]] AlphaBlenderDescriptorPerRenderTarget getElement(int renderTargetIndex) const;
		[[nodiscard]] cpp::Vector4D<float> getBlendFactor() const  noexcept;
	};
}
