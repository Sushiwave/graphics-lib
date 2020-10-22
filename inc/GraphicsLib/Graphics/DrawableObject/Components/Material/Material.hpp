#pragma once
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Buffer/Components/Constant.hpp>
#include <GraphicsLib/Graphics/GPUResource/ShaderResource/Texture/Texture2D/Base/ITexture2D.hpp>
#include <ThirdParty/CPPLib/Log/Log.hpp>






namespace cg
{
	class Material
	{
	public:
		class ConstantDict
		{
		private:
			std::unordered_map<ShaderStage, std::function<std::shared_ptr<Constant>()>> m_cloneConstant;
			std::unordered_map<ShaderStage, std::shared_ptr<Constant>> m_dict;
		public:
			template <typename Constant_>
			void emplace(ShaderStage key, std::shared_ptr<Constant_> constant)
			{
				m_cloneConstant.emplace(key, [&, key]()->std::shared_ptr<Constant>
				{
					if (m_dict.count(key) == 0)
					{
						return nullptr;
					}
					return std::make_shared<Constant_>(m_dict[key]->clone().getP()); 
				});
				m_dict.emplace(key, constant);
			}

			[[nodiscard]] std::shared_ptr<Constant> getConstant(ShaderStage stage) const;

			[[nodiscard]] ConstantDict clone() const;
		};
		using TextureDict = std::unordered_map<std::string, std::shared_ptr<ITexture2D>>;
	private:
		ConstantDict m_constantDict;
		TextureDict m_textureDict;
	public:
		Material();
		Material(const TextureDict& textureDict);
		Material(const ConstantDict& constantForEachShader);
		Material(const ConstantDict& constantForEachShader, TextureDict textureDict);
		virtual ~Material() = default;



		[[nodiscard]] std::shared_ptr<Constant> getConstantP(ShaderStage stage) const;
		[[nodiscard]] Constant getConstant(ShaderStage stage) const;
		[[nodiscard]] std::shared_ptr<ITexture2D> getTexture(const std::string& name) const;



		[[nodiscard]] Material clone() const;
	};
}
