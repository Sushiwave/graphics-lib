#pragma once
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/WavefrontOBJModel.hpp>
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJVertexDataPool.hpp>
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJIndex.hpp>
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJFace.hpp>
#include <ThirdParty/CPPLib/File/FileStream.hpp>
#include <GraphicsLib/Graphics/3DModelLoader/WavefrontOBJ/Helper/WavefrontOBJLoadingHelper.hpp>
#include <GraphicsLib/Graphics/3DModel/WavefrontOBJ/Components/WavefrontOBJTriangle.hpp>

#include <memory>
#include <string>
#include <functional>





namespace cg
{
	class WavefrontOBJModelLoader
	{
	private:
		using FaceLineParser = std::function<std::string(cpp::FileStreamInput&, const std::string&, wavefrontobj::VertexFormat, int, bool, const wavefrontobj::VertexDataPool&, unsigned int, wavefrontobj::Indices*, unsigned int*, unsigned int*, cpp::Vector3D<float>*, cpp::Vector3D<float>*)>;
	private:
		static void initializationForFaceLineParsing(wavefrontobj::VertexFormat vertexFormat, int positionDimensionCount, std::shared_ptr<void>* outVertices, std::shared_ptr<void>* outTriangles, wavefrontobj::Indices* outIndices, unsigned int* outBaseIndex, unsigned int* outVertexCount, unsigned int* outTriangleCount, int* outVertexByteSize, FaceLineParser* outFaceLineParser);

		[[nodiscard]] static int loadFaceVertexCount(const std::string& line);
		[[nodiscard]] static wavefrontobj::VertexFormat loadVertexFormat(const std::string& line, int faceVertexCount);
		[[nodiscard]] static int loadPositionDimensionCount(const std::string& line);
		[[nodiscard]] static bool loadNotation(const std::string& line);
		template <int dimensionCount_>
		[[nodiscard]] static auto loadPosition(const std::string& line, bool leftHanded, bool isExpNotation)
		{
			auto position = WavefrontOBJLoadingHelper::loadVector<float, dimensionCount_>(line, "v", " ", true, isExpNotation);
			position[0] *= leftHanded ? -1.0 : 1.0;
			return position;
		}
		[[nodiscard]] static wavefrontobj::Normal3 loadNormal3(const std::string& line, bool leftHanded, bool isExpNotation);
		[[nodiscard]] static wavefrontobj::UV2 loadUV2(const std::string& line, bool isExpNotation);
		[[nodiscard]] static std::vector<wavefrontobj::Index> loadFaceIndex(const std::string& line, wavefrontobj::VertexFormat vertexFormat, int faceVertexCount, bool leftHanded);
		[[nodiscard]] static std::string loadMaterialKey(const std::string& line);
		[[nodiscard]] static wavefrontobj::MaterialDict loadMaterial(const std::string& line);





		[[nodiscard]] static std::string parseLine(cpp::FileStreamInput& fileStream, const std::string& line, const std::string& tag, const std::function<void(const std::string&)>& loadOperation);
		[[nodiscard]] static std::string parseSmoothingGroupLine(cpp::FileStreamInput& fileStream, const std::string& line);
		[[nodiscard]] static std::string parseGroupLine(cpp::FileStreamInput& fileStream, const std::string& line, std::string* groupName);
		[[nodiscard]] static std::string parseObjectLine(cpp::FileStreamInput& fileStream, const std::string& line, std::string* objectName);
		[[nodiscard]] static std::string parseMaterialLibLine(cpp::FileStreamInput& fileStream, const std::string& line, cg::wavefrontobj::MaterialDict* materialDict);
		[[nodiscard]] static std::string parseUseMaterialLine(cpp::FileStreamInput& fileStream, const std::string& line, std::string* materialKey);
		[[nodiscard]] static std::string parsePositionLine(cpp::FileStreamInput& fileStream, const std::string& line, bool leftHanded, wavefrontobj::VertexDataPool* vertexDataPool, int* positionDimensionCount);
		[[nodiscard]] static std::string parseNormalLine(cpp::FileStreamInput& fileStream, const std::string& line, bool leftHanded, wavefrontobj::VertexDataPool* vertexDataPool);
		[[nodiscard]] static std::string parseUVLine(cpp::FileStreamInput& fileStream, const std::string& line, wavefrontobj::VertexDataPool* vertexDataPool);
		template <typename Vertex_>
		[[nodiscard]] static std::string parseFaceLine(cpp::FileStreamInput& fileStream, const std::string& line, wavefrontobj::VertexFormat vertexFormat, int positionDimensionCount, bool leftHanded, const wavefrontobj::VertexDataPool& vertexDataPool, unsigned int baseIndex, std::shared_ptr<wavefrontobj::Vertices<Vertex_>> vertices, std::shared_ptr<wavefrontobj::Triangles<Vertex_>> triangles, wavefrontobj::Indices* indices, unsigned int* vertexCount, unsigned int* triangleCount, cpp::Vector3D<float>* minXYZ, cpp::Vector3D<float>* maxXYZ)
		{
			std::unordered_map<unsigned int, Vertex_> vertexDict;
			
			auto beginIndex = baseIndex+*vertexCount;

			auto load = [&](const std::string& line_)
			{
				wavefrontobj::Triangles<Vertex_> faceTriangles;
				wavefrontobj::Indices faceIndices;
				wavefrontobj::Face<Vertex_> face;
				const auto faceVertexCount = loadFaceVertexCount(line_);
				const auto faceIndex = loadFaceIndex(line_, vertexFormat, faceVertexCount, leftHanded);
				createFace<Vertex_>(faceIndex, vertexFormat, positionDimensionCount, vertexDataPool, &face);
				createTriangle<Vertex_>(face, faceIndex, &faceTriangles, &faceIndices);

				for (int i = 0; i < faceVertexCount; ++i)
				{
					const auto index = faceIndex.at(i).vertex;
					if (vertexDict.count(index) == false &&
						beginIndex <= index)
					{
						vertexDict.emplace(index, face[i]);
						*vertexCount += 1;
					}
				}
				for (const auto& triangle : faceTriangles)
				{
					triangles->emplace_back(triangle);
					*triangleCount += 1;
				}
				for (const auto index : faceIndices)
				{
					indices->emplace_back(index-baseIndex);
				}
			};

			auto line_ = parseLine(fileStream, line, "f", load);

			auto endIndex = beginIndex+static_cast<unsigned int>(vertexDict.size());
			for (auto i = beginIndex; i < endIndex; ++i)
			{
				auto& vertex = vertexDict.at(i);
				auto position = cpp::Vector3D<float>(vertex.position);
				*minXYZ = minVector(*minXYZ, position);
				*maxXYZ = maxVector(*maxXYZ, position);
				vertices->emplace_back(vertex);
				vertexDict.erase(i);
			}

			return line_;
		}





