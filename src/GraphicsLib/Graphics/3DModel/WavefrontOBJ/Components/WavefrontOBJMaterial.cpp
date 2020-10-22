#include <GraphicsLib\Graphics\3DModel\WavefrontOBJ\Components\WavefrontOBJMaterial.hpp>
#include <GraphicsLib\Graphics\DrawableObject\Components\Material\Material.hpp>





namespace cg
{
	namespace wavefrontobj
	{
		Material::Material()
			: name(""),
			  ambient(),
			  diffuse(),
			  specular(),
			  shininess(),
			  textureFilename("")
		{
		}
		Material::Material(const std::string& name, const Ambient& ambient, const Diffuse& diffuse, const Specular& specular, Shininess shininess, const std::string& textureFilename) noexcept
			: name(name),
			  ambient(ambient),
			  diffuse(diffuse),
			  specular(specular),
			  shininess(shininess),
			  textureFilename(textureFilename)
		{
		}
	}
}
