#include <GraphicsLib/Graphics/3DModelLoader/WavefrontOBJ/WavefrontOBJMaterialLoader.hpp>
#include <ThirdParty/CPPLib/File/FileStream.hpp>
#include <GraphicsLib/Graphics/3DModelLoader/WavefrontOBJ/Helper/WavefrontOBJLoadingHelper.hpp>





namespace cg
{
	namespace wavefrontobj
	{
		wavefrontobj::MaterialDict MaterialLoader::load(const std::string& filename)
		{
			MaterialDict materialDict;

			cpp::FileStreamInput fileStreamInput(filename);

			std::string line;

			std::string materialName;
			materialName.resize(1024);
			Ambient ambient;
			Diffuse diffuse;
			Specular specular;
			Shininess shininess = 0.0f;
			std::string textureFilename;
			textureFilename.resize(1024);

			while (fileStreamInput.isEOF())
			{
				fileStreamInput.getLine(line);
				if (line.empty()) { continue; }

				switch (line[0])
				{
				case 'n':
					if (materialName.empty() == false)
					{
						materialDict.emplace(materialName, Material(materialName, ambient, diffuse, specular, shininess, textureFilename));
					}

					materialName = WavefrontOBJLoadingHelper::loadName(line, "newmtl");
					
					break;
				case 'm':
					textureFilename = WavefrontOBJLoadingHelper::loadName(line, "map_Kd");
					break;
				case 'K':
					switch (line[1])
					{
					case 'a':
						{
							const auto& rgb = WavefrontOBJLoadingHelper::loadVector<float, 3>(line, "Ka", " ", true);
							ambient = { rgb[0], rgb[1], rgb[2] };
						}
						break;
					case 'd':
						{
							const auto& rgb = WavefrontOBJLoadingHelper::loadVector<float, 3>(line, "Kd", " ", true);
							diffuse = { rgb[0], rgb[1], rgb[2] };
						}
						break;
					case 's':
						{
							const auto& rgb = WavefrontOBJLoadingHelper::loadVector<float, 3>(line, "Ks", " ", true);
							specular = { rgb[0], rgb[1], rgb[2] };
						}
						break;
					default:
						LogEX("Found a line that cannot be parsed: \"%s\"", line.c_str());
						break;
					}
				case 'N':
					{
						const auto& v = WavefrontOBJLoadingHelper::loadVector<float, 1>(line, "Ns", " ", true);
						shininess = v[0];
					}
					break;
				default:
					LogEX("Found a line that cannot be parsed: \"%s\"", line.c_str());
					break;
				}
			}

			materialDict.emplace(materialName, Material(materialName, ambient, diffuse, specular, shininess, textureFilename));


			return materialDict;
		}
	}
}
