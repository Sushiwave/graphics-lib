#include <GraphicsLib/Graphics/DrawableObject/Components/Geometry/Components/Material/Material.hpp>





namespace cg
{
	Material::Material()
		: Material(ConstantDict())
	{
	}
	Material::Material(const TextureDict& textureDict)
		: m_textureDict(textureDict)
	{
	}
	Material::Material(const ConstantDict& constantForEachShader)
		: m_constantDict(constantForEachShader)
	{
	}
	Material::Material(const ConstantDict& constantForEachShader, TextureDict textureDict)
		: m_constantDict(constantForEachShader),
		  m_textureDict(textureDict)
	{
	}
	std::shared_ptr<Constant> Material::getConstantP(ShaderStage stage) const
	{
		auto constant = m_constantDict.getConstant(stage);
		if (constant == nullptr)
		{
			LogEX("The material does not hold a constant corresponding to a given shader stage.");
		}
		return constant;
	}
	Constant Material::getConstant(ShaderStage stage) const
	{
		auto constant = m_constantDict.getConstant(stage);
		if (constant == nullptr) 
		{
			LogEX("The material does not hold a constant corresponding to a given shader stage.");
			return Constant(); 
		}
		return *constant;
	}

	std::shared_ptr<ITexture2D> Material::getTexture(const std::string& name) const
	{
		if (m_textureDict.count(name) == 0) 
		{
			LogEX("The material does not hold the texture named \"%s\".", name.c_str());
			return nullptr; 
		}
		return m_textureDict.at(name);
	}
	Material Material::clone() const
	{
		return Material(m_constantDict.clone(), m_textureDict);
	}



	std::shared_ptr<Constant> Material::ConstantDict::getConstant(ShaderStage stage) const
	{
		if (m_dict.count(stage) == 0)
		{
			return nullptr;
		}
		return m_dict.at(stage);
	}
	Material::ConstantDict Material::ConstantDict::clone() const
	{
		Material::ConstantDict clonedConstantDict;
		for (const auto stage : ShaderStageAll)
		{
			std::shared_ptr<Constant> clonedConstant = nullptr;
			if (m_cloneConstant.count(stage))
			{
				clonedConstant = m_cloneConstant.at(stage)();
			}
			clonedConstantDict.emplace(stage, clonedConstant);
		}
		return clonedConstantDict;
	}
}
