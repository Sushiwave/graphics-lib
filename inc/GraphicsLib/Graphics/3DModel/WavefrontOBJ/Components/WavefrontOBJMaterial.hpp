#pragma once
#include <ThirdParty/CPPLib/Math/Vector/Vector3D.hpp>

#include <unordered_map>





namespace cg
{
	namespace wavefrontobj
	{
		using Ambient = cpp::Vector3D<float>;
		using Diffuse = cpp::Vector3D<float>;
		using Specular = cpp::Vector3D<float>;
		using Shininess = float;

		class Material
		{
		public:
			const std::string name;
			const Ambient ambient;
			const Diffuse diffuse;
			const Specular specular;
			const Shininess shininess;
			const std::string& textureFilename;
		public:
			Material();
			Material(const std::string& name, const Ambient& ambient, const Diffuse& diffuse, const Specular& specular, Shininess shininess, const std::string& textureFilename) noexcept;
			virtual ~Material() = default;
		};

		using MaterialDict = std::unordered_map<std::string, Material>;
	}
}