		template <typename Vertex_>
		[[nodiscard]] static void createVertex(const wavefrontobj::Index& index, wavefrontobj::VertexFormat vertexFormat, int positionDimensionCount, const wavefrontobj::VertexDataPool& vertexDataPool, Vertex_* outVertex)
		{
			wavefrontobj::Normal3 normal = {};
			wavefrontobj::UV2 uv = {};

			if (static_cast<int>(vertexFormat) & static_cast<int>(wavefrontobj::VertexFormat::n))
			{
				normal = vertexDataPool.normal3DataPool.get(index.normal);
			}
			if (static_cast<int>(vertexFormat) & static_cast<int>(wavefrontobj::VertexFormat::t))
			{
				uv = vertexDataPool.uv2DataPool.get(index.uv);
			}

			if (positionDimensionCount == 3)
			{
				*outVertex = Vertex_(vertexDataPool.position3DataPool.get(index.vertex), normal, uv);
			}
			else if (positionDimensionCount == 4)
			{
				*outVertex = Vertex_(vertexDataPool.position4DataPool.get(index.vertex), normal, uv);
			}
		}
		template <typename Vertex_>
		static void createFace(const std::vector<wavefrontobj::Index>& faceIndex, wavefrontobj::VertexFormat vertexFormat, int positionDimensionCount, const wavefrontobj::VertexDataPool& vertexDataPool, wavefrontobj::Face<Vertex_>* outFace)
		{
			Vertex_ vertex;
			for (auto index : faceIndex)
			{
				createVertex<Vertex_>(index, vertexFormat, positionDimensionCount, vertexDataPool, &vertex);
				outFace->emplace_back(vertex);
			}
		}
		template <typename Vertex_>
		[[nodiscard]] static void createTriangle(const wavefrontobj::Face<Vertex_>& face, const std::vector<wavefrontobj::Index>& faceIndex, wavefrontobj::Triangles<Vertex_>* outTriangles, wavefrontobj::Indices* outIndices)
		{
			const auto faceVertexCount = static_cast<int>(face.size());
			if (faceVertexCount < 3)
			{
				LogEX("Couldn't make a triangle from a given face.");
				return;
			}

			const auto triangleCount = faceVertexCount-2;

			const auto i2 = faceVertexCount-1;
			for (int i = 0; i < triangleCount; ++i)
			{
				const auto i0 = i;
				const auto i1 = i+1;
				outTriangles->emplace_back(wavefrontobj::Triangle<Vertex_>{ face[i0], face[i1], face[i2] });
				outIndices->emplace_back(faceIndex.at(i0).vertex);
				outIndices->emplace_back(faceIndex.at(i1).vertex);
				outIndices->emplace_back(faceIndex.at(i2).vertex);
			}
		}
		template <typename Vertex_>
		[[nodiscard]] static void createResourceForFaceLineParsing(std::shared_ptr<void>* outVertices, std::shared_ptr<void>* outTriangles, int* outVertexByteSize, FaceLineParser* outParser)
		{
			auto vertices = std::make_shared<wavefrontobj::Vertices<Vertex_>>();
			auto triangles = std::make_shared<wavefrontobj::Triangles<Vertex_>>();
			*outVertices = vertices;
			*outTriangles = triangles;
			*outVertexByteSize = sizeof(Vertex_);

			*outParser = [=](cpp::FileStreamInput& fs, const std::string& l, wavefrontobj::VertexFormat vf, int d, bool lh, const wavefrontobj::VertexDataPool& vp, unsigned int bi, wavefrontobj::Indices* i, unsigned int* vc, unsigned int* tc, cpp::Vector3D<float>* min, cpp::Vector3D<float>* max)->std::string
			{
				return parseFaceLine<Vertex_>(fs, l, vf, d, lh, vp, bi, vertices, triangles, i, vc, tc, min, max);
			};
		}
	public:
		[[nodiscard]] static std::shared_ptr<WavefrontOBJModel> load(const std::string& filename, bool leftHanded = false);
	};
}
